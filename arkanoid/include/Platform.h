#pragma once

#include "configure.h"
#include "B2DIncarnate.h"
#include "PPIncarnate.h"


namespace arkanoid {


class Platform :
    public PPIncarnate,
    public B2DIncarnate
{
public:
    Platform(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        const polygon_t&            polygon,
        float                       density,
        const typelib::coord2_t&    coord
    );


    virtual ~Platform();




    /**
    * @virtual B2DIncarnate
    */
    virtual void sync();




    /**
    * @virtual PPIncarnate
    */
    virtual void draw( prcore::Bitmap& context ) const;




private:
    /**
    * Где должна находиться платформа (желание игрока).
    */
    typelib::coord2Int_t  mDestination;




    friend World;
};








/**
* Платформа в форме капсулы.
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
        const typelib::coord2_t&    coord
    );


    virtual ~CapsulePlatform();
};


} // arkanoid
