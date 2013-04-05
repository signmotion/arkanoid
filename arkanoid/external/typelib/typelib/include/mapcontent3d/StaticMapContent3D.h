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
* Статические методы для карты содержания MapContent3D.
*
* @template S* Кол-во ячеек по сторонам параллелипипеда.
*
*
* Термины:
*    - тринум - часть ячейки, разбитой на равные части 3-мя плоскостями (3^3 =
*      27 частей). Лат., tria (3) + planum (плоскость) = три[пла]нум.
*    - нонум - часть ячейки, разбитой на равные части 9-тью плоскостями (9^3 =
*      729 частей). Лат., novem (9) + planum (плоскость) = но[вопла]нум.
* @see Числа по латыни > http://www.liveinternet.ru/users/2752294/post114441737
*
*
* Принцип нумерациии частей 3D-ячейки (тринумов), разбитой 3-мя плоскостями.
* Смотрим по оси OY на куб 3x3x3. Ось Z направлена вверх.
* Снимаем средний (центральный) 2D слой - номеруем его согласно isc2D().
* Снимаем ближний - номеруем также. Снимаем дальний слой - аналогично.
*
    Нумерация, вертикальный разрез:

    дальний 2D слой
    26   19   23
    22   18   20
    25   21   24

    центральный 2D слой
    8   1   5
    4   0   2
    7   3   6

    ближний 2D слой
    17   10   14
    13    9   11
    16   12   15
*
*/
template< std::size_t SX, std::size_t SY, std::size_t SZ >
class StaticMapContent3D {
public:
    /**
    * Одномерный индекс для доступа к элементам карты.
    */
    typedef std::size_t  index_t;




public:
    /**
    * @return Размер карты содержания (3D, длины сторон).
    */
    static inline sizeInt_t size() {
        return sizeInt_t( SX, SY, SZ );
    }



    /**
    * @return Все стороны карты равны.
    */
    static inline bool cube() {
        return ( (SX == SY) && (SX == SZ) );
    }



    /**
    * @return Количество ячеек по каждой из сторон карты содержания.
    */
    static inline std::size_t sizeCube() {
        static_assert( (SX == SY) && (SX == SZ), "Метод применим только для кубических карт." );
        return SX;
    }



    /**
    * @return Объём карты. Он же - размер в 1D.
    */
    static inline std::size_t volume() {
        return (SX * SY * SZ);
    }



    /**
    * @return Минимальная и максимальная координаты на карте.
    */
    static inline coordInt_t minCoord() {
        return -maxCoord();
    }

    static inline coordInt_t maxCoord() {
        return static_cast< coordInt_t >( (size() - 1) / 2 );
    }




    /**
    * @return Координата лежит на границе карты.
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
    * @return Координата лежит на карте.
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

    /* - Метод способствует ошибкам (при вызове ic() в прикладных задачах).
    static inline bool inside( index_t i ) {
        return (i < volume());
    }
    */




    /**
    * @return Координата лежит за пределами карты.
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

    /* - Метод способствует ошибкам - вызов ic() в прикладных задачах.
    static inline bool outside( index_t i ) {
        return (i >= volume());
    }
    */



    /**
    * @return 3D-координата, переведёная в 1D.
    */
    static inline std::size_t ic( const coordInt_t& c ) {
        return ic( c.x, c.y, c.z );
    }

    static inline index_t ic( int x, int y, int z ) {
        /* - Проверка мешает оптимизации.
             Пример: smik::io::IzoOgre3DVisual::operator<<( Picture )
        assert( inside( x, y, z ) && "Координата лежит за пределами карты." );
        */
        const index_t i = (
            static_cast< std::size_t >(x + maxCoord().x)
          + static_cast< std::size_t >(y + maxCoord().y) * SX
          + static_cast< std::size_t >(z + maxCoord().z) * SX * SY
        );
        return i;
    }




    /**
    * @return Трёхмерная координата по одномерной.
    *         Результат лежит в диапазоне [ minCoord(); maxCoord() ].
    */
    static inline coordInt_t ci( index_t i ) {
        return ci< SX, SY, SZ >( i );
    }




    /**
    * @see ci( int i)
    *
    * Позволяет задать размеры карты, отличные от шаблона класса.
    * Метод понадобился после ввода BitMap::assignSurfaceOr().
    */
    template< std::size_t OtherSX, std::size_t OtherSY, std::size_t OtherSZ >
    static inline coordInt_t ci( index_t i ) {
        // @todo optimize Брать координаты из готовой таблицы.
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
            && "Вычисленная 3D координата лежит за пределами заданной карты." );

        return c;
    }



    /**
    * @return Вектор смещения в сторону указанной ячейки.
    *         Если превышены границы мира, возвращает (0; 0).
    *
    * @see Нумерацию в прим. к классу.
    */
    static inline coordInt_t isc( std::size_t cell ) {
        const static coordInt_t a[27] = {
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
* То же, что StaticMapContent3D, но в виде куба.
*/
template< std::size_t S >
class CubeStaticMapContent3D :
    public StaticMapContent3D< S, S, S > {
};




/**
* Сокращение для CubeStaticMapContent3D.
*/
template< std::size_t S >
class CubeSMC3D :
    public CubeStaticMapContent3D< S > {
};



} // typelib
