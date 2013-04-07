#pragma once

#include "configure.h"
#include "PPIncarnate.h"


namespace arkanoid {


/**
* # Сообщения - что хотим рассказать / показать игроку.
*/
class Message :
    public PPIncarnate
{
public:
    /**
    * Если координаты не указаны, сообщение будет выведено по центру окна.
    */
    Message(
        const std::string&        sprite,
        const typelib::coord2_t&  coord = typelib::coord2_t::ZERO()
    );


    virtual ~Message();
};


} // arkanoid
