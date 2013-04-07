#include "../include/stdafx.h"
#include "../include/ManagerSprite.h"
#include "../include/Platform.h"
#include "../include/World.h"


namespace arkanoid {


Platform::Platform(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    const polygon_t&            polygon,
    float                       density,
    const typelib::coord2_t&    coord
) :
    PPIncarnate( sprite, coord, needVisualSize ),
    B2DIncarnate( world ),
    mDestination( coord )
{
    const size_t n = polygon.size();
    {
        ASSERT( (polygon.front() != polygon.back())
            && "Вершины платформы не должны замыкаться: замыкание построят здесь." );
#ifdef _DEBUG
        //std::unique( polygon.begin(), polygon.end() );
        //ASSERT( (n == polygon.size())
        //    && "Вершины платформы не должны повторяться." );
#endif
        ASSERT( (n >= 3)
            && "Платформа должна состоять не менее чем из трёх вершин." );
        ASSERT( (density > 0.0f)
            && "Плотность платформы должна быть указана." );
    }


    b2PolygonShape shape;
    std::unique_ptr< b2Vec2 >  vertices( new b2Vec2[ n + 1 ] );
    for (auto itr = polygon.cbegin(); itr != polygon.cend(); ++itr) {
        const size_t i = std::distance( polygon.cbegin(), itr );
        vertices.get()[ i ].Set( itr->x, itr->y );
    }
    const auto& front = polygon.front();
    vertices.get()[ n ].Set( front.x, front.y );
    shape.Set( vertices.get(), n );

    b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = density;
	fd.friction = 0.0f;
    fd.restitution = 1.0f;

	b2BodyDef bd;
    // # Платформу будем двигать сами.
    bd.type = b2_kinematicBody;
    // # Координаты задаются в метрах.
    //const auto shift = static_cast< typelib::coord2_t >( needVisualSize );
    const auto pc = coord;
	bd.position.Set( pc.x, pc.y );

    B2DIncarnate::init( bd, fd );
}




Platform::~Platform() {
}




void
Platform::sync() {
    const auto vc = coord();
    visualCoord( vc.x, vc.y );
    const auto a = rotation();
    visualRotation( a );
}




void
Platform::draw( prcore::Bitmap& context ) const {

    using namespace prcore;

    auto s = mManagerSprite->sprite(
        PATH_MEDIA + "/" + sprite,
        needVisualSize
    );
    DASSERT( s
        && "Спрайт для элемента не найден." );

    SetAlphaFunc( SRCALPHA, SRCINVALPHA );
    SetConstantAlpha( 0xFF, 0xFF );
    // @todo fine Согласовать физ. модель с визуальной на уровне PPIncarnate.
    const auto shift = needVisualSize / 2;
    const auto vc = visualCoord();
    AlphaBlend( vc.x - shift.x,  vc.y + shift.y,  context,  *s );
}








CapsulePlatform::CapsulePlatform(
    std::shared_ptr< World >    world,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    const typelib::size2Int_t&  size,
    const typelib::coord2_t&    coord
) :
    Platform(
        world,
        sprite,
        needVisualSize,
#if 0
        // # Капсула представлена полигоном:
        //      1-------------6
        //   2<       0:0       >5
        //      3-------------4
        static_cast< polygon_t >( boost::assign::list_of
            ( typelib::coord2_t( -size.x / 2 + size.x / 10,   size.y / 2 ) )    // 1
            ( typelib::coord2_t( -size.x / 2,                 0 ) )             // 2
            ( typelib::coord2_t( -size.x / 2 + size.x / 10,  -size.y / 2 ) )    // 3
            ( typelib::coord2_t(  size.x / 2 - size.x / 10,  -size.y / 2 ) )    // 4
            ( typelib::coord2_t(  size.x / 2,                 0 ) )             // 5
            ( typelib::coord2_t(  size.x / 2 - size.x / 10,   size.y / 2 ) )    // 6
        ),
#else
        // # Капсула представлена полигоном (схема):
        //             1
        //            / \
        //         /       \
        //      /             \
        //   2<       0:0       >5
        //      3-------------4
        static_cast< polygon_t >( boost::assign::list_of
            ( typelib::coord2_t(  0,                         size.y / 2 ) )    // 1
            ( typelib::coord2_t( -size.x / 2,                0 ) )             // 2
            ( typelib::coord2_t( -size.x / 2 + size.x / 5,  -size.y / 2 ) )    // 3
            ( typelib::coord2_t(  size.x / 2 - size.x / 5,  -size.y / 2 ) )    // 4
            ( typelib::coord2_t(  size.x / 2,                0 ) )             // 5
        ),
#endif
        DENSITY_CAPSULE_PLATFORM,
        coord
    )
{
}




CapsulePlatform::~CapsulePlatform() {
}


} // arkanoid
