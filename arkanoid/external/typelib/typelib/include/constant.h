#pragma once

#include "../configure.h"


/**
* ���������.
*
* @see ���������� ��������� ����.
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
* ����� ��.
*/
const auto pi = static_cast< real_t >( 3.14159265358979323846 );


    } // constant
} // typelib








/**
* ���������� ���������.
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
* �������� � ��������.
*/
const auto CK = static_cast< real_t >( -273.15 );
           


            
/**
* �������� ����� � �������, �/�.
*/
const auto c = static_cast< real_t >( 299792458 );




/**
* �������������� ����������, ��/�/�^2.
*/
const auto G = static_cast< real_t >( 6.67428E-11 );




/**
* ����������� �����, ��.
*/
const auto mp = static_cast< real_t >( 2.17644E-8 );


/**
* ����������� �����, �.
*/
const auto lp = static_cast< real_t >( 1.616252E-35 );




/**
* ����������� �����, �.
*/
const auto tp = static_cast< real_t >( 5.39124E-44 );




/**
* ����������� �����������, �.
*/
const auto Tp = static_cast< real_t >( 1.416785E+32 );




/**
* ���������� ������� � ���������.
*/
const auto stefanBoltzmann = static_cast< real_t >( 5.670373E-8 );




// @todo extend �������� ������ ���������.


        } // physics
    } // constant
} // typelib
