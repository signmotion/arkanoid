#pragma once

#include "MapContent3D.h"
#include "../Sign.h"
#include "BitMap.h"
#include <map>
#include <set>
#include <algorithm>
#include <boost/bind.hpp>


// @see http://bmagic.sourceforge.net
#include <bm.h>



namespace typelib {

template< std::size_t SX, std::size_t SY, std::size_t SZ >
class SignBitMap;

}


/*
namespace std {

template<>
std::ostream& operator<<( std::ostream&, const typelib::SignBitMap<>& );

} // std
*/



namespace typelib {


/**
* Наборы меток, хранимые в виде битовых 3D-образов.
*/
template< std::size_t SX, std::size_t SY, std::size_t SZ >
class SignBitMap :
    public MapContent3D< Sign<>, SX, SY, SZ >
{
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< SignBitMap >  Ptr;
    typedef std::unique_ptr< SignBitMap >  UPtr;


    /**
    * Храним по слоям сырых (одномерных) битовых наборов.
    */
    typedef bm::bvector<>  layerRaw_t;
    typedef std::pair< Sign<>, layerRaw_t >  signLayerRaw_t;
    typedef std::pair< Sign<>, bool >  signValue_t;
    typedef std::map< Sign<>, layerRaw_t >  raw_t;


    /**
    * Тип для карты меток меток с последовательными уникальными номерами
    * (SID-карта).
    * Назначение SID-карты: идентифицировать метку простым *последовательным*
    * номером, уникальным для этой карты меток. Это позволяет без лишних хлопот
    * создавать список структур (например, для обработки OpenCL), индекс
    * которых может быть однозначно связан с меткой.
    *
    * @see addSID()
    */
    typedef std::map< Sign<>, std::size_t >  sidMap_t;




public:
    SignBitMap();
    SignBitMap( const Sign<>& sign, const layerRaw_t& layer );
    explicit SignBitMap( const raw_t& r );    
        
    virtual ~SignBitMap();


    raw_t const& raw() const;
    raw_t& raw();



    /**
    * @return SID-карта меток.
    */
    sidMap_t const& sidMap() const;



    /**
    * @return SID указанной метки или UINT_MAX, если метки не существует.
    */
    std::size_t sid( const Sign<>& ) const;
    std::size_t sid( const std::string& sign ) const;



    /**
    * @return Указанную метку или Sign::SPACE, если метки по указанному
    *         SID не существует.
    */
    Sign<> sid( std::size_t n ) const;




    /**
    * @return Первый зажжённый бит первого слоя карты. Может быть '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return Следующий зажжённый бит первого слоя карты или 0, если больше битов нет.
    */
    virtual std::size_t next( std::size_t i ) const;



    /**
    * Данные полностью перезаписываются новым классом.
    */
    SignBitMap& operator=( const SignBitMap& b );



    /**
    * Добавляет метку с полностью заполненным 'true' слоём на эту карту.
    * Если метка существует, она полностью заполняется.
    *
    * @alias operator+=( Sign<> )
    */
    SignBitMap& operator=( const Sign<>& sign );



    /**
    * @alias operator=( Sign<> )
    */
    SignBitMap& operator+=( const Sign<>& s );
    


    /**
    * Добавляет метку со слоём биткарты на эту карту.
    * Если метка не существует, она создаётся.
    * Иначе, слои биткарт существующей и новой метки слив. по принципу "ИЛИ".
    *
    * @alias operator+=( signLayerRaw_t )
    */
    SignBitMap& operator=( const signLayerRaw_t& sl );



    /**
    * Добавляет метку со слоём биткарты на эту карту.
    * Если метка не существует, она создаётся.
    * Иначе, слои биткарт существующей и новой метки слив. по принципу "ИЛИ".
    *
    * @alias operator=( signLayerRaw_t )
    */
    SignBitMap& operator+=( const signLayerRaw_t& sl );



    /**
    * Удаляет метку из этой карты и из sidMap.
    * Если метка не существует, ничего не происходит.
    */
    SignBitMap& operator-=( const Sign<>& sign );
    


    SignBitMap& operator&=( const SignBitMap& b );
    SignBitMap& operator|=( const SignBitMap& b );



    /* - @todo ...
    BitMap& operator^=(const BitMap& b) {
        mRaw ^= b.raw();
        return *this;
    }
    */



    bool operator==( const SignBitMap& b ) const;
    bool operator!=( const SignBitMap& b ) const;

    

    virtual void set( std::size_t i, const Sign<>& sign );
    virtual void set( const Sign<>& sign );
    void set( const coordInt_t& c, const Sign<>& sign );
    void set( int x, int y, int z, const Sign<>& sign );
    

    
    virtual bool test( std::size_t i ) const;
    virtual bool test( const coordInt_t& c ) const;
    virtual bool test( int x, int y, int z ) const;



    bool any() const;
    bool none() const;
    


    /**
    * @return Кол-во уникальных меток на карте.
    */
    std::size_t countUnique() const;



    /**
    * @return Кол-во всех установленных *не пустых* меток.
    *         Проверка каждого элемента не проводится.
    */
    std::size_t count() const;



    /**
    * @return Кол-во (test() == true) элементов с указанной меткой.
    */
    std::size_t count( const Sign<>& sign ) const;


    
    /**
    * (1) Удаляет пустые слой-метки.
    * (2) Уменьшает занимаемый битовыми слоями объём в памяти.
    */
    void compact();



    /**
    * @return Итератор на слой-метку или raw().cend() если запрашиваемой
    *         метки нет.
    */
    raw_t::iterator find( const Sign<>& sign );



    /**
    * @return Указанная метка имеется на карте.
    */
    bool has( const Sign<>& sign ) const;


    
    /**
    * @return Биткарта, в которой единицами отмечены места, где присутствует
    *         хотя бы 1 элемент среди битслоёв меток.
    */
    BitMap< SX, SY, SZ > presence() const;





private:
    /**
    * Добавляет новую метку к SID-карте меток.
    * Для новой метки ищется *минимально возможный номер* SID.
    */
    void addSID( const Sign<>& sign );


    /**
    * Удаляет метку из SID-карты меток.
    */
    void deleteSID( const Sign<>& sign );





private:
    /**
    * Сырые слои битовых наборов.
    */
    raw_t mRaw;


    /**
    * SID-карта меток.
    */
    sidMap_t mSIDMap;

};




} // typelib










#include "SignBitMap.inl"
