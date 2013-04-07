#include "../include/stdafx.h"
#include "../include/Container.h"
#include "../include/Level.h"
#include "../include/World.h"


namespace arkanoid {


Container::Container(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    sign_t                      next,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      radius,
    float                       density,
    const typelib::coord2_t&    coord
) :
    PPIncarnate( sprite, coord, needVisualSize ),
    B2DIncarnate( world ),
    sign( sign ),
    next( next )
{
    ASSERT( (radius > 0.0f)
        && "Для контейнера необходимо указать радиус." );
    ASSERT( (density >= 0.0f)
        && "Плотность контейнера должна быть положительной или нулевой." );

    b2CircleShape   shape;
    shape.m_radius = static_cast< float >( radius );

    b2FixtureDef fd;
    fd.shape = &shape;
	fd.density = density;
	fd.friction = 0.0f;
    fd.restitution = 1.0f;

	b2BodyDef bd;
    bd.type = b2_staticBody;
    // # Координаты задаются в метрах.
    const auto pc = coord;
	bd.position.Set( pc.x, pc.y );

    B2DIncarnate::init( bd, fd );
}




Container::Container(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    sign_t                      next,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    const polygon_t&            polygon,
    float                       density,
    const typelib::coord2_t&    coord
) :
    PPIncarnate( sprite, coord, needVisualSize ),
    B2DIncarnate( world ),
    sign( sign ),
    next( next )
{
    const size_t n = polygon.size();
    {
        ASSERT( (polygon.front() != polygon.back())
            && "Вершины контейнера не должны замыкаться: замыкание построят здесь." );
#ifdef _DEBUG
        //std::unique( polygon.begin(), polygon.end() );
        //ASSERT( (n == polygon.size())
        //    && "Вершины контейнера не должны повторяться." );
#endif
        ASSERT( (n >= 3)
            && "Контейнер должен состоять не менее чем из трёх вершин." );
        ASSERT( (density >= 0.0f)
            && "Плотность контейнера должна быть положительной или нулевой." );
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
    bd.type = b2_staticBody;
    // # Координаты задаются в метрах.
    const auto pc = coord;
	bd.position.Set( pc.x, pc.y );

    B2DIncarnate::init( bd, fd );
}




Container::~Container() {
}




std::unique_ptr< Container >
Container::valueOf(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    const AboutSet&             about,
    const typelib::size2Int_t&  needVisualSize,
    const typelib::size2Int_t&  cell,
    const typelib::coord2_t&    coord
) {
    if (about.kind == "Cube") {
        const int side = cell.x;
        return std::unique_ptr< Container >( new CubeContainer(
            world,
            sign,
            about.next,
            about.sprite,
            needVisualSize,
            side,
            coord
        ) );
    }

    if (about.kind == "Sphere") {
        const size_t radius = cell.x / 2;
        return std::unique_ptr< Container >( new SphereContainer(
            world,
            sign,
            about.next,
            about.sprite,
            needVisualSize,
            radius,
            coord
        ) );

    }

    // подходящий контейнер не может быть создан
    return std::unique_ptr< Container >();
}




void
Container::sync() {
    // # Статический элемент. Не нуждается в синхронизации.
}








SphereContainer::SphereContainer(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    sign_t                      next,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      radius,
    const typelib::coord2_t&    coord
) :
    Container(
        world,
        sign,
        next,
        sprite,
        needVisualSize,
        radius,
        DENSITY_SPHERE_CONTAINER,
        coord
    )
{
}




SphereContainer::~SphereContainer() {
}








CubeContainer::CubeContainer(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    sign_t                      next,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    int                         side,
    const typelib::coord2_t&    coord
) :
    Container(
        world,
        sign,
        next,
        sprite,
        needVisualSize,
        // # Контейнер представлен полигоном:
        //   1---4
        //   |   |
        //   2---3
        static_cast< polygon_t >( boost::assign::list_of
            ( typelib::coord2_t( -side / 2,   side / 2 ) )    // 1
            ( typelib::coord2_t( -side / 2,  -side / 2 ) )    // 2
            ( typelib::coord2_t(  side / 2,  -side / 2 ) )    // 3
            ( typelib::coord2_t(  side / 2,   side / 2 ) )    // 4
        ),
        DENSITY_CUBE_CONTAINER,
        coord
    )
{
}




CubeContainer::~CubeContainer() {
}


} // arkanoid
