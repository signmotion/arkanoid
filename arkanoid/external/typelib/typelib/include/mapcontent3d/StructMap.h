#pragma once

#include "MapContent3D.h"
#include "../other.h"


namespace typelib {

template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
class StructMap;

}


/*
namespace std {

template< std::size_t SX, std::size_t SY, std::size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::StructMap< SX, SY, SZ >& );

} // std
*/



namespace typelib {


/**
* Содержание 3D, хранимое в виде числового образа.
*/
template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
class StructMap :
    public MapContent3D< Struct, SX, SY, SZ >
{
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< StructMap >  Ptr;
    typedef std::unique_ptr< StructMap >  UPtr;

    /**
    * Сырой (одномерный) набор чисел.
    */
    typedef std::array< Struct, SX * SY * SZ >  raw_t;



public:
    explicit StructMap( Struct value );
    explicit StructMap( const raw_t& );
        
    virtual ~StructMap();


    raw_t const& raw() const;
    raw_t& raw();





    /**
    * @return Первая не пустая структура карты. Может быть '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return Следующая не пустая структура карты или 0, если не пустых
    *         структур больше нет.
    */
    virtual std::size_t next( std::size_t i ) const;




    StructMap& operator=( Struct );
    StructMap& operator=( const StructMap& );

    bool operator==( const StructMap& ) const;    
    bool operator!=( const StructMap& ) const;

    virtual void set( std::size_t i, const Struct& );
    virtual void set( const Struct& );
    void set( const coordInt_t& c, const Struct& );
    void set( int x, int y, int z, const Struct& );





    /**
    * @return Структура в указанной ячейке не пустая.
    *
    * # Проверка делается методом Struct.empty().
    */
    virtual bool test( std::size_t i ) const;
    virtual bool test( const coordInt_t& ) const;
    virtual bool test( int x, int y, int z ) const;



    /**
    * @return Структура в указанной ячейке равна заданной.
    *
    * # Проверка делается методом Struct.operator==().
    *
    * @todo fine Добавить как virtual к родителю.
    */
    bool test( std::size_t i, const Struct& ) const;
    bool test( const coordInt_t&, const Struct& ) const;
    bool test( int x, int y, int z, const Struct& ) const;




    /**
    * @return Запрашиваемая структура.
    *
    * # Доступ к элементам предоставлен по операторам () и [], т.к. для
    *   более сложных карт - например, SignStructMap - оператора [] на C++
    *   быть не может.
    */
    Struct const& operator()( std::size_t i ) const;
    Struct& operator()( std::size_t i );
    Struct const& operator()( const coordInt_t& ) const;
    Struct& operator()( const coordInt_t& );

    Struct const& operator[]( std::size_t i ) const;
    Struct& operator[]( std::size_t i );
    Struct const& operator[]( const coordInt_t& ) const;
    Struct& operator[]( const coordInt_t& );




    /**
    * @return Карта содержит хотя бы одну не пустую структуру.
    *
    * # Проверка делается методом Struct.empty().
    */
    bool any() const;



    /**
    * @return Все структуры на карте - пустые.
    *
    * # Проверка делается методом Struct.empty().
    */
    bool none() const;



    /**
    * @return Карта полностью заполнена непустыми структурами.
    *
    * # Проверка делается методом Struct.empty().
    */
    bool full() const;
    


    /**
    * @return Количество не пустых структур карты.
    *
    * # Проверка делается методом Struct.empty().
    */
    std::size_t count() const;



    /**
    * @return Количество структур карты, равных заданной структуре.
    *
    * @todo fine Вынести как virtual в класс-родитель.
    *
    * # Проверка делается методом Struct.operator==().
    */
    std::size_t count( const Struct& ) const;







private:
    /**
    * Сырой слой структур.
    */
    raw_t mRaw;

};




} // typelib










#include "StructMap.inl"
