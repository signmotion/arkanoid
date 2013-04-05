#pragma once

#include "MapContent3D.h"

// @see http://bmagic.sourceforge.net
#include <bm.h>


// @todo fine ������� ���������� ������� > 5 ����� � BitMap.inl.


namespace typelib {

template< std::size_t SX, std::size_t SY, std::size_t SZ >
class BitMap;

}


/*
namespace std {

template< std::size_t SX, std::size_t SY, std::size_t SZ >
std::ostream& operator<<( std::ostream&, const typelib::BitMap< SX, SY, SZ >& );

} // std
*/



namespace typelib {


/**
* ���������� 3D, �������� � ���� �������� ������.
*/
template< std::size_t SX, std::size_t SY, std::size_t SZ >
class BitMap :
    public MapContent3D< bool, SX, SY, SZ >
{
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< BitMap >  Ptr;
    typedef std::unique_ptr< BitMap >  UPtr;

    /**
    * ����� (����������) ����� ���.
    */
    typedef bm::bvector<>  raw_t;



public:
    explicit BitMap( bool value = false );
    explicit BitMap( const raw_t& r );

    virtual ~BitMap();


    raw_t const& raw() const;
    raw_t& raw();


    /**
    * @return ������ �������� ��� �����. ����� ���� '0'.
    */
    virtual std::size_t first() const;


    /**
    * @return ��������� �������� ��� ����� ��� 0, ���� ������ ����� ���.
    */
    virtual std::size_t next( std::size_t i ) const;


    BitMap& operator=( bool x );
    BitMap& operator=( const BitMap& b );

    BitMap& operator&=( const BitMap& b );
    BitMap& operator|=( const BitMap& b );
    BitMap& operator^=( const BitMap& b );

    BitMap operator&( const BitMap& b ) const;
    BitMap operator|( const BitMap& b ) const;
    BitMap operator^( const BitMap& b ) const;

    bool operator==( const BitMap& b ) const;
    bool operator!=( const BitMap& b ) const;

    void set();
    virtual void set( std::size_t i, const bool& value );
    virtual void set( const bool& value );
    void set( const coordInt_t& c );
    void set( int x, int y, int z );

    void flip( const coordInt_t& c );
    void flip( std::size_t i );
    void flip();
    
    virtual bool test( std::size_t i ) const;
    virtual bool test( const coordInt_t& c ) const;
    virtual bool test( int x, int y, int z ) const;

    bool any() const;
    bool none() const;


    /**
    * @return ������� ����� ��������� ��������.
    */
    bool full() const;


    BitMap operator~() const;

    std::size_t count() const;



    /**
    * �������� ��������� XY - raw_t �������������� ��� ��������� XY - ��
    * ������� 'z' ���� ���-�����. ���� ������������ �� �������� "���".
    */
    void assignSurfaceOr( int z, const raw_t& mapXY );




private:
    /**
    * ����� (����������) ����� ���.
    */
    raw_t mRaw;

};




} // typelib










#include "BitMap.inl"
