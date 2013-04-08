#pragma once

#include "configure.h"


namespace arkanoid {


/**
* ��������� ������� ����.
* # � �������� ��������� ������ ������������ irrKlang.
*
* @see http://ambiera.com/irrklang
*/
class ManagerSound {
public:
    /**
    * ��������� ��������� �����.
    *
    * # ���� ������� �� ������ �����.
    */
    typedef std::string  pathSound_t;
    typedef std::unordered_map<
        pathSound_t,
        // # �� ���������� ��������� irrKlang.
        irrklang::ISoundSource*
    > knownSound_t;




public:
    ManagerSound();




    virtual ~ManagerSound();




    /**
    * ������ ���� �� ��������� �����.
    *
    * @param volume  ��������� � ��������� [ 0.0; 1.0 ].
    * @param loop    ���� ����� ����������� ����������.
    */
    void play(
        const pathSound_t&,
        float volume = 1.0f,
        bool loop = false
    );




    /**
    * ������������� ������������ ���� ������.
    *
    * @param clear  ���������� ������ �� ����������� ������.
    */
    void stop( bool clear );




    /**
    * @return �������� ����� ��� nullptr, ���� ���� ��������� �� �������.
    */
    irrklang::ISoundSource* sound( const pathSound_t& );




private:
    /**
    * ��������� ����.
    */
    irrklang::ISoundSource* loadSound( const pathSound_t& );




private:
    std::unique_ptr< irrklang::ISoundEngine>  mEngine;

    knownSound_t  mKnownSound;
};


} // arkanoid
