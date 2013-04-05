#include "../include/stdafx.h"
#include "../include/Border.h"
#include "../include/World.h"


namespace arkanoid {


Border::Border(
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




Border::~Border() {
}




void
Border::applyForceAndTorque() {
    NDIncarnate::applyForceAndTorque();
}




void
Border::setTransform( const dgMatrix& matrix ) {
    // # Неподвижен.
}





void
Border::contactProcess(
    NDIncarnate*        other,
    const NewtonJoint*  contactJoint
) {
}








BoxBorder::BoxBorder(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    const typelib::size2Int_t&  size,
    const typelib::coord2_t&    coord,
    const typelib::coord2_t&    rotation
) :
    Border(
        world,
        sprite,
        needVisualSize,
        NewtonCreateBox(
            world->physics().get(),
            static_cast< float >( size.x ),
            static_cast< float >( size.x ),
            static_cast< float >( size.y ),
            0, nullptr
        ),
        0,
        coord,
        rotation,
        typelib::vector2_t::ZERO()
    )
{
    ASSERT( ( (size.x > 0) && (size.y > 0) )
        && "Размер должен быть указан." );
}




BoxBorder::~BoxBorder() {
}


} // arkanoid
