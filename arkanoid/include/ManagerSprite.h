#pragma once

#include "configure.h"


namespace arkanoid {


/**
* Управляет спрайтами игры.
*/
class ManagerSprite {
public:
    /**
    * Известные менеджеру спрайты.
    *
    * # Спрайт состоит из одного неподвижного фрейма.
    */
    typedef std::string  pathSprite_t;
    typedef std::unordered_map<
        pathSprite_t,
        std::unique_ptr< prcore::Bitmap >
    > knownSprite_t;




public:
    ManagerSprite();




    virtual ~ManagerSprite();




    /**
    * @return Спрайт или nullptr, если спрайт загрузить на удалось.
    */
    prcore::Bitmap* sprite(
        const typelib::size2Int_t&  needVisualSize,
        const pathSprite_t&
    );




private:
    /**
    * Загружает спрайт.
    */
    prcore::Bitmap* loadSprite(
        const typelib::size2Int_t&  needVisualSize,
        const pathSprite_t&
    );




private:
    knownSprite_t  mKnownSprite;
};


} // arkanoid
