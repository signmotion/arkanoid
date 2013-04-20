#pragma once

#include "configure.h"


namespace arkanoid {


class ManagerSound;


/**
* ������, ������������������ � ������ ������.
*
* @see ManagerSound
*/
class SIncarnate {
protected:
    SIncarnate();


    virtual ~SIncarnate();




public:
    /**
    * ������ ��� �������� ���� �� ��������� �����.
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
    * ������������� ������������ ���� ������.
    *
    * @see ManagerSound::play()
    *
    * @param clear  ���������� ������ �� ����������� ������.
    */
    static void stop( bool clear );




protected:
    static std::unique_ptr< ManagerSound >  mManagerSound;
};



} // arkanoid
