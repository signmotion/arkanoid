#pragma once

#include "../../configure.h"
#include "DynamicMapContent2D.h"


namespace typelib {


template< typename T >
class DMapContent2D;

template< typename T >
class CubeDMapContent2D;


/**
* Карта содержания с динамически заданным размером. 2D. Базовый класс.
*
* @see Термины в StaticMapContent2D.
*/
template< typename T >
class DMapContent2D :
    public DynamicMapContent2D {
public:
    typedef std::shared_ptr< DMapContent2D >  Ptr;
    typedef std::unique_ptr< DMapContent2D >  UPtr;




public:
    inline DMapContent2D(
        std::size_t sx, std::size_t sy
    ) :
        DynamicMapContent2D( sx, sy )
    {
        assert( ((sx % 2) == 1)
            && "Длина стороны по X должна быть нечётной." );
        assert( ((sy % 2) == 1)
            && "Длина стороны по Y должна быть нечётной." );
    }




    inline virtual ~DMapContent2D() {
    }




    virtual index_t first() const = 0;




    virtual index_t firstEmpty() const = 0;




    virtual index_t next( index_t ) const = 0;




    inline bool filled(
        const coord2Int_t& c,
        std::size_t k,
        bool borderState
    ) const {
        assert( inside( c )
            && "Координата лежит за пределами карты." );
        const auto coordCell = c + isc( k );
        if ( outside( coordCell ) ) {
            return borderState;
        }
        return test( coordCell );
    }



    inline bool all4Filled( const coord2Int_t& c, bool borderState ) const {
        return
            filled( c, 1, borderState )
         && filled( c, 2, borderState )
         && filled( c, 3, borderState )
         && filled( c, 4, borderState );
    }




    inline bool all8Filled( const coord2Int_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 8; ++k) {
            if ( !filled( c, k, borderState ) ) {
                return false;
            }
        }
        return true;
    }




    inline bool any4Filled( const coord2Int_t& c, bool borderState ) const {
        return
            filled( c, 1, borderState )
         || filled( c, 2, borderState )
         || filled( c, 3, borderState )
         || filled( c, 4, borderState );
    }




    inline bool any8Filled( const coord2Int_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 8; ++k) {
            if ( filled( c, k, borderState ) ) {
                return true;
            }
        }
        return false;
    }





    virtual void set( index_t i, const T& value ) = 0;


    virtual void set( const T& value ) = 0;


    inline void set( const coord2Int_t& c, const T& value ) {
        set( ic( c ),  value );
    }


    inline bool set( int x, int y, const T& value ) {
        return set( ic( x, y ),  value );
    }



    void reset( index_t i ) {
        set( i, T() );
    }


    inline void reset( const coord2Int_t& c ) {
        reset( ic( c ) );
    }


    inline void reset( int x, int y ) {
        reset( ic( x, y ) );
    }


    inline void reset() {
        set( T() );
    }




    virtual bool test( index_t i ) const = 0;

    virtual bool test( const coord2Int_t& c ) const = 0;

    virtual bool test( int x, int y ) const = 0;




    virtual std::size_t count() const = 0;



    inline bool empty() const {
        return (count() == 0);
    }

};





/**
* То же, что DynamicMapContent2D, но в виде куба.
*/
template< typename T >
class CubeDMapContent2D :
    public DMapContent2D< T >
{
    inline CubeDMapContent2D(
        std::size_t s
    ) :
        DMapContent2D< T >( s )
    {
    }
};




} // typelib
