#pragma once

#include "configure.h"
#include "PPIncarnate.h"


namespace arkanoid {


class Background :
    public PPIncarnate
    // # Фон не является частью физ. мира.
{
public:
    Background(
        const std::string&           sprite,
        const typelib::size2Int_t&   needVisualSize,
        const typelib::coord2_t&     coord
    );


    virtual ~Background();
};


} // arkanoid
