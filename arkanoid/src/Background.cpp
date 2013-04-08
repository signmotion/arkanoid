#include "../include/stdafx.h"
#include "../include/Background.h"


namespace arkanoid {


Background::Background(
    const std::string&           sprite,
    const typelib::size2Int_t&   needVisualSize,
    const typelib::coord2_t&     coord,
    const AboutBackground&       about
) :
    PPIncarnate( sprite, coord, needVisualSize ),
    about( about )
{
    // включаем фоновую музыку
    playNotEmpty( about.load.sound, 0.5f, true );
}




Background::~Background() {
}


} // arkanoid
