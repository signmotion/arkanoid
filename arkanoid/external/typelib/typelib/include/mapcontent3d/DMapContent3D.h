#pragma once

#include "../../configure.h"
#include "DynamicMapContent3D.h"


namespace typelib {


template< typename T >
class DMapContent3D;

template< typename T >
class CubeDMapContent3D;


/**
*  арта содержани€ с динамически заданным размером. 3D. Ѕазовый класс.
*
* @see “ермины в StaticMapContent3D.
*/
template< typename T >
class DMapContent3D :
    public DynamicMapContent3D {
public:
    typedef std::shared_ptr< DMapContent3D >  Ptr;
    typedef std::unique_ptr< DMapContent3D >  UPtr;




public:
    inline DMapContent3D(
        std::size_t sx, std::size_t sy, std::size_t sz
    ) :
        DynamicMapContent3D( sx, sy, sz )
    {
        assert( ((sx % 2) == 1)
            && "ƒлина стороны по X должна быть нечЄтной." );
        assert( ((sy % 2) == 1)
            && "ƒлина стороны по Y должна быть нечЄтной." );
        assert( ((sz % 2) == 1)
            && "ƒлина стороны по Z должна быть нечЄтной." );
    }




    inline virtual ~DMapContent3D() {
    }




    virtual std::size_t first() const = 0;




    virtual std::size_t next( std::size_t i ) const = 0;




    inline std::pair< int, int >  edgeZ() const {
        std::pair< int, int >  r( maxCoord().z + 1,  minCoord().z - 1 );
        std::size_t i = first();
        do {
            const coordInt_t c = ci( i );
            if (c.z < r.first) {
                r.first = c.z;
            }
            if (c.z > r.second) {
                r.second = c.z;
            }

            i = next( i );

        } while (i != 0);

        return r;
    }




    inline bool filled(
        const coordInt_t& c,
        std::size_t k,
        bool borderState
    ) const {
        assert( inside( c )
            && " оордината лежит за пределами карты." );
        const coordInt_t coordCell = c + isc( k );
        if ( outside( coordCell ) ) {
            return borderState;
        }
        return test( coordCell );
    }



    inline bool all6Filled( const coordInt_t& c, bool borderState ) const {
        return
            // верхн€€
            filled( c, 1, borderState )
            // права€
         && filled( c, 2, borderState )
            // нижн€€
         && filled( c, 3, borderState )
            // лева€
         && filled( c, 4, borderState )
            // ближн€€
         && filled( c, 9, borderState )
            // дальн€€
         && filled( c, 18, borderState );
    }




    inline bool all26Filled( const coordInt_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 26; ++k) {
            if ( !filled( c, k, borderState ) ) {
                return false;
            }
        }
        return true;
    }




    inline bool any6Filled( const coordInt_t& c, bool borderState ) const {
        return
            // верхн€€
            filled( c, 1, borderState )
            // права€
         || filled( c, 2, borderState )
            // нижн€€
         || filled( c, 3, borderState )
            // лева€
         || filled( c, 4, borderState )
            // ближн€€
         || filled( c, 9, borderState )
            // дальн€€
         || filled( c, 18, borderState );
    }




    inline bool any26Filled( const coordInt_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 26; ++k) {
            if ( filled( c, k, borderState ) ) {
                return true;
            }
        }
        return false;
    }





    virtual void set( std::size_t i, const T& value ) = 0;


    virtual void set( const T& value ) = 0;


    inline void set( const coordInt_t& c, const T& value ) {
        set( ic( c ),  value );
    }


    inline bool set( int x, int y, int z, const T& value ) {
        return set( ic( x, y, z ),  value );
    }



    void reset( std::size_t i ) {
        set( i, T() );
    }


    inline void reset( const coordInt_t& c ) {
        reset( ic( c ) );
    }


    inline void reset( int x, int y, int z ) {
        reset( ic( x, y, z ) );
    }


    inline void reset() {
        set( T() );
    }




    virtual bool test( std::size_t i ) const = 0;

    virtual bool test( const coordInt_t& c ) const = 0;

    virtual bool test( int x, int y, int z ) const = 0;




    virtual std::size_t count() const = 0;



    inline bool empty() const {
        return (count() == 0);
    }

};





/**
* “о же, что DynamicMapContent3D, но в виде куба.
*/
template< typename T >
class CubeDMapContent3D :
    public DMapContent3D< T >
{
    inline CubeDMapContent3D(
        std::size_t s
    ) :
        DMapContent3D< T >( s )
    {
    }
};




} // typelib
