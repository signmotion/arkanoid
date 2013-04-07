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
        const pathSprite_t&,
        const typelib::size2Int_t&  needVisualSize = typelib::size2Int_t::ZERO()
    );




    /**
    * @return ������ ������� ��� (0, 0), ���� ������ �� ������.
    */
    typelib::size2Int_t sizeSprite( const pathSprite_t& ) const;




private:
    /**
    * ��������� ������.
    */
    prcore::Bitmap* loadSprite(
        const pathSprite_t&,
        const typelib::size2Int_t&  needVisualSize = typelib::size2Int_t::ZERO()
    );




private:
    knownSprite_t  mKnownSprite;
};


} // arkanoid
