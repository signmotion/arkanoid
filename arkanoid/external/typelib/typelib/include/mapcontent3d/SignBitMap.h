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
* ������ �����, �������� � ���� ������� 3D-�������.
*/
template< std::size_t SX, std::size_t SY, std::size_t SZ >
class SignBitMap :
    public MapContent3D< Sign<>, SX, SY, SZ >
{
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< SignBitMap >  Ptr;
    typedef std::unique_ptr< SignBitMap >  UPtr;


    /**
    * ������ �� ����� ����� (����������) ������� �������.
    */
    typedef bm::bvector<>  layerRaw_t;
    typedef std::pair< Sign<>, layerRaw_t >  signLayerRaw_t;
    typedef std::pair< Sign<>, bool >  signValue_t;
    typedef std::map< Sign<>, layerRaw_t >  raw_t;


    /**
    * ��� ��� ����� ����� ����� � ����������������� ����������� ��������
    * (SID-�����).
    * ���������� SID-�����: ���������������� ����� ������� *����������������*
    * �������, ���������� ��� ���� ����� �����. ��� ��������� ��� ������ ������
    * ��������� ������ �������� (��������, ��� ��������� OpenCL), ������
    * ������� ����� ���� ���������� ������ � ������.
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
    * @return SID-����� �����.
    */
    sidMap_t const& sidMap() const;



    /**
    * @return SID ��������� ����� ��� UINT_MAX, ���� ����� �� ����������.
    */
    std::size_t sid( const Sign<>& ) const;
    std::size_t sid( const std::string& sign ) const;



    /**
    * @return ��������� ����� ��� Sign::SPACE, ���� ����� �� ����������
    *         SID �� ����������.
    */
    Sign<> sid( std::size_t n ) const;




    /**
    * @return ������ �������� ��� ������� ���� �����. ����� ���� '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return ��������� �������� ��� ������� ���� ����� ��� 0, ���� ������ ����� ���.
    */
    virtual std::size_t next( std::size_t i ) const;



    /**
    * ������ ��������� ���������������� ����� �������.
    */
    SignBitMap& operator=( const SignBitMap& b );



    /**
    * ��������� ����� � ��������� ����������� 'true' ���� �� ��� �����.
    * ���� ����� ����������, ��� ��������� �����������.
    *
    * @alias operator+=( Sign<> )
    */
    SignBitMap& operator=( const Sign<>& sign );



    /**
    * @alias operator=( Sign<> )
    */
    SignBitMap& operator+=( const Sign<>& s );
    


    /**
    * ��������� ����� �� ���� �������� �� ��� �����.
    * ���� ����� �� ����������, ��� ��������.
    * �����, ���� ������� ������������ � ����� ����� ����. �� �������� "���".
    *
    * @alias operator+=( signLayerRaw_t )
    */
    SignBitMap& operator=( const signLayerRaw_t& sl );



    /**
    * ��������� ����� �� ���� �������� �� ��� �����.
    * ���� ����� �� ����������, ��� ��������.
    * �����, ���� ������� ������������ � ����� ����� ����. �� �������� "���".
    *
    * @alias operator=( signLayerRaw_t )
    */
    SignBitMap& operator+=( const signLayerRaw_t& sl );



    /**
    * ������� ����� �� ���� ����� � �� sidMap.
    * ���� ����� �� ����������, ������ �� ����������.
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
    * @return ���-�� ���������� ����� �� �����.
    */
    std::size_t countUnique() const;



    /**
    * @return ���-�� ���� ������������� *�� ������* �����.
    *         �������� ������� �������� �� ����������.
    */
    std::size_t count() const;



    /**
    * @return ���-�� (test() == true) ��������� � ��������� ������.
    */
    std::size_t count( const Sign<>& sign ) const;


    
    /**
    * (1) ������� ������ ����-�����.
    * (2) ��������� ���������� �������� ������ ����� � ������.
    */
    void compact();



    /**
    * @return �������� �� ����-����� ��� raw().cend() ���� �������������
    *         ����� ���.
    */
    raw_t::iterator find( const Sign<>& sign );



    /**
    * @return ��������� ����� ������� �� �����.
    */
    bool has( const Sign<>& sign ) const;


    
    /**
    * @return ��������, � ������� ��������� �������� �����, ��� ������������
    *         ���� �� 1 ������� ����� ������� �����.
    */
    BitMap< SX, SY, SZ > presence() const;





private:
    /**
    * ��������� ����� ����� � SID-����� �����.
    * ��� ����� ����� ������ *���������� ��������� �����* SID.
    */
    void addSID( const Sign<>& sign );


    /**
    * ������� ����� �� SID-����� �����.
    */
    void deleteSID( const Sign<>& sign );





private:
    /**
    * ����� ���� ������� �������.
    */
    raw_t mRaw;


    /**
    * SID-����� �����.
    */
    sidMap_t mSIDMap;

};




} // typelib










#include "SignBitMap.inl"
