#pragma once

#include "configure.h"
#include "structure.h"
#include "B2DIncarnate.h"
#include "PPIncarnate.h"
#include "IRRKIncarnate.h"


namespace arkanoid {


class Platform :
    public PPIncarnate,
    public B2DIncarnate,
    public IRRKIncarnate
{
public:
    /**
    * ���������� � ���������, ���������� �� ����� ���������� ������.
    *
    * @todo fine ��������� �����������: ������ ����� ���� �����������.
    */
    const AboutPlatform  about;




public:
    Platform(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        const polygon_t&            polygon,
        float                       density,
        const typelib::coord2_t&    coord,
        const AboutPlatform&
    );


    virtual ~Platform();




    /**
    * @virtual B2DIncarnate
    */
    virtual void sync();
    virtual void selfReaction( const std::string& event );
    virtual void collisionReaction( const GE* );




    /**
    * @virtual PPIncarnate
    */
    virtual void draw( prcore::Bitmap& context ) const;




private:
    /**
    * ��� ������ ���������� ��������� (������� ������).
    */
    typelib::coord2Int_t  mDestination;




    friend World;
};








/**
* ��������� � ����� �������.
*/
class CapsulePlatform :
    public Platform
{
public:
    CapsulePlatform(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::size2Int_t&  size,
        const typelib::coord2_t&    coord,
        const AboutPlatform&
    );


    virtual ~CapsulePlatform();
};


} // arkanoid
