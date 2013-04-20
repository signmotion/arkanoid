#include "../include/stdafx.h"
#include "../include/Remains.h"


namespace arkanoid {


Remains::Remains(
    const std::string&           sprite,
    const typelib::size2Int_t&   needVisualSize,
    const typelib::coord2_t&     coord,
    const AboutRemains&          about
) :
    VIncarnate( sprite, coord, needVisualSize ),
    about( about )
{
}




Remains::~Remains() {
}




std::unique_ptr< Remains >
Remains::valueOf(
    const AboutRemains&         about,
    const typelib::size2Int_t&  needVisualSize,
    const typelib::coord2_t&    coord
) {
    if (about.kind == "Remains") {
        return std::unique_ptr< Remains >( new Remains(
            about.sprite,
            needVisualSize,
            coord,
            about
        ) );
    }

    // подходящие останки не могут быть созданы
    return std::unique_ptr< Remains >();
}


} // arkanoid
