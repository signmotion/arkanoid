#pragma once

#include "../other.h"
#include "FilterMap.h"
#include "BitMap.h"


namespace typelib {


/**
* Фильтр для MapContent3D.
* Оставляет на карте содержания только те элементы, рядом с которыми
* не менее NMin и не более NMax соседей включительно.
*
* @template borderState Воспринимать ячейку за границами карты как заполненную.
*
* Примеры фильтра
*   - Оставить элементы, у которых нет соседей
*       typelib::NeightbourFilterMap< 0, 0 >
*   - Оставить элементы, у которых только 1 сосед
*       typelib::NeightbourFilterMap< 1, 1 >
*   - Оставить элементы, у которых не более 4 соседей
*       typelib::NeightbourFilterMap< 0, 4 >
*   - Оставить элементы, которые полностью окружены соседями
*       typelib::NeightbourFilterMap< 26, 26 >
*   - См. также "shape-visualtest".
*/
template< std::size_t NMin, std::size_t NMax, bool borderState >
class NeightbourFilterMap : public FilterMap {
public:

    template< std::size_t SX, std::size_t SY, std::size_t SZ >
    inline void operator()( BitMap< SX, SY, SZ >&  bm ) const {

        typedef BitMap< SX, SY, SZ >  bm_t;

        static_assert( (NMin <= NMax),
            "Диапазон следует задавать в порядке \"меньший-больший\"." );
        static_assert( ( (NMin <= 26) && (NMax <= 26) ),
            "Рядом с ячейкой может находится не более 26 соседей. См. MapContent3D." );


#ifdef _DEBUG
        std::cout << typeid( *this ).name() << " Count before: " << bm.count() << std::endl;
#endif

        const BitMap< SX, SY, SZ >  copy( bm );
        for (int z = bm_t::minCoord().z; z <= bm_t::maxCoord().z; ++z) {
            for (int y = bm_t::minCoord().y; y <= bm_t::maxCoord().y; ++y) {
                for (int x = bm_t::minCoord().x; x <= bm_t::maxCoord().x; ++x) {

                    const typelib::coordInt_t c( x, y, z );
                    const std::size_t i = bm_t::ic( x, y, z );
                    if ( !copy.test( i ) ) {
                        continue;
                    }

                    std::size_t n = 0;
                    for (std::size_t k = 1; k <= 26; ++k) {
                        const bool has = copy.filled( c, k, borderState );
                        if ( has ) {
                            ++n;
                            // тут же можем частично проверить условие,
                            // дабы избежать лишних подсчётов
                            if (n > NMax) {
                                break;
                            }
                        }
                    }
                    if ( !typelib::between( n, NMin, NMax ) ) {
                        bm.reset( i );
                    }

                } // for (int x = 

            } // for (int y = 

        } // for (int z = 

#ifdef _DEBUG
        std::cout << typeid( *this ).name() << " Count after: " << bm.count() << std::endl;
#endif
    }


};



} // typelib
