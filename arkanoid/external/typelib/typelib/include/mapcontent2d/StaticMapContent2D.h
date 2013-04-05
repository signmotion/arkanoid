#pragma once

#include "../../configure.h"
#include "../mapcontent3d/StaticMapContent3D.h"


namespace typelib {


template< std::size_t SX, std::size_t SY >
class StaticMapContent2D;

template< std::size_t S >
class CubeStaticMapContent2D;

template< std::size_t S >
class CubeSMC2D;


/**
* @see StaticMapContent3D
*
    Нумерация ячеек:
    8   1   5
    4   0   2
    7   3   6
*
* @todo fine Переписать (упрощение, контроль) некоторые методы.
*/
template< std::size_t SX, std::size_t SY >
class StaticMapContent2D :
    public StaticMapContent3D< SX, SY, 1 >
{
};





/**
* @see CubeStaticMapContent3D
*/
template< std::size_t S >
class CubeStaticMapContent2D :
    public StaticMapContent2D< S, S > {
};




/**
* Сокращение для CubeStaticMapContent2D.
*/
template< std::size_t S >
class CubeSMC2D :
    public CubeStaticMapContent2D< S > {
};




} // typelib
