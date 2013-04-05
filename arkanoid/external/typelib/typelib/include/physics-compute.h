#pragma once

#include "../configure.h"
#include "constant.h"
#include "vector.h"


/**
* Функции для вычисления физических величин.
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
* @return Первая космическая скорость.
*
* @source http://en.wikipedia.org/wiki/Orbital_speed
*/
static real_t orbitalSpeed(
    real_t massOrbitBody,
    real_t massCenterBody,
    real_t distance
);




/**
* @return Скорости двух тел после столкновения.
*         Прямой, абсолютно упругий удар.
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
* @return Скорость двух тел после столкновения.
*         Прямой, абсолютно неупругий удар.
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
* @return Скорости двух тел после столкновения.
*         Прямой, с указанием коэффициента восстановления.
*
* @param COR (сокр. от Coefficient of restitution)
*        При == 1, абсолютно упругий удар.
*        При  < 1, неупругий удар.
*        При == 0, абсолютно неупругий удар.
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
* @return На сколько градусов изменится температура тела.
*/
static real_t deltaTemperature(
    real_t q,  real_t mass,  real_t heatCapacity
);




/**
* @return Светимость тела в зависимости от температуры поверхности.
*/
static real_t luminosity(
    real_t radius,  real_t temperature
);




/**
* @return RGB-цвет в зависимости от температуры поверхности.
*
* @source http://en.wikipedia.org/wiki/Color_temperature
*//* - @todo
static color_t color( real_t temperature );
*/




/**
* @return Эффективная температура для небесного тела.
*
* @param luminosity  Светимость звезды.
* @param distance  Расстояние тела от звезды.
* @param albedo  Геометрическое альбедо тела.
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
