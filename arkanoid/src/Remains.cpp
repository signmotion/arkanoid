#include "../include/stdafx.h"
#include "../include/Remains.h"


namespace arkanoid {


Remains::Remains(
    const std::string&           sprite,
    const typelib::size2Int_t&   needVisualSize,
    const typelib::coord2_t&     coord,
    const typelib::coord2_t&     rotation
) :
    PPIncarnate(
        coord,
        sprite,
        needVisualSize
    )
{
}




Remains::~Remains() {
}


} // arkanoid
