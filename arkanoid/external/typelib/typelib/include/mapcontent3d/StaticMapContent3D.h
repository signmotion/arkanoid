#pragma once

#include "../../configure.h"
#include "../coord.h"
#include "../size.h"


namespace typelib {


template< std::size_t SX, std::size_t SY, std::size_t SZ >
class StaticMapContent3D;

template< std::size_t S >
class CubeStaticMapContent3D;

template< std::size_t S >
class CubeSMC3D;



/**
* ����������� ������ ��� ����� ���������� MapContent3D.
*
* @template S* ���-�� ����� �� �������� ���������������.
*
*
* �������:
*    - ������ - ����� ������, �������� �� ������ ����� 3-�� ����������� (3^3 =
*      27 ������). ���., tria (3) + planum (���������) = ���[���]���.
*    - ����� - ����� ������, �������� �� ������ ����� 9-��� ����������� (9^3 =
*      729 ������). ���., novem (9) + planum (���������) = ��[�����]���.
* @see ����� �� ������ > http://www.liveinternet.ru/users/2752294/post114441737
*
*
* ������� ���������� ������ 3D-������ (��������), �������� 3-�� �����������.
* ������� �� ��� OY �� ��� 3x3x3. ��� Z ���������� �����.
* ������� ������� (�����������) 2D ���� - �������� ��� �������� isc2D().
* ������� ������� - �������� �����. ������� ������� ���� - ����������.
*
    ���������, ������������ ������:

    ������� 2D ����
    26   19   23
    22   18   20
    25   21   24

    ����������� 2D ����
    8   1   5
    4   0   2
    7   3   6

    ������� 2D ����
    17   10   14
    13    9   11
    16   12   15
*
*/
template< std::size_t SX, std::size_t SY, std::size_t SZ >
class StaticMapContent3D {
public:
    /**
    * ���������� ������ ��� ������� � ��������� �����.
    */
    typedef std::size_t  index_t;




public:
    /**
    * @return ������ ����� ���������� (3D, ����� ������).
    */
    static inline sizeInt_t size() {
        return sizeInt_t( SX, SY, SZ );
    }



    /**
    * @return ��� ������� ����� �����.
    */
    static inline bool cube() {
        return ( (SX == SY) && (SX == SZ) );
    }



    /**
    * @return ���������� ����� �� ������ �� ������ ����� ����������.
    */
    static inline std::size_t sizeCube() {
        static_assert( (SX == SY) && (SX == SZ), "����� �������� ������ ��� ���������� ����." );
        return SX;
    }



    /**
    * @return ����� �����. �� �� - ������ � 1D.
    */
    static inline std::size_t volume() {
        return (SX * SY * SZ);
    }



    /**
    * @return ����������� � ������������ ���������� �� �����.
    */
    static inline coordInt_t minCoord() {
        return -maxCoord();
    }

    static inline coordInt_t maxCoord() {
        return static_cast< coordInt_t >( (size() - 1) / 2 );
    }




    /**
    * @return ���������� ����� �� ������� �����.
    */
    static inline bool border( const coordInt_t& c ) {
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return (c.x == mi.x) || (c.x == ma.x)
            || (c.y == mi.y) || (c.y == ma.y)
            || (c.z == mi.z) || (c.z == ma.z);
    }

    static inline bool border( int x, int y, int z ) {
        return border( coordInt_t( x, y, z ) );
    }



    /**
    * @return ���������� ����� �� �����.
    *
    * @alias !outside()
    */
    static inline bool inside( const coordInt_t& c ) {
        //return inside( ic( c ) );
        //return (c >= minCoord()) && (c <= maxCoord());
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return (c.x >= mi.x) && (c.x <= ma.x)
            && (c.y >= mi.y) && (c.y <= ma.y)
            && (c.z >= mi.z) && (c.z <= ma.z);
    }

    static inline bool inside( int x, int y, int z ) {
        //return inside( ic( x, y, z ) );
        return inside( coordInt_t( x, y, z ) );
    }

    /* - ����� ������������ ������� (��� ������ ic() � ���������� �������).
    static inline bool inside( index_t i ) {
        return (i < volume());
    }
    */




    /**
    * @return ���������� ����� �� ��������� �����.
    *
    * @alias !inside()
    */
    static inline bool outside( const coordInt_t& c ) {
        const coordInt_t mi = minCoord();
        const coordInt_t ma = maxCoord();
        return ( (c.x < mi.x) || (c.x > ma.x) )
            || ( (c.y < mi.y) || (c.y > ma.y) )
            || ( (c.z < mi.z) || (c.z > ma.z) )
        ;
    }

    static inline bool outside( int x, int y, int z ) {
        return outside( coordInt_t( x, y, z ) );
    }

    /* - ����� ������������ ������� - ����� ic() � ���������� �������.
    static inline bool outside( index_t i ) {
        return (i >= volume());
    }
    */



    /**
    * @return 3D-����������, ���������� � 1D.
    */
    static inline std::size_t ic( const coordInt_t& c ) {
        return ic( c.x, c.y, c.z );
    }

    static inline index_t ic( int x, int y, int z ) {
        /* - �������� ������ �����������.
             ������: smik::io::IzoOgre3DVisual::operator<<( Picture )
        assert( inside( x, y, z ) && "���������� ����� �� ��������� �����." );
        */
        const index_t i = (
            static_cast< std::size_t >(x + maxCoord().x)
          + static_cast< std::size_t >(y + maxCoord().y) * SX
          + static_cast< std::size_t >(z + maxCoord().z) * SX * SY
        );
        return i;
    }




    /**
    * @return ��������� ���������� �� ����������.
    *         ��������� ����� � ��������� [ minCoord(); maxCoord() ].
    */
    static inline coordInt_t ci( index_t i ) {
        return ci< SX, SY, SZ >( i );
    }




    /**
    * @see ci( int i)
    *
    * ��������� ������ ������� �����, �������� �� ������� ������.
    * ����� ����������� ����� ����� BitMap::assignSurfaceOr().
    */
    template< std::size_t OtherSX, std::size_t OtherSY, std::size_t OtherSZ >
    static inline coordInt_t ci( index_t i ) {
        // @todo optimize ����� ���������� �� ������� �������.
        const std::size_t z = i / (OtherSX * OtherSY);
        const std::size_t kz = z * OtherSX * OtherSY;
        const std::size_t y = (i - kz) / OtherSX;
        const std::size_t x = i - y * OtherSX - kz;

        const coordInt_t c(
            static_cast< int >( x ) - maxCoord().x,
            static_cast< int >( y ) - maxCoord().y,
            static_cast< int >( z ) - maxCoord().z
        );

        assert( inside( c )
            && "����������� 3D ���������� ����� �� ��������� �������� �����." );

        return c;
    }



    /**
    * @return ������ �������� � ������� ��������� ������.
    *         ���� ��������� ������� ����, ���������� (0; 0).
    *
    * @see ��������� � ����. � ������.
    */
    static inline coordInt_t isc( std::size_t cell ) {
        const static coordInt_t a[27] = {
            // ����������� 2D ����: 0-8
            coordInt_t(  0,  0,  0 ),
            coordInt_t(  0,  0, +1 ),
            coordInt_t( +1,  0,  0 ),
            coordInt_t(  0,  0, -1 ),
            coordInt_t( -1,  0,  0 ),
            coordInt_t( +1,  0, +1 ),
            coordInt_t( +1,  0, -1 ),
            coordInt_t( -1,  0, -1 ),
            coordInt_t( -1,  0, +1 ),
            // ������� 2D ����: 9-17
            coordInt_t(  0, -1,  0 ),
            coordInt_t(  0, -1, +1 ),
            coordInt_t( +1, -1,  0 ),
            coordInt_t(  0, -1, -1 ),
            coordInt_t( -1, -1,  0 ),
            coordInt_t( +1, -1, +1 ),
            coordInt_t( +1, -1, -1 ),
            coordInt_t( -1, -1, -1 ),
            coordInt_t( -1, -1, +1 ),
            // ������� 2D ����: 18-26
            coordInt_t(  0, +1,  0 ),
            coordInt_t(  0, +1, +1 ),
            coordInt_t( +1, +1,  0 ),
            coordInt_t(  0, +1, -1 ),
            coordInt_t( -1, +1,  0 ),
            coordInt_t( +1, +1, +1 ),
            coordInt_t( +1, +1, -1 ),
            coordInt_t( -1, +1, -1 ),
            coordInt_t( -1, +1, +1 )
        };

        return a[ cell ];
    }


};





/**
* �� ��, ��� StaticMapContent3D, �� � ���� ����.
*/
template< std::size_t S >
class CubeStaticMapContent3D :
    public StaticMapContent3D< S, S, S > {
};




/**
* ���������� ��� CubeStaticMapContent3D.
*/
template< std::size_t S >
class CubeSMC3D :
    public CubeStaticMapContent3D< S > {
};



} // typelib
