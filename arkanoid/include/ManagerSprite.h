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
        const pathSprite_t&,
        const typelib::size2Int_t&  needVisualSize = typelib::size2Int_t::ZERO()
    );




    /**
    * @return Размер спрайта или (0, 0), если спрайт не найден.
    */
    typelib::size2Int_t sizeSprite( const pathSprite_t& ) const;




private:
    /**
    * Загружает спрайт.
    */
    prcore::Bitmap* loadSprite(
        const pathSprite_t&,
        const typelib::size2Int_t&  needVisualSize = typelib::size2Int_t::ZERO()
    );




private:
    knownSprite_t  mKnownSprite;
};


} // arkanoid
