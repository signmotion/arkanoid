#pragma once

#include "../../configure.h"
#include "../coord2.h"
#include "../size2.h"


namespace typelib {


class DynamicMapContent2D;
class CubeDynamicMapContent2D;
class CubeDMC3D;



/**
* ������� ������ ��� ����� ���������� DMapContent2D.
*
* @see ����. � StaticMapContent2D.
*/
class DynamicMapContent2D {
public:
    /**
    * ���������� ������ ��� ������� � ��������� �����.
    */
    typedef std::size_t  index_t;




    /**
    * ������ �����.
    */
    const std::size_t  SX;
    const std::size_t  SY;




public:
    inline DynamicMapContent2D(
        std::size_t sx, std::size_t sy
    ) :
        SX( sx ), SY( sy )
    {
        assert( ((SX > 0) && (SY > 0))
            && "������ ����� ������ ���� ������ 0." );
    }




    inline size2Int_t size() const {
        return size2Int_t( SX, SY );
    }



    inline bool cube() const {
        return (SX == SY);
    }



    inline std::size_t sizeCube() const {
        assert( (SX == SY)
            && "����� �������� ������ ��� ���������� ����." );
        return SX;
    }



    inline std::size_t volume() const {
        return (SX * SY);
    }



    inline coord2Int_t minCoord() const {
        return -maxCoord();
    }

    inline coord2Int_t maxCoord() const {
        return static_cast< coord2Int_t >( (size() - 1) / 2 );
    }




    inline bool border( const coord2Int_t& c ) const {
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return (c.x == mi.x) || (c.x == ma.x)
            || (c.y == mi.y) || (c.y == ma.y);
    }

    inline bool border( int x, int y ) const {
        return border( coord2Int_t( x, y ) );
    }



    inline bool inside( const coord2Int_t& c ) const {
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return (c.x >= mi.x) && (c.x <= ma.x)
            && (c.y >= mi.y) && (c.y <= ma.y);
    }

    inline bool inside( int x, int y ) const {
        return inside( coord2Int_t( x, y ) );
    }

    /* - ����� ������������ ������� (��� ������ ic() � ���������� �������).
    inline bool inside( std::size_t i ) const {
        return (i < volume());
    }
    */




    inline bool outside( const coord2Int_t& c ) const {
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return ( (c.x < mi.x) || (c.x > ma.x) )
            || ( (c.y < mi.y) || (c.y > ma.y) );
        ;
    }

    inline bool outside( int x, int y ) const {
        return outside( coord2Int_t( x, y ) );
    }

    /* - ����� ������������ ������� - ����� ic() - � ���������� �������.
    inline bool outside( std::size_t i ) const {
        return (i >= volume());
    }
    */



    inline index_t ic( const coord2Int_t& c ) const {
        return ic( c.x, c.y );
    }

    inline index_t ic( int x, int y ) const {
        const auto max = maxCoord();
        const index_t i = (
            static_cast< std::size_t >(x + max.x)
          + static_cast< std::size_t >(y + max.y) * SX
        );
        return i;
    }




    inline coord2Int_t ci( index_t i ) const {
        // @todo optimize ����� ���������� �� ������� �������.
        const std::size_t y = i / SX;
        const std::size_t x = i - y * SX;

        const coord2Int_t c(
            static_cast< int >( x ) - maxCoord().x,
            static_cast< int >( y ) - maxCoord().y
        );

        assert( inside( c )
            && "����������� 2D ���������� ����� �� ��������� �������� �����." );

        return c;
    }




    static inline coord2Int_t isc( std::size_t cell ) {
        const static coord2Int_t a[ 9 ] = {
            coord2Int_t(  0,   0 ),
            coord2Int_t(  0,  +1 ),
            coord2Int_t( +1,   0 ),
            coord2Int_t(  0,  -1 ),
            coord2Int_t( -1,   0 ),
            coord2Int_t( +1,  +1 ),
            coord2Int_t( +1,  -1 ),
            coord2Int_t( -1,  -1 ),
            coord2Int_t( -1,  +1 )
        };

        return a[ cell ];
    }


};





/**
* �� ��, ��� DynamicMapContent2D, �� � ���� ����.
*/
class CubeDynamicMapContent2D :
    public DynamicMapContent2D
{
public:
    inline CubeDynamicMapContent2D(
        std::size_t s
    ) :
        DynamicMapContent2D( s, s )
    {
    }
};




/**
* ���������� ��� CubeDynamicMapContent2D.
*/
class CubeDMC2D :
    public CubeDynamicMapContent2D
{
    inline CubeDMC2D(
        std::size_t s
    ) :
        CubeDynamicMapContent2D( s )
    {
    }
};



} // typelib
