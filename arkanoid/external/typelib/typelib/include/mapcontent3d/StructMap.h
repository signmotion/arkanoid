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
* ���������� 3D, �������� � ���� ��������� ������.
*/
template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
class StructMap :
    public MapContent3D< Struct, SX, SY, SZ >
{
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< StructMap >  Ptr;
    typedef std::unique_ptr< StructMap >  UPtr;

    /**
    * ����� (����������) ����� �����.
    */
    typedef std::array< Struct, SX * SY * SZ >  raw_t;



public:
    explicit StructMap( Struct value );
    explicit StructMap( const raw_t& );
        
    virtual ~StructMap();


    raw_t const& raw() const;
    raw_t& raw();





    /**
    * @return ������ �� ������ ��������� �����. ����� ���� '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return ��������� �� ������ ��������� ����� ��� 0, ���� �� ������
    *         �������� ������ ���.
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
    * @return ��������� � ��������� ������ �� ������.
    *
    * # �������� �������� ������� Struct.empty().
    */
    virtual bool test( std::size_t i ) const;
    virtual bool test( const coordInt_t& ) const;
    virtual bool test( int x, int y, int z ) const;



    /**
    * @return ��������� � ��������� ������ ����� ��������.
    *
    * # �������� �������� ������� Struct.operator==().
    *
    * @todo fine �������� ��� virtual � ��������.
    */
    bool test( std::size_t i, const Struct& ) const;
    bool test( const coordInt_t&, const Struct& ) const;
    bool test( int x, int y, int z, const Struct& ) const;




    /**
    * @return ������������� ���������.
    *
    * # ������ � ��������� ������������ �� ���������� () � [], �.�. ���
    *   ����� ������� ���� - ��������, SignStructMap - ��������� [] �� C++
    *   ���� �� �����.
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
    * @return ����� �������� ���� �� ���� �� ������ ���������.
    *
    * # �������� �������� ������� Struct.empty().
    */
    bool any() const;



    /**
    * @return ��� ��������� �� ����� - ������.
    *
    * # �������� �������� ������� Struct.empty().
    */
    bool none() const;



    /**
    * @return ����� ��������� ��������� ��������� �����������.
    *
    * # �������� �������� ������� Struct.empty().
    */
    bool full() const;
    


    /**
    * @return ���������� �� ������ �������� �����.
    *
    * # �������� �������� ������� Struct.empty().
    */
    std::size_t count() const;



    /**
    * @return ���������� �������� �����, ������ �������� ���������.
    *
    * @todo fine ������� ��� virtual � �����-��������.
    *
    * # �������� �������� ������� Struct.operator==().
    */
    std::size_t count( const Struct& ) const;







private:
    /**
    * ����� ���� ��������.
    */
    raw_t mRaw;

};




} // typelib










#include "StructMap.inl"
