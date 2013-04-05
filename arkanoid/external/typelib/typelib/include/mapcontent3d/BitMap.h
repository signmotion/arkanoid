#pragma once

#include "MapContent3D.h"

// @see http://bmagic.sourceforge.net
#include <bm.h>


// @todo fine Вынести реализацию методов > 5 строк в BitMap.inl.


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
* Содержание 3D, хранимое в виде битового образа.
*/
template< std::size_t SX, std::size_t SY, std::size_t SZ >
class BitMap :
    public MapContent3D< bool, SX, SY, SZ >
{
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< BitMap >  Ptr;
    typedef std::unique_ptr< BitMap >  UPtr;

    /**
    * Сырой (одномерный) набор бит.
    */
    typedef bm::bvector<>  raw_t;



public:
    explicit BitMap( bool value = false );
    explicit BitMap( const raw_t& r );

    virtual ~BitMap();


    raw_t const& raw() const;
    raw_t& raw();


    /**
    * @return Первый зажжённый бит карты. Может быть '0'.
    */
    virtual std::size_t first() const;


    /**
    * @return Следующий зажжённый бит карты или 0, если больше битов нет.
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
    * @return Битовый объём полностью заполнен.
    */
    bool full() const;


    BitMap operator~() const;

    std::size_t count() const;



    /**
    * Помещает плоскость XY - raw_t воспринимается как плоскость XY - на
    * уровень 'z' этой бит-карты. Биты объединяются по принципу "ИЛИ".
    */
    void assignSurfaceOr( int z, const raw_t& mapXY );




private:
    /**
    * Сырой (одномерный) набор бит.
    */
    raw_t mRaw;

};




} // typelib










#include "BitMap.inl"
