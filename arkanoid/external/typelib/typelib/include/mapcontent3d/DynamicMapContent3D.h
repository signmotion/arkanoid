#pragma once

#include "../../configure.h"
#include "../coord.h"
#include "../size.h"


namespace typelib {


class DynamicMapContent3D;
class CubeDynamicMapContent3D;
class CubeDMC3D;



/**
* Базовые методы для карты содержания DMapContent3D.
*
* @see Комм. к StaticMapContent3D.
*/
class DynamicMapContent3D {
public:
    /**
    * Одномерный индекс для доступа к элементам карты.
    */
    typedef std::size_t  index_t;




    /**
    * Размер карты.
    */
    const std::size_t  SX;
    const std::size_t  SY;
    const std::size_t  SZ;




public:
    inline DynamicMapContent3D(
        std::size_t sx, std::size_t sy, std::size_t sz
    ) :
        SX( sx ), SY( sy ), SZ( sz )
    {
        assert( ((SX > 0) && (SY > 0) && (SZ > 0))
            && "Размер карты должен быть больше 0." );
    }




    inline sizeInt_t size() const {
        return sizeInt_t( SX, SY, SZ );
    }



    inline bool cube() const {
        return ( (SX == SY) && (SX == SZ) );
    }



    inline std::size_t sizeCube() const {
        assert( ((SX == SY) && (SX == SZ))
            && "Метод применим только для кубических карт." );
        return SX;
    }



    inline std::size_t volume() const {
        return (SX * SY * SZ);
    }



    inline coordInt_t minCoord() const {
        return -maxCoord();
    }

    inline coordInt_t maxCoord() const {
        return static_cast< coordInt_t >( (size() - 1) / 2 );
    }




    inline bool border( const coordInt_t& c ) const {
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return (c.x == mi.x) || (c.x == ma.x)
            || (c.y == mi.y) || (c.y == ma.y)
            || (c.z == mi.z) || (c.z == ma.z);
    }

    inline bool border( int x, int y, int z ) const {
        return border( coordInt_t( x, y, z ) );
    }



    inline bool inside( const coordInt_t& c ) const {
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return (c.x >= mi.x) && (c.x <= ma.x)
            && (c.y >= mi.y) && (c.y <= ma.y)
            && (c.z >= mi.z) && (c.z <= ma.z);
    }

    inline bool inside( int x, int y, int z ) const {
        return inside( coordInt_t( x, y, z ) );
    }

    /* - Метод способствует ошибкам (при вызове ic() в прикладных задачах).
    inline bool inside( index_t i ) const {
        return (i < volume());
    }
    */




    inline bool outside( const coordInt_t& c ) const {
        const coordInt_t mi = minCoord();
        const coordInt_t ma = maxCoord();
        return ( (c.x < mi.x) || (c.x > ma.x) )
            || ( (c.y < mi.y) || (c.y > ma.y) )
            || ( (c.z < mi.z) || (c.z > ma.z) )
        ;
    }

    inline bool outside( int x, int y, int z ) const {
        return outside( coordInt_t( x, y, z ) );
    }

    /* - Метод способствует ошибкам - вызов ic() в прикладных задачах.
    inline bool outside( index_t i ) const {
        return (i >= volume());
    }
    */



    inline index_t ic( const coordInt_t& c ) const {
        return ic( c.x, c.y, c.z );
    }

    inline index_t ic( int x, int y, int z ) const {
        const auto max = maxCoord();
        const std::size_t i = (
            static_cast< std::size_t >(x + max.x)
          + static_cast< std::size_t >(y + max.y) * SX
          + static_cast< std::size_t >(z + max.z) * SX * SY
        );
        return i;
    }




    inline coordInt_t ci( index_t i ) const {
        // @todo optimize Брать координаты из готовой таблицы.
        const std::size_t z = i / (SX * SY);
        const std::size_t kz = z * SX * SY;
        const std::size_t y = (i - kz) / SX;
        const std::size_t x = i - y * SX - kz;

        const coordInt_t c(
            static_cast< int >( x ) - maxCoord().x,
            static_cast< int >( y ) - maxCoord().y,
            static_cast< int >( z ) - maxCoord().z
        );

        assert( inside( c )
            && "Вычисленная 3D координата лежит за пределами заданной карты." );

        return c;
    }




    static inline coordInt_t isc( std::size_t cell ) {
        const static coordInt_t a[ 27 ] = {
            // центральный 2D слой: 0-8
            coordInt_t(  0,  0,  0 ),
            coordInt_t(  0,  0, +1 ),
            coordInt_t( +1,  0,  0 ),
            coordInt_t(  0,  0, -1 ),
            coordInt_t( -1,  0,  0 ),
            coordInt_t( +1,  0, +1 ),
            coordInt_t( +1,  0, -1 ),
            coordInt_t( -1,  0, -1 ),
            coordInt_t( -1,  0, +1 ),
            // ближний 2D слой: 9-17
            coordInt_t(  0, -1,  0 ),
            coordInt_t(  0, -1, +1 ),
            coordInt_t( +1, -1,  0 ),
            coordInt_t(  0, -1, -1 ),
            coordInt_t( -1, -1,  0 ),
            coordInt_t( +1, -1, +1 ),
            coordInt_t( +1, -1, -1 ),
            coordInt_t( -1, -1, -1 ),
            coordInt_t( -1, -1, +1 ),
            // дальний 2D слой: 18-26
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
* То же, что DynamicMapContent3D, но в виде куба.
*/
class CubeDynamicMapContent3D :
    public DynamicMapContent3D
{
public:
    inline CubeDynamicMapContent3D(
        std::size_t s
    ) :
        DynamicMapContent3D( s, s, s )
    {
    }
};




/**
* Сокращение для CubeDynamicMapContent3D.
*/
class CubeDMC3D :
    public CubeDynamicMapContent3D
{
    inline CubeDMC3D(
        std::size_t s
    ) :
        CubeDynamicMapContent3D( s )
    {
    }
};



} // typelib
