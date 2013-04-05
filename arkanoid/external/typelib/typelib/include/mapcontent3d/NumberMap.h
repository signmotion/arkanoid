#pragma once

#include "MapContent3D.h"
#include "../other.h"
#include <numeric>


namespace typelib {

template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class NumberMap;

}


/*
namespace std {

template< std::size_t SX, std::size_t SY, std::size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::NumberMap< SX, SY, SZ >& );

} // std
*/



namespace typelib {


/**
* Содержание 3D, хранимое в виде числового образа.
*/
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class NumberMap :
    public MapContent3D< Number, SX, SY, SZ >
{
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< NumberMap >  Ptr;
    typedef std::unique_ptr< NumberMap >  UPtr;

    /**
    * Сырой (одномерный) набор чисел.
    */
    typedef std::array< Number, SX * SY * SZ >  raw_t;



public:
    explicit NumberMap( Number value = static_cast< Number >( 0 ) );
    explicit NumberMap( const raw_t& );
        
    virtual ~NumberMap();


    raw_t const& raw() const;
    raw_t& raw();





    /**
    * @return Первое не пустое число карты. Может быть '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return Следующее не пустое значение карты или 0, если не пустых
    *         значений больше нет.
    */
    virtual std::size_t next( std::size_t i ) const;




    NumberMap& operator=( Number );
    NumberMap& operator=( const NumberMap& );

    bool operator==( const NumberMap& ) const;    
    bool operator!=( const NumberMap& ) const;

    virtual void set( std::size_t i, const Number& );
    virtual void set( const Number& );
    void set( const coordInt_t& c, const Number& );
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



    /**
    * @return Количество значений карты, равных заданному.
    *
    * @todo fine Вынести как virtual в класс-родитель.
    */
    std::size_t count( const Number& ) const;



    /**
    * @return Минимальное значение на карте.
    */
    Number min() const;



    /**
    * @return Максимальное значение на карте.
    */
    Number max() const;



    /**
    * @return Минимальное и максимальное значения на карте.
    *         [0; 0] для пустой карты.
    */
    std::pair< Number, Number>  minmax() const;



    /**
    * @return Сумма всех значений на карте.
    */
    Number sum() const;



    /**
    * @return Среднее арифметическое всех значений на карте.
    */
    Number avg() const;






private:
    raw_t mRaw;

};




} // typelib










#include "NumberMap.inl"
