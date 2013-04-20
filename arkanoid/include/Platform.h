#pragma once

#include "configure.h"
#include "structure.h"
#include "PIncarnate.h"
#include "VIncarnate.h"
#include "SIncarnate.h"


namespace arkanoid {


class Platform :
    public VIncarnate,
    public PIncarnate,
    public SIncarnate
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
    * @virtual PIncarnate
    */
    virtual void sync();
    virtual void selfReaction( const std::string& event );
    virtual void collisionReaction( const GE* );




    /**
    * @virtual VIncarnate
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
