#pragma once

#include "../other.h"
#include "FilterMap.h"
#include "BitMap.h"


namespace typelib {


/**
* ‘ильтр дл€ MapContent3D.
* ќставл€ет только внешний контур карты содержани€.
*
* @template saveBorder ќставл€ть €чейки на границе без изменений.
*/
template< bool saveBorder >
class OutlineFilterMap : public FilterMap {
public:

    template< std::size_t SX, std::size_t SY, std::size_t SZ >
    inline void operator()( BitMap< SX, SY, SZ >&  bm ) const {

        typedef BitMap< SX, SY, SZ >  bm_t;

#ifdef _DEBUG
        std::cout << typeid( *this ).name() << " Count before: " << bm.count() << std::endl;
#endif

        const BitMap< SX, SY, SZ >  copy( bm );
        for (int z = bm_t::minCoord().z; z <= bm_t::maxCoord().z; ++z) {
            for (int y = bm_t::minCoord().y; y <= bm_t::maxCoord().y; ++y) {
                for (int x = bm_t::minCoord().x; x <= bm_t::maxCoord().x; ++x) {

                    const typelib::coordInt_t c( x, y, z );
                    const std::size_t i = bm.ic( x, y, z );
                    if ( !copy.test( i ) ) {
                        // погашенные - не интересуют
                        continue;
                    }
                    if ( copy.border( c ) && saveBorder ) {
                        // на границе - не трогаем
                        continue;
                    }

                    if ( copy.all26Filled( c, true ) ) {
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
