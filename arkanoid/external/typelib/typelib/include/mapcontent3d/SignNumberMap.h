#pragma once

#include "MapContent3D.h"
#include "../Sign.h"
#include <map>



namespace typelib {

template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class SignNumberMap;

}


/*
namespace std {

template<>
std::ostream& operator<<( std::ostream&, const typelib::SignNumberMap<>& );

} // std
*/



namespace typelib {


/**
* Наборы меток, хранимые в виде числовых 3D-образов типа Number.
*/
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class SignNumberMap :
    public MapContent3D< Sign<>, SX, SY, SZ >
{
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< SignNumberMap >  Ptr;
    typedef std::unique_ptr< SignNumberMap >  UPtr;


    /**
    * Храним по слоям числовых наборов.
    */
    typedef std::array< Number, SX * SY * SZ >  layerRaw_t;
    typedef std::pair< Sign<>, layerRaw_t >  signLayerRaw_t;
    typedef std::pair< Sign<>, Number >  signValue_t;
    typedef std::map< Sign<>, layerRaw_t >  raw_t;



    SignNumberMap();
    SignNumberMap( const Sign<>&, const layerRaw_t& );
    explicit SignNumberMap( const raw_t& );
        
    virtual ~SignNumberMap();

    raw_t const& raw() const;
    raw_t& raw();



    /**
    * Проход по непустым - !empty() - элементам карты.
    */
    virtual inline std::size_t first() const;
    virtual inline std::size_t next( std::size_t i ) const;



    SignNumberMap& operator=( const signLayerRaw_t& );    
    SignNumberMap& operator=( const SignNumberMap& );
    
    SignNumberMap& operator&=( const SignNumberMap& );


    /**
    * @return Пустые элементы замещаются непустыми. Остальные - остаются
    *         без изменений.
    */
    SignNumberMap& operator|=( const SignNumberMap& );



    bool operator==( const SignNumberMap& ) const;
    bool operator!=( const SignNumberMap& ) const;



    virtual void set( std::size_t i, const Sign<>& );
    virtual void set( const Sign<>& );
    void set( const coordInt_t&, const Sign<>& );
    void set( int x, int y, int z, const Sign<>& );


        
    virtual bool test( std::size_t i ) const;
    virtual bool test( const coordInt_t& ) const;
    virtual bool test( int x, int y, int z ) const;



    /**
    * @return Запрашиваемый элемент.
    */
    Number const& operator()( const Sign<>&, std::size_t i ) const;
    Number& operator()( const Sign<>&, std::size_t i );
    Number const& operator()( const Sign<>&, const coordInt_t& ) const;
    Number& operator()( const Sign<>&, const coordInt_t& );


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
    std::size_t count( const Sign<>& ) const;




    /**
    * (1) Удаляет пустые слой-метки.
    * (2) Уменьшает занимаемый битовыми слоями объём в памяти.
    */
    void compact();

    

    /**
    * @return Итератор на слой-метку или raw.cend() если запрашиваемой
    *         метки нет.
    */
    typename raw_t::iterator find( const Sign<>& );



    /**
    * @return Указанная метка имеется на карте.
    */
    bool has( const Sign<>& ) const;







    /**
    * @return Биткарту, в которой 1-цами отмечены места, где присутствует
    *         элементы с указанным диапазоном значений.
    */
    BitMap< SX, SY, SZ > presence( Number from, Number to ) const;





private:
    /**
    * Сырые слои битовых наборов.
    */
    raw_t mRaw;

};




} // typelib










#include "SignNumberMap.inl"
