#pragma once

#include "../configure.h"
#include "constant.h"


/**
* Функции для вычисления геометрических величин.
*/
namespace typelib {
    namespace compute {
        namespace geometry {


#ifdef LOW_PRECISION_COMPUTE_TYPELIB
    typedef float   real_t;
#else
    typedef double  real_t;
#endif


        } // geometry
    } // compute
} // typelib








/**
* Функции для вычисления значений эллипосида.
*/
namespace typelib {
    namespace compute {
        namespace geometry {
            namespace ellipsoid {


/**
* @return Объём эллипсоида.
*/
static real_t volume( real_t ra,  real_t rb,  real_t rc );




/**
* @return Один из радиусов эллипсоида по известному объёму.
*/
static real_t radiusByVolume( real_t volume, real_t ra,  real_t rb );


            } // ellipsoid
        } // geometry
    } // compute
} // typelib







#include "geometry-compute.inl"
