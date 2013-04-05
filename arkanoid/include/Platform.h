#pragma once

#include "configure.h"
#include "NDIncarnate.h"
#include "PPIncarnate.h"


namespace arkanoid {


class Platform :
    public PPIncarnate,
    public NDIncarnate
{
public:
    Platform(
        std::shared_ptr< World >,
        const std::string&           sprite,
        const typelib::size2Int_t&   needVisualSize,
        NewtonCollision*             collision,
        float                        mass,
        const typelib::coord2_t&     coord,
        const typelib::coord2_t&     rotation,
        const typelib::vector2_t&    momentInertia,
        std::unique_ptr< Material > =
            std::move( Material::valueOf() )
    );


    virtual ~Platform();




    /**
    * @virtual NDIncarnate
    */
    virtual void applyForceAndTorque();

    virtual void setTransform( const dgMatrix&  matrix );

    virtual void contactProcess(
        NDIncarnate*        other,
        const NewtonJoint*  contactJoint
    );




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
        const typelib::coord2_t&    coord,
        const typelib::coord2_t&    rotation
    );


    virtual ~CapsulePlatform();
};


} // arkanoid
