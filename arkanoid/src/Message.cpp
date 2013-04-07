#include "../include/stdafx.h"
#include "../include/Message.h"


namespace arkanoid {


Message::Message(
    const std::string&        sprite,
    const typelib::coord2_t&  coord
) :
    PPIncarnate(
        sprite,
        (coord == typelib::coord2_t::ZERO())
          ? PPIncarnate::centerSprite( sprite )
          : coord
    )
{
}




Message::~Message() {
}


} // arkanoid
