#include "../include/stdafx.h"
#include "../include/Message.h"


namespace arkanoid {


Message::Message(
    const std::string&        sprite,
    const typelib::coord2_t&  coord
) :
    VIncarnate(
        sprite,
        (coord == typelib::coord2_t::ZERO())
          ? VIncarnate::centerSprite( sprite )
          : coord
    )
{
}




Message::~Message() {
}


} // arkanoid
