#pragma once

#include "../other.h"
#include "FilterMap.h"
#include "BitMap.h"


namespace typelib {


/**
* Фильтр для MapContent3D.
* Инвертирует карту содержания.
*
* @template См. MapContent3D.
*/
class InverseFilterMap : public FilterMap {
public:

    template< std::size_t SX, std::size_t SY, std::size_t SZ >
    inline void operator()( BitMap< SX, SY, SZ >&  bm ) const {

#ifdef _DEBUG
        std::cout << "InverseFilterMap Count before: " << bm.count() << std::endl;
#endif

        bm.flip();

#ifdef _DEBUG
        std::cout << "InverseFilterMap Count after: " << bm.count() << std::endl;
#endif
    }


};



} // typelib
