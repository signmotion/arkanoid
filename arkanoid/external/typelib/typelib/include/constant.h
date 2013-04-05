#pragma once

#include "../configure.h"


/**
* Константы.
*
* @see Физические константы ниже.
* @see compute.h
*/
namespace typelib {
    namespace constant {


#ifdef LOW_PRECISION_CONSTANT_TYPELIB
    typedef float   real_t;
#else
    typedef double  real_t;
#endif


/**
* Число Пи.
*/
const auto pi = static_cast< real_t >( 3.14159265358979323846 );


    } // constant
} // typelib








/**
* Физические константы.
*
* @see http://en.wikipedia.org/wiki/Physical_constant
* @see compute.h
*/
namespace typelib {
    namespace constant {
        namespace physics {


#ifdef LOW_PRECISION_CONSTANT_TYPELIB
    typedef float   real_t;
#else
    typedef double  real_t;
#endif


/**
* Цельсиев в Кельвине.
*/
const auto CK = static_cast< real_t >( -273.15 );
           


            
/**
* Скорость света в вакууме, м/с.
*/
const auto c = static_cast< real_t >( 299792458 );




/**
* Гравитационная постоянная, кг/м/с^2.
*/
const auto G = static_cast< real_t >( 6.67428E-11 );




/**
* Планковская масса, кг.
*/
const auto mp = static_cast< real_t >( 2.17644E-8 );


/**
* Планковская длина, м.
*/
const auto lp = static_cast< real_t >( 1.616252E-35 );




/**
* Планковское время, с.
*/
const auto tp = static_cast< real_t >( 5.39124E-44 );




/**
* Планковская температура, К.
*/
const auto Tp = static_cast< real_t >( 1.416785E+32 );




/**
* Постоянная Стефана — Больцмана.
*/
const auto stefanBoltzmann = static_cast< real_t >( 5.670373E-8 );




// @todo extend Добавить другие константы.


        } // physics
    } // constant
} // typelib
