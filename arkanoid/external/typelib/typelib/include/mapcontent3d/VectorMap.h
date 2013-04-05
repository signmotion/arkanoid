#pragma once

#include "MapContent3D.h"
#include "../other.h"
#include "../vector.h"
#include <numeric>


namespace typelib {

template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class VectorMap;

}


/*
namespace std {

template< std::size_t SX, std::size_t SY, std::size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::VectorMap< SX, SY, SZ >& );

} // std
*/



namespace typelib {


/**
* Содержание 3D, хранимое в виде 3D-векторов.
*/
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class VectorMap :
    public MapContent3D< Number, SX, SY, SZ >
{
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< VectorMap >  Ptr;
    typedef std::unique_ptr< VectorMap >  UPtr;

    /**
    * Сырой (одномерный) набор векторов.
    * Храним в виде 1D-массива для скорости и непрерывного представления
    * в памяти.
    */
    typedef std::array< Number, SX * SY * SZ * 3 >  raw_t;



public:
    VectorMap();
    //VectorMap( const VectorT< Number >& );
    VectorMap( Number x, Number y, Number z );
    explicit VectorMap( const raw_t& );
        
    virtual ~VectorMap();


    raw_t const& raw() const;
    raw_t& raw();





    /**
    * @return Первый не пустой вектор карты. Может быть '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return Следующий не пустой вектор карты или 0, если не пустых
    *         векторов больше нет.
    */
    virtual std::size_t next( std::size_t i ) const;




    VectorMap& operator=( const VectorT< Number >& );
    VectorMap& operator=( const VectorMap& );

    bool operator==( const VectorMap& ) const;    
    bool operator!=( const VectorMap& ) const;

    virtual void set( std::size_t i, const Number& );
    virtual void set( const Number& );
    void set( const coordInt_t&, const Number& );
    void set( int x, int y, int z, const Number& );





    /**
    * @return Значение в указанной ячейке не пустое.
    */
    virtual bool test( std::size_t i ) const;
    virtual bool test( const coordInt_t& ) const;
    virtual bool test( int x, int y, int z ) const;



    /**
    * @return Значение в указанной ячейке равно заданному.
    *         Числа с плавающей точкой сравниваются согласно PRECISSION.
    *
    * @todo fine Добавить как virtual к родителю.
    */
    bool test( std::size_t i, const Number& ) const;
    bool test( const coordInt_t&, const Number& ) const;
    bool test( int x, int y, int z, const Number& ) const;




    /**
    * @return Запрашиваемое значение.
    *
    * # Доступ к элементам предоставлен по операторам () и [], т.к. для
    *   более сложных карт - например, SignNumberMap - оператора [] на C++
    *   быть не может.
    */
    Number const& operator()( std::size_t i ) const;
    Number& operator()( std::size_t i );
    Number const& operator()( const coordInt_t& ) const;
    Number& operator()( const coordInt_t& );

    Number const& operator[]( std::size_t i ) const;
    Number& operator[]( std::size_t i );
    Number const& operator[]( const coordInt_t& ) const;
    Number& operator[]( const coordInt_t& );




    /**
    * @return Карта содержит хотя бы одно не пустое значение.
    */
    bool any() const;



    /**
    * @return Все значения на карте - пустые.
    */
    bool none() const;



    /**
    * @return Карта полностью заполнена непустыми значениями.
    */
    bool full() const;
    


    /**
    * @return Количество не пустых значений карты.
    */
    std::size_t count() const;





private:
    /**
    * Сырой слой векторов.
    */
    raw_t mRaw;

};




} // typelib








#include "VectorMap.inl"
