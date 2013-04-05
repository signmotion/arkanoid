#pragma once

#include "configure.h"


namespace arkanoid {


/**
* ��������� ��������� ����.
*/
class ManagerSprite {
public:
    /**
    * ��������� ��������� �������.
    *
    * # ������ ������� �� ������ ������������ ������.
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
    * @return ������ ��� nullptr, ���� ������ ��������� �� �������.
    */
    prcore::Bitmap* sprite(
        const typelib::size2Int_t&  needVisualSize,
        const pathSprite_t&
    );




private:
    /**
    * ��������� ������.
    */
    prcore::Bitmap* loadSprite(
        const typelib::size2Int_t&  needVisualSize,
        const pathSprite_t&
    );




private:
    knownSprite_t  mKnownSprite;
};


} // arkanoid
