#include "../include/stdafx.h"
#include "../include/Remains.h"


namespace arkanoid {


Remains::Remains(
    const std::string&           sprite,
    const typelib::size2Int_t&   needVisualSize,
    const typelib::coord2_t&     coord
) :
    PPIncarnate( sprite, coord, needVisualSize )
{
}




Remains::~Remains() {
}




std::unique_ptr< Remains >
Remains::valueOf(
    const AboutSet&             about,
    const typelib::size2Int_t&  needVisualSize,
    const typelib::coord2_t&    coord
) {
    if (about.kind == "Remains") {
        return std::unique_ptr< Remains >( new Remains(
            about.sprite,
            needVisualSize,
            coord
        ) );
    }

    // подходящие останки не могут быть созданы
    return std::unique_ptr< Remains >();
}


} // arkanoid
