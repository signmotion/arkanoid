#include "../include/stdafx.h"
#include "../include/Background.h"


namespace arkanoid {


Background::Background(
    const std::string&           sprite,
    const typelib::size2Int_t&   needVisualSize,
    const typelib::coord2_t&     coord
) :
    PPIncarnate(
        coord,
        sprite,
        needVisualSize
    )
{
}




Background::~Background() {
}


} // arkanoid
