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
* ���������� 2D ������������� �������, �������� � ���� ���������� �� ������
* ��������� �������� ����.
*/
template< typename T >
class ObjectPtrDMap2D :
    public DMapContent2D< T >
{
public:
    typedef std::shared_ptr< ObjectPtrDMap2D >  Ptr;
    typedef std::unique_ptr< ObjectPtrDMap2D >  UPtr;

    /**
    * ����� (����������) �����.
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
    * @return �������� � ��������� ������ �� ������.
    */
    virtual bool test( index_t ) const;
    virtual bool test( const coord2Int_t& ) const;
    virtual bool test( int x, int y ) const;



    /**
    * @return �������� � ��������� ������ ����� ���������.
    *         ����� � ��������� ������ ������������ �������� PRECISSION.
    *
    * @todo fine �������� ��� virtual � ��������.
    */
    bool test( index_t, const T& ) const;
    bool test( const coord2Int_t&, const T& ) const;
    bool test( int x, int y, const T& ) const;




    /**
    * @return ������������� ��������.
    *
    * # ������ � ��������� ������������ �� ���������� () � [], �.�. ���
    *   ����� ������� ���� - ��������, SignNumberMap - ��������� [] �� C++
    *   ���� �� �����.
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
    * @return ����� �������� ���� �� ���� �� ������ ��������.
    */
    bool any() const;



    /**
    * @return ��� �������� �� ����� - ������.
    */
    bool none() const;



    /**
    * @return ����� ��������� ��������� �� ������� ����������.
    */
    bool full() const;
    


    /**
    * @return ���������� �� ������ �������� �����.
    */
    std::size_t count() const;



    /**
    * @return ���������� �������� �����, ������ ���������.
    *
    * @todo fine ������� ��� virtual � �����-��������.
    */
    std::size_t count( const T& ) const;






private:
    raw_t mRaw;
};




} // typelib










#include "ObjectPtrDMap2D.inl"
