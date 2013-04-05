#include "../include/stdafx.h"
#include "../include/Racket.h"
#include "../include/World.h"


namespace arkanoid {


Racket::Racket(
    std::shared_ptr< World >     world,
    const std::string&           sprite,
    const typelib::size2Int_t&   needVisualSize,
    NewtonCollision*             collision,
    float                        mass,
    const typelib::coord2_t&     coord,
    const typelib::coord2_t&     rotation,
    const typelib::vector2_t&    momentInertia,
    std::unique_ptr< Material >  material
) :
    PPIncarnate(
        coord,
        sprite,
        needVisualSize
    ),
    NDIncarnate(
        world,
        collision,
        mass,
        coord,
        rotation,
        momentInertia,
        std::move( material )
    )
{
}




Racket::~Racket() {
}




void
Racket::applyForceAndTorque() {
    NDIncarnate::applyForceAndTorque();
}





void
Racket::setTransform( const dgMatrix& matrix ) {
    auto ndc = NDIncarnate::coord();
    visualCoord( ndc.x, ndc.y );
}





void
Racket::contactProcess(
    NDIncarnate*        other,
    const NewtonJoint*  contactJoint
) {
}








SphereRacket::SphereRacket(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      radius,
    const typelib::coord2_t&    coord,
    const typelib::coord2_t&    rotation
) :
    Racket(
        world,
        sprite,
        needVisualSize,
        NewtonCreateSphere(
            world->physics().get(),
            static_cast< float >( radius ),
            static_cast< float >( radius ),
            static_cast< float >( radius ),
            0, nullptr
        ),
        MASS_SPHERE_RACKET,
        coord,
        rotation,
        // @see http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BC%D0%BE%D0%BC%D0%B5%D0%BD%D1%82%D0%BE%D0%B2_%D0%B8%D0%BD%D0%B5%D1%80%D1%86%D0%B8%D0%B8
        typelib::vector2_t( MASS_SPHERE_RACKET, MASS_SPHERE_RACKET ) *
            2 * radius * radius / 5
    )
{
    ASSERT( (radius > 0)
        && "Радиус должен быть указан." );
}




SphereRacket::~SphereRacket() {
}


} // arkanoid
