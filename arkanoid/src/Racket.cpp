#include "../include/stdafx.h"
#include "../include/Racket.h"
#include "../include/World.h"


namespace arkanoid {


Racket::Racket(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      radius,
    float                       density,
    const typelib::coord2_t&    coord
) :
    PPIncarnate( sprite, coord, needVisualSize ),
    B2DIncarnate( world )
{
    ASSERT( (radius > 0.0f)
        && "Для ракетки необходимо указать радиус." );
    ASSERT( (density > 0.0f)
        && "Плотность ракетки должна быть указана." );

    b2CircleShape   shape;
    shape.m_radius = static_cast< float >( radius );

    b2FixtureDef fd;
    fd.shape = &shape;
	fd.density = density;
	fd.friction = 0.0f;
    fd.restitution = 1.0f;

	b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.bullet = true;
    // # Координаты задаются в метрах.
    const auto pc = coord;
	bd.position.Set( pc.x, pc.y );

    B2DIncarnate::init( bd, fd );
}




Racket::Racket(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    const polygon_t&            polygon,
    float                       density,
    const typelib::coord2_t&    coord
) :
    PPIncarnate( sprite, coord, needVisualSize ),
    B2DIncarnate( world )
{
    const size_t n = polygon.size();
    {
        ASSERT( (polygon.front() != polygon.back())
            && "Вершины ракетки не должны замыкаться: замыкание построят здесь." );
#ifdef _DEBUG
        //std::unique( polygon.begin(), polygon.end() );
        //ASSERT( (n == polygon.size())
        //    && "Вершины ракетки не должны повторяться." );
#endif
        ASSERT( (n >= 3)
            && "Ракетка должна состоять не менее чем из трёх вершин." );
        ASSERT( (density > 0.0f)
            && "Плотность ракетки должна быть указана." );
    }


    b2PolygonShape shape;
    std::unique_ptr< b2Vec2 >  vertices( new b2Vec2[ n ] );
    for (auto itr = polygon.cbegin(); itr != polygon.cend(); ++itr) {
        const size_t i = std::distance( polygon.cbegin(), itr );
        vertices.get()[ i ].Set( itr->x, itr->y );
    }
    shape.Set( vertices.get(), n );

    b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = density;
	fd.friction = 0.0f;
    fd.restitution = 1.0f;

	b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.bullet = true;
    // # Координаты задаются в метрах.
    const auto pc = coord;
	bd.position.Set( pc.x, pc.y );

    B2DIncarnate::init( bd, fd );
}




Racket::~Racket() {
}




void
Racket::sync() {
    const auto vc = coord();
    visualCoord( vc.x, vc.y );
    const auto a = rotation();
    visualRotation( a );
}








SphereRacket::SphereRacket(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      radius,
    const typelib::coord2_t&    coord
) :
    Racket(
        world,
        sprite,
        needVisualSize,
        radius,
        DENSITY_SPHERE_RACKET,
        coord
    )
{
}




SphereRacket::~SphereRacket() {
}


} // arkanoid
