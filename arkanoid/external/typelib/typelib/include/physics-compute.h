#pragma once

#include "../configure.h"
#include "constant.h"
#include "vector.h"


/**
* ������� ��� ���������� ���������� �������.
*/
namespace typelib {
    namespace compute {
        namespace physics {


#ifdef LOW_PRECISION_COMPUTE_TYPELIB
    typedef float   real_t;
#else
    typedef double  real_t;
#endif


/**
* @return ������ ����������� ��������.
*
* @source http://en.wikipedia.org/wiki/Orbital_speed
*/
static real_t orbitalSpeed(
    real_t massOrbitBody,
    real_t massCenterBody,
    real_t distance
);




/**
* @return �������� ���� ��� ����� ������������.
*         ������, ��������� ������� ����.
*
* @source http://en.wikipedia.org/wiki/Elastic_collision#One-dimensional_Newtonian
*/
static std::pair< real_t, real_t >  speedElasticCollision(
    real_t massA,  real_t speedA,
    real_t massB,  real_t speedB
);


static std::pair< VectorT< real_t >,  VectorT< real_t > >
speedElasticCollision(
    real_t massA,  const VectorT< real_t >&  speedA,
    real_t massB,  const VectorT< real_t >&  speedB
);




/**
* @return �������� ���� ��� ����� ������������.
*         ������, ��������� ��������� ����.
*
* @source http://en.wikipedia.org/wiki/Inelastic_collision
*/
static real_t speedInelasticCollision(
    real_t massA,  real_t speedA,
    real_t massB,  real_t speedB
);


static VectorT< real_t >  speedInelasticCollision(
    real_t massA,  const VectorT< real_t >&  speedA,
    real_t massB,  const VectorT< real_t >&  speedB
);




/**
* @return �������� ���� ��� ����� ������������.
*         ������, � ��������� ������������ ��������������.
*
* @param COR (����. �� Coefficient of restitution)
*        ��� == 1, ��������� ������� ����.
*        ���  < 1, ��������� ����.
*        ��� == 0, ��������� ��������� ����.
*
* @source http://en.wikipedia.org/wiki/Inelastic_collision
*/
static std::pair< real_t, real_t >  speedCollision(
    real_t massA,  real_t speedA,
    real_t massB,  real_t speedB,
    real_t COR
);


static std::pair< VectorT< real_t >,  VectorT< real_t > >
speedCollision(
    real_t massA,  const VectorT< real_t >&  speedA,
    real_t massB,  const VectorT< real_t >&  speedB,
    real_t COR
);




/**
* @return �� ������� �������� ��������� ����������� ����.
*/
static real_t deltaTemperature(
    real_t q,  real_t mass,  real_t heatCapacity
);




/**
* @return ���������� ���� � ����������� �� ����������� �����������.
*/
static real_t luminosity(
    real_t radius,  real_t temperature
);




/**
* @return RGB-���� � ����������� �� ����������� �����������.
*
* @source http://en.wikipedia.org/wiki/Color_temperature
*//* - @todo
static color_t color( real_t temperature );
*/




/**
* @return ����������� ����������� ��� ��������� ����.
*
* @param luminosity  ���������� ������.
* @param distance  ���������� ���� �� ������.
* @param albedo  �������������� ������� ����.
*
* @source http://en.wikipedia.org/wiki/Effective_temperature
*
* @see luminosity()
*/
static real_t effectiveTemperature(
    real_t luminosity,  real_t distance,  real_t albedo
);


        } // physics
    } // compute
} // typelib







#include "physics-compute.inl"
