#pragma once

#include "configure.h"


namespace arkanoid {


class ManagerSound;


/**
* Объект, зарегистрированный в движке звуков.
*
* @see ManagerSound
*/
class SIncarnate {
protected:
    SIncarnate();


    virtual ~SIncarnate();




public:
    /**
    * Играет для элемента звук из заданного файла.
    *
    * @see ManagerSound::play()
    */
    virtual void play(
        const std::string& file,
        float volume = 1.0f,
        bool loop = false
    ) const;


    inline void playNotEmpty(
        const std::string& file,
        float volume = 1.0f,
        bool loop = false
    ) const {
        if ( !file.empty() ) {
            play( file, volume, loop );
        }
    }




    /**
    * Останавливает проигрывание всех звуков.
    *
    * @see ManagerSound::play()
    *
    * @param clear  Освободить память от загруженных звуков.
    */
    static void stop( bool clear );




protected:
    static std::unique_ptr< ManagerSound >  mManagerSound;
};



} // arkanoid
