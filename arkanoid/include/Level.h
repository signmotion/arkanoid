#pragma once


#include "configure.h"


namespace arkanoid {


class World;

    
class Level {
public:
    typedef char  sign_t;


    struct AboutBackground {
        std::string  sprite;
    };


    struct AboutPlatform {
        std::string  kind;
        std::string  sprite;
    };


    struct AboutRacket {
        std::string  kind;
        std::string  sprite;
    };


    struct AboutSet {
        std::string  kind;
        std::string  sprite;
        sign_t       next;
    };


    typedef std::map< sign_t, AboutSet >  aboutSetSign_t;


    // # ������������� ���, ��� ������ ��� ����� ����������� � ���� ������.
    typedef std::string  row_t;
    typedef std::vector< row_t >  map_t;




public:
    /**
    * ����� ������.
    */
    const size_t  current;




public:
    Level( size_t current );


    virtual ~Level();




    /**
    * @return ���� ������� � �������� �������.
    */
    static bool has( size_t level );




private:
    /**
    * @see ����. � media/1.level
    */
    AboutBackground      mAboutBackground;
    AboutPlatform        mAboutPlatform;
    AboutRacket          mAboutRacket;
    typelib::size2Int_t  mCell;
    aboutSetSign_t       mAboutSetSign;
    map_t                mMap;


    friend World;
};


} // arkanoid
