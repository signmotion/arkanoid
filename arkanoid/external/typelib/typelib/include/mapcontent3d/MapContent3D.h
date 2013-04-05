#pragma once

#include "../../configure.h"
#include "StaticMapContent3D.h"


// @todo fine Вынести реализацию методов > 5 строк в MapContent3D.inl.


namespace typelib {


template< typename T, std::size_t SX, std::size_t SY, std::size_t SZ >
class MapContent3D;

template< typename T, std::size_t S >
class CubeMapContent3D;


/**
* Карта содержания. 3D. Базовый класс.
*
* @template S* См. StaticMapContent3D.
*
* @see Термины в StaticMapContent3D.
*/
template< typename T, std::size_t SX, std::size_t SY, std::size_t SZ >
class MapContent3D :
    public StaticMapContent3D< SX, SY, SZ > {
public:
    typedef std::shared_ptr< MapContent3D >  Ptr;
    typedef std::unique_ptr< MapContent3D >  UPtr;




public:

    inline MapContent3D() {
        static_assert( ((SX % 2) == 1), "Длина стороны по X должна быть нечётной." );
        static_assert( ((SY % 2) == 1), "Длина стороны по Y должна быть нечётной." );
        static_assert( ((SZ % 2) == 1), "Длина стороны по Z должна быть нечётной." );
    }



    inline virtual ~MapContent3D() {
    }




    /**
    * @return Первый не пустой элемент карты.
    *         (!) 1D-координата в формате хранения 'raw'.
    *         Если элемент не найден, возвращается значение,
    *         равное или превышающее объём карты volume().
    *
    * @see raw, next(), ic(), ci()
    */
    virtual index_t first() const = 0;




    /**
    * @return Первый пустой элемент карты.
    *         Если элемент не найден, возвращается значение,
    *         равное или превышающее объём карты volume().
    *
    * @see raw, next(), ic(), ci()
    */
    inline virtual index_t firstEmpty() const {
        assert( false
            && "@todo ..." );
    }



    /**
    * @return Следующий не пустой элемент карты по 1D-координате.
    *         Если элемент не найден, возвращается значение,
    *         равное или превышающее объём карты volume().
    *
    * @see first(), ic(), ci()
    */
    virtual index_t next( index_t i ) const = 0;



    /**
    * @return Следующий пустой элемент карты по 1D-координате.
    *         Если элемент не найден, возвращается значение,
    *         равное или превышающее объём карты volume().
    *
    * @see first(), ic(), ci()
    */
    virtual index_t nextEmpty( index_t i ) const {
        assert( false
            && "@todo ..." );
    }




    /**
    * @return Крайние координаты не пустых - !T.empty() - значений
    *         по соотв. осям этой карты: edgeZ() - gпо оси Z. Если
    *         значений на карте нет, результат не определён (следует
    *         проверять карту на empty()).
    */
    inline std::pair< int, int >  edgeZ() const {
        std::pair< int, int >
            r( maxCoord().z + 1,  minCoord().z - 1 );
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





    /**
    * @return Содежание с указанной стороны ячейки не пустое.
    *
    * Если соседняя ячейка выходит за пределы 3D-матрицы (ячейка лежит на
    * границе), возвращает 'false'.
    *
    * @param с Рассматриваемая ячейка.
    * @param k Номер соседней ячейки. Нумерация сторон - см. прим. к классу.
    * @param borderState Воспринимать ячейку за границами карты как заполненную.
    *
    * @todo Вынести borderState в template.
    */
    inline bool filled( const coordInt_t& c, std::size_t k, bool borderState ) const {
        assert( inside( c ) && "Координата лежит за пределами карты." );
        const coordInt_t coordCell = c + isc( k );
        if ( outside( coordCell ) ) {
            return borderState;
        }
        return test( coordCell );
    }



    /**
    * @return Содержание со *всех* 6-ти сторон ячейки - не пустое.
    *         Проверяются ячейки 1, 2, 3, 4, 9, 18 - см. прим. к классу.
    *
    * @see filled(), any6Filled()
    */
    inline bool all6Filled( const coordInt_t& c, bool borderState ) const {
        return
            // верхняя
            filled( c, 1, borderState )
            // правая
         && filled( c, 2, borderState )
            // нижняя
         && filled( c, 3, borderState )
            // левая
         && filled( c, 4, borderState )
            // ближняя
         && filled( c, 9, borderState )
            // дальняя
         && filled( c, 18, borderState );
    }




    /**
    * @return Содержание со *всех* 26-ти сторон ячейки - не пустое.
    *
    * @see filled(), any26Filled()
    */
    inline bool all26Filled( const coordInt_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 26; ++k) {
            if ( !filled( c, k, borderState ) ) {
                return false;
            }
        }
        return true;
    }




    /**
    * @return Содержание с *одной* из 6-ти сторон ячейки - не пустое.
    *
    * @see filled(), all6Filled()
    */
    inline bool any6Filled( const coordInt_t& c, bool borderState ) const {
        return
            // верхняя
            filled( c, 1, borderState )
            // правая
         || filled( c, 2, borderState )
            // нижняя
         || filled( c, 3, borderState )
            // левая
         || filled( c, 4, borderState )
            // ближняя
         || filled( c, 9, borderState )
            // дальняя
         || filled( c, 18, borderState );
    }




    /**
    * @return Содержание с *одной* из 26-ти сторон ячейки - не пустое.
    *
    * @see filled(), all26Filled()
    */
    inline bool any26Filled( const coordInt_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 26; ++k) {
            if ( filled( c, k, borderState ) ) {
                return true;
            }
        }
        return false;
    }





    /**
    * @param i Одномерная координата.
    *
    * @see ic()
    */
    virtual void set( std::size_t i, const T& value ) = 0;


    virtual void set( const T& value ) = 0;


    inline void set( const coordInt_t& c, const T& value ) {
        set( ic( c ),  value );
    }


    inline bool set( int x, int y, int z, const T& value ) {
        return set( ic( x, y, z ),  value );
    }



    /**
    * @param i Одномерная координата.
    *
    * @see ic()
    */
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




    /**
    * @return Содержимое указанной ячейки.
    *//* - @todo ...
    virtual T value( std::size_t i ) const = 0;

    virtual T value( const coordInt_t& c ) const = 0;

    virtual T value( int x, int y, int z ) const = 0;
    */



    /**
    * @return Содержимое указанной ячейки - не пустое.
    */
    virtual bool test( std::size_t i ) const = 0;

    virtual bool test( const coordInt_t& c ) const = 0;

    virtual bool test( int x, int y, int z ) const = 0;




    /**
    * @return Количество не пустых данных.
    */
    virtual std::size_t count() const = 0;



    /**
    * @return Карта не содержит данных (все ячейки - пустые).
    */
    inline bool empty() const {
        return (count() == 0);
    }

};





/**
* То же, что StaticMapContent3D, но в виде куба.
*/
template< typename T, std::size_t S >
class CubeMapContent3D :
    public MapContent3D< T, S, S, S > {
};




} // typelib
