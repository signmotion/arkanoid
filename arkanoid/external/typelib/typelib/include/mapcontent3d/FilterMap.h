#pragma once

#include "../../configure.h"


namespace typelib {


/**
* Фильтр для MapContent3D. Представляет собой функтор для изменения
* карты содержания.
*
* @see MapContent3D
*/
class FilterMap {
public:
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< FilterMap >  Ptr;
    typedef std::unique_ptr< FilterMap >  UPtr;



public:
    /* - Нет. Каждый фильтр определяет свой собcтвенный operator().
    template< std::size_t SX, std::size_t SY, std::size_t SZ >
    inline void operator()( BitMap< SX, SY, SZ >&  bm ) const {
        throw "operator() require implementation in the child's class";
    }
    */

};


} // typelib
