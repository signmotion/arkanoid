#pragma once


#include "configure.h"


namespace arkanoid {


class World;

    
class Level {
public:
    typedef char  sign_t;


    struct AboutPlatform {
        std::string  kind;
        std::string  sprite;
    };


    struct AboutRacket {
        std::string  kind;
        std::string  sprite;
    };


    struct AboutContainer {
        std::string  kind;
        std::string  sprite;
        sign_t       next;
    };


    typedef std::map< sign_t, AboutContainer >  aboutContainerSign_t;


    // # Воспользуемся тем, что ряд контейнеров представлен в виде строки.
    typedef std::string  row_t;
    typedef std::vector< row_t >  containerMap_t;




public:
    /**
    * Номер уровня.
    */
    const size_t  current;




public:
    Level( size_t current );


    virtual ~Level();




private:
    /**
    * @see Комм. в media/1.level
    */
    AboutPlatform         mAboutPlatform;
    AboutRacket           mAboutRacket;
    typelib::size2Int_t   mCell;
    aboutContainerSign_t  mAboutContainerSign;
    containerMap_t        mContainerMap;


    friend World;
};


} // arkanoid
