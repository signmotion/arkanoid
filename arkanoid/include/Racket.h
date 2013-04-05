#pragma once

#include "configure.h"
#include "NDIncarnate.h"
#include "PPIncarnate.h"


namespace arkanoid {


class Racket :
    public PPIncarnate,
    public NDIncarnate
{
public:
    Racket(
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


    virtual ~Racket();




    inline void pushRacket( const typelib::vector2_t&  force ) {
        applyAddForce( force );
    }




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
* Ракетка в форме сферы.
*/
class SphereRacket :
    public Racket
{
public:
    SphereRacket(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      radius,
        const typelib::coord2_t&    coord,
        const typelib::coord2_t&    rotation
    );


    virtual ~SphereRacket();
};


} // arkanoid
