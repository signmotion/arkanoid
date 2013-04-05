#include "../include/stdafx.h"
#include "../include/Container.h"
#include "../include/World.h"


namespace arkanoid {


Container::Container(
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




Container::~Container() {
}




void
Container::applyForceAndTorque() {

#if 0
    // @test
    auto b = NDIncarnate::body();
    typelib::vector2_t gravity( 0.0f, +10.0f );
    static size_t count = 0;
    if (count < 1000) {
        // подбрасываем выше
        gravity.y = -100.0f;
        // и отклоняем немного в сторону
        static typelib::Random< float >  rg( -100.0f, 100.0f, 0 );
        gravity.x = rg.next();
        ++count;
    }
    float mass, ix, iy, iz;
    NewtonBodyGetMassMatrix( b, &mass, &ix, &iy, &iz );
    const float force[ 4 ] =
        { gravity.x * mass,  0.0f,  gravity.y * mass,  1.0f };
    NewtonBodySetForce( b, force );
#endif

    NDIncarnate::applyForceAndTorque();
}




void
Container::setTransform( const dgMatrix& matrix ) {
    auto ndc = NDIncarnate::coord();
    visualCoord( ndc.x, ndc.y );
}





void
Container::contactProcess(
    NDIncarnate*        other,
    const NewtonJoint*  contactJoint
) {
}








CubeContainer::CubeContainer(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      side,
    const typelib::coord2_t&    coord,
    const typelib::coord2_t&    rotation
) :
    Container(
        world,
        sprite,
        needVisualSize,
        NewtonCreateBox(
            world->physics().get(),
            static_cast< float >( side ),
            static_cast< float >( side ),
            static_cast< float >( side ),
            0, nullptr
        ),
        MASS_CUBE_CONTAINER,
        coord,
        rotation,
        // @see http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BC%D0%BE%D0%BC%D0%B5%D0%BD%D1%82%D0%BE%D0%B2_%D0%B8%D0%BD%D0%B5%D1%80%D1%86%D0%B8%D0%B8
        typelib::vector2_t( MASS_CUBE_CONTAINER, MASS_CUBE_CONTAINER ) *
            side * side / 6
    )
{
    ASSERT( (side > 0)
        && "Размер должен быть указан." );
}




CubeContainer::~CubeContainer() {
}








SphereContainer::SphereContainer(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      radius,
    const typelib::coord2_t&    coord,
    const typelib::coord2_t&    rotation
) :
    Container(
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
        MASS_SPHERE_CONTAINER,
        coord,
        rotation,
        // @see http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BC%D0%BE%D0%BC%D0%B5%D0%BD%D1%82%D0%BE%D0%B2_%D0%B8%D0%BD%D0%B5%D1%80%D1%86%D0%B8%D0%B8
        typelib::vector2_t( MASS_SPHERE_CONTAINER, MASS_SPHERE_CONTAINER ) *
            2 * radius * radius / 5
    )
{
    ASSERT( (radius > 0)
        && "Радиус должен быть указан." );
}




SphereContainer::~SphereContainer() {
}


} // arkanoid
