#pragma once

#include "DMapContent2D.h"
#include "../other.h"
#include <vector>


namespace typelib {

template< typename T >
class ObjectPtrDMap2D;

}



namespace typelib {


/**
* Содержание 2D динамического размера, хранимое в виде указателей на объект
* заданного шаблоном типа.
*/
template< typename T >
class ObjectPtrDMap2D :
    public DMapContent2D< T >
{
public:
    typedef std::shared_ptr< ObjectPtrDMap2D >  Ptr;
    typedef std::unique_ptr< ObjectPtrDMap2D >  UPtr;

    /**
    * Сырой (одномерный) набор.
    */
    typedef std::vector< T >  raw_t;



public:
    ObjectPtrDMap2D( std::size_t sx,  std::size_t sy,  T value = nullptr );
    ObjectPtrDMap2D( std::size_t sx,  std::size_t sy,  const raw_t& );
        
    virtual ~ObjectPtrDMap2D();


    raw_t const& raw() const;
    raw_t& raw();





    virtual index_t first() const;




    virtual index_t firstEmpty() const;




    virtual index_t next( index_t ) const;




    virtual index_t nextEmpty( index_t ) const;




    ObjectPtrDMap2D& operator=( T );
    ObjectPtrDMap2D& operator=( const ObjectPtrDMap2D& );

    bool operator==( const ObjectPtrDMap2D& ) const;    
    bool operator!=( const ObjectPtrDMap2D& ) const;

    virtual void set( index_t, const T& );
    virtual void set( const T& );
    void set( const coord2Int_t& c, const T& );
    void set( int x, int y, const T& );





    /**
    * @return Значение в указанной ячейке не пустое.
    */
    virtual bool test( index_t ) const;
    virtual bool test( const coord2Int_t& ) const;
    virtual bool test( int x, int y ) const;



    /**
    * @return Значение в указанной ячейке равно заданному.
    *         Числа с плавающей точкой сравниваются согласно PRECISSION.
    *
    * @todo fine Добавить как virtual к родителю.
    */
    bool test( index_t, const T& ) const;
    bool test( const coord2Int_t&, const T& ) const;
    bool test( int x, int y, const T& ) const;




    /**
    * @return Запрашиваемое значение.
    *
    * # Доступ к элементам предоставлен по операторам () и [], т.к. для
    *   более сложных карт - например, SignNumberMap - оператора [] на C++
    *   быть не может.
    */
    T const& operator()( index_t ) const;
    T& operator()( index_t );
    T const& operator()( const coord2Int_t& ) const;
    T& operator()( const coord2Int_t& );

    T const& operator[]( index_t ) const;
    T& operator[]( index_t );
    T const& operator[]( const coord2Int_t& ) const;
    T& operator[]( const coord2Int_t& );




    /**
    * @return Карта содержит хотя бы одно не пустое значение.
    */
    bool any() const;



    /**
    * @return Все значения на карте - пустые.
    */
    bool none() const;



    /**
    * @return Карта полностью заполнена не пустыми значениями.
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
    std::size_t count( const T& ) const;






private:
    raw_t mRaw;
};




} // typelib










#include "ObjectPtrDMap2D.inl"
