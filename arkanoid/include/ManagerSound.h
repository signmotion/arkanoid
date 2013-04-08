#pragma once

#include "configure.h"


namespace arkanoid {


/**
* Управляет звуками игры.
* # В качестве звукового движка используется irrKlang.
*
* @see http://ambiera.com/irrklang
*/
class ManagerSound {
public:
    /**
    * Известные менеджеру звуки.
    *
    * # Звук состоит из одного файла.
    */
    typedef std::string  pathSound_t;
    typedef std::unordered_map<
        pathSound_t,
        // # Об указателях заботится irrKlang.
        irrklang::ISoundSource*
    > knownSound_t;




public:
    ManagerSound();




    virtual ~ManagerSound();




    /**
    * Играет звук из заданного файла.
    *
    * @param volume  Громкость в диапазоне [ 0.0; 1.0 ].
    * @param loop    Звук будет повторяться бесконечно.
    */
    void play(
        const pathSound_t&,
        float volume = 1.0f,
        bool loop = false
    );




    /**
    * Останавливает проигрывание всех звуков.
    *
    * @param clear  Освободить память от загруженных звуков.
    */
    void stop( bool clear );




    /**
    * @return Источник звука или nullptr, если звук загрузить на удалось.
    */
    irrklang::ISoundSource* sound( const pathSound_t& );




private:
    /**
    * Загружает звук.
    */
    irrklang::ISoundSource* loadSound( const pathSound_t& );




private:
    std::unique_ptr< irrklang::ISoundEngine>  mEngine;

    knownSound_t  mKnownSound;
};


} // arkanoid
