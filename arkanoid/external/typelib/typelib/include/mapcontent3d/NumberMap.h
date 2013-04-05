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
* ���������� 3D, �������� � ���� ��������� ������.
*/
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
class NumberMap :
    public MapContent3D< Number, SX, SY, SZ >
{
public:
    /**
    * ������.
    */
    typedef std::shared_ptr< NumberMap >  Ptr;
    typedef std::unique_ptr< NumberMap >  UPtr;

    /**
    * ����� (����������) ����� �����.
    */
    typedef std::array< Number, SX * SY * SZ >  raw_t;



public:
    explicit NumberMap( Number value = static_cast< Number >( 0 ) );
    explicit NumberMap( const raw_t& );
        
    virtual ~NumberMap();


    raw_t const& raw() const;
    raw_t& raw();





    /**
    * @return ������ �� ������ ����� �����. ����� ���� '0'.
    */
    virtual std::size_t first() const;



    /**
    * @return ��������� �� ������ �������� ����� ��� 0, ���� �� ������
    *         �������� ������ ���.
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



    /**
    * @return ���������� �������� �����, ������ ���������.
    *
    * @todo fine ������� ��� virtual � �����-��������.
    */
    std::size_t count( const Number& ) const;



    /**
    * @return ����������� �������� �� �����.
    */
    Number min() const;



    /**
    * @return ������������ �������� �� �����.
    */
    Number max() const;



    /**
    * @return ����������� � ������������ �������� �� �����.
    *         [0; 0] ��� ������ �����.
    */
    std::pair< Number, Number>  minmax() const;



    /**
    * @return ����� ���� �������� �� �����.
    */
    Number sum() const;



    /**
    * @return ������� �������������� ���� �������� �� �����.
    */
    Number avg() const;






private:
    raw_t mRaw;

};




} // typelib










#include "NumberMap.inl"
