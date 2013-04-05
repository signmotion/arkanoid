#pragma once

#include "configure.h"
#include "NDIncarnate.h"
#include "PPIncarnate.h"


namespace arkanoid {


class Border :
    public PPIncarnate,
    public NDIncarnate
{
public:
    Border(
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


    virtual ~Border();




    /**
    * @virtual NDIncarnate
    */
    virtual void applyForceAndTorque();

    virtual void setTransform( const dgMatrix&  matrix );

    virtual void contactProcess(
        NDIncarnate*        other,
        const NewtonJoint*  contactJoint
    );

};








/**
* Граница в форме кубоида.
*/
class BoxBorder :
    public Border
{
public:
    BoxBorder(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::size2Int_t&  size,
        const typelib::coord2_t&    coord,
        const typelib::coord2_t&    rotation
    );


    virtual ~BoxBorder();
};


} // arkanoid
