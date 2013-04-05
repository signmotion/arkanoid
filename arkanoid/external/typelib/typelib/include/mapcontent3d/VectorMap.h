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
* ���������� 3D, �������� � ���� 3D-��������.
*/
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class VectorMap :
    public MapContent3D< Number, SX, SY, SZ >
{
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< VectorMap >  Ptr;
    typedef std::unique_ptr< VectorMap >  UPtr;

    /**
    * ����� (����������) ����� ��������.
    * ������ � ���� 1D-������� ��� �������� � ������������ �������������
    * � ������.
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
    * @return ������ �� ������ ������ �����. ����� ���� '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return ��������� �� ������ ������ ����� ��� 0, ���� �� ������
    *         �������� ������ ���.
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
    * @return �������� � ��������� ������ �� ������.
    */
    virtual bool test( std::size_t i ) const;
    virtual bool test( const coordInt_t& ) const;
    virtual bool test( int x, int y, int z ) const;



    /**
    * @return �������� � ��������� ������ ����� ���������.
    *         ����� � ��������� ������ ������������ �������� PRECISSION.
    *
    * @todo fine �������� ��� virtual � ��������.
    */
    bool test( std::size_t i, const Number& ) const;
    bool test( const coordInt_t&, const Number& ) const;
    bool test( int x, int y, int z, const Number& ) const;




    /**
    * @return ������������� ��������.
    *
    * # ������ � ��������� ������������ �� ���������� () � [], �.�. ���
    *   ����� ������� ���� - ��������, SignNumberMap - ��������� [] �� C++
    *   ���� �� �����.
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
    * @return ����� �������� ���� �� ���� �� ������ ��������.
    */
    bool any() const;



    /**
    * @return ��� �������� �� ����� - ������.
    */
    bool none() const;



    /**
    * @return ����� ��������� ��������� ��������� ����������.
    */
    bool full() const;
    


    /**
    * @return ���������� �� ������ �������� �����.
    */
    std::size_t count() const;





private:
    /**
    * ����� ���� ��������.
    */
    raw_t mRaw;

};




} // typelib








#include "VectorMap.inl"
