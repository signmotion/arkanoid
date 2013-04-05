#pragma once

#include "../configure.h"
#include "constant.h"


/**
* ������� ��� ���������� �������������� �������.
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
* ������� ��� ���������� �������� ����������.
*/
namespace typelib {
    namespace compute {
        namespace geometry {
            namespace ellipsoid {


/**
* @return ����� ����������.
*/
static real_t volume( real_t ra,  real_t rb,  real_t rc );




/**
* @return ���� �� �������� ���������� �� ���������� ������.
*/
static real_t radiusByVolume( real_t volume, real_t ra,  real_t rb );


            } // ellipsoid
        } // geometry
    } // compute
} // typelib







#include "geometry-compute.inl"
