#include "../include/stdafx.h"
#include "../include/Platform.h"
#include "../include/World.h"


namespace arkanoid {


Platform::Platform(
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
        coord /*- static_cast< typelib::coord2_t >( needVisualSize / 2 )*/,
        rotation,
        momentInertia,
        std::move( material )
    ),

    mDestination( coord /*- static_cast< typelib::coord2_t >( needVisualSize / 2 )*/ )
{
}




Platform::~Platform() {
}




void
Platform::applyForceAndTorque() {

    //CONSOLE << NDIncarnate::coord() << std::endl;

    NDIncarnate::applyForceAndTorque();
}





void
Platform::setTransform( const dgMatrix& matrix ) {
    // # Координата Y платформы не меняется.
    auto ndc = NDIncarnate::coord();
    NDIncarnate::coord( ndc.x,  static_cast< float >( visualCoord().y ) );
    visualCoord().x = static_cast< int >( ndc.x );
}





void
Platform::contactProcess(
    NDIncarnate*        other,
    const NewtonJoint*  contactJoint
) {
}








CapsulePlatform::CapsulePlatform(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    const typelib::size2Int_t&  size,
    const typelib::coord2_t&    coord,
    const typelib::coord2_t&    rotation
) :
    Platform(
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
        MASS_CAPSULE_PLATFORM,
        coord,
        rotation,
        // @see http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BC%D0%BE%D0%BC%D0%B5%D0%BD%D1%82%D0%BE%D0%B2_%D0%B8%D0%BD%D0%B5%D1%80%D1%86%D0%B8%D0%B8
        /* - @todo Сделать капсулу. Сейчас - Box.
        typelib::vector2_t(
            static_cast< float >( radius * radius ) / 2.0f,
            static_cast< float >( 3 * radius * radius + height * height ) / 12
        ) * MASS_CAPSULE_PLATFORM
        */
        typelib::vector2_t::ZERO()
    )
{
    ASSERT( ((size.x > 0) && (size.y > 0))
        && "Размер платформы должен быть указан." );
}




CapsulePlatform::~CapsulePlatform() {
}


} // arkanoid
