#pragma once

#include "configure.h"
#include "NDIncarnate.h"
#include "PPIncarnate.h"


namespace arkanoid {


class Container :
    public PPIncarnate,
    public NDIncarnate
{
public:
    Container(
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


    virtual ~Container();




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
* Контейнер в форме куба.
*/
class CubeContainer :
    public Container
{
public:
    CubeContainer(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      side,
        const typelib::coord2_t&    coord,
        const typelib::coord2_t&    rotation
    );


    virtual ~CubeContainer();
};








/**
* Контейнер в форме сферы.
*/
class SphereContainer :
    public Container
{
public:
    SphereContainer(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      radius,
        const typelib::coord2_t&    coord,
        const typelib::coord2_t&    rotation
    );


    virtual ~SphereContainer();
};


} // arkanoid
