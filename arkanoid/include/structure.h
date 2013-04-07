#pragma once


// Простые типы, которые не доросли до выделения в отдельный файл / класс.


namespace arkanoid {


/**
* Метка элемента.
* Используется для построения карты уровня.
*/
typedef char  sign_t;




/**
* Структуры для загрузки уровня.
*/
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


} // arkanoid
