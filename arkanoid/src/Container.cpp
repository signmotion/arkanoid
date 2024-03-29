#include "../include/stdafx.h"
#include "../include/Container.h"
#include "../include/Level.h"
#include "../include/ManagerSound.h"
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
    const typelib::coord2_t&    coord,
    const AboutContainer&       about
) :
    VIncarnate( sprite, coord, needVisualSize ),
    PIncarnate( world, sign, next ),
    about( about )
{
    ASSERT( (radius > 0.0f)
        && "��� ���������� ���������� ������� ������." );
    ASSERT( (density >= 0.0f)
        && "��������� ���������� ������ ���� ������������� ��� �������." );

    b2CircleShape   shape;
    shape.m_radius = static_cast< float >( radius );

    b2FixtureDef fd;
    fd.shape = &shape;
	fd.density = density;
	fd.friction = 0.0f;
    fd.restitution = 1.0f;

	b2BodyDef bd;
    bd.type = b2_staticBody;
    // # ���������� �������� � ������.
    const auto pc = coord;
	bd.position.Set( pc.x, pc.y );

    PIncarnate::init( bd, fd );
}




Container::Container(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    sign_t                      next,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    const polygon_t&            polygon,
    float                       density,
    const typelib::coord2_t&    coord,
    const AboutContainer&       about
) :
    VIncarnate( sprite, coord, needVisualSize ),
    PIncarnate( world, sign, next ),
    about( about )
{
    const size_t n = polygon.size();
    {
        ASSERT( (polygon.front() != polygon.back())
            && "������� ���������� �� ������ ����������: ��������� �������� �����." );
#ifdef _DEBUG
        //std::unique( polygon.begin(), polygon.end() );
        //ASSERT( (n == polygon.size())
        //    && "������� ���������� �� ������ �����������." );
#endif
        ASSERT( (n >= 3)
            && "��������� ������ �������� �� ����� ��� �� ��� ������." );
        ASSERT( (density >= 0.0f)
            && "��������� ���������� ������ ���� ������������� ��� �������." );
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
    // # ���������� �������� � ������.
    const auto pc = coord;
	bd.position.Set( pc.x, pc.y );

    PIncarnate::init( bd, fd );
}




Container::~Container() {
}




std::unique_ptr< Container >
Container::valueOf(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    const AboutContainer&       about,
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
            coord,
            about
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
            coord,
            about
        ) );
    }

    // ���������� ��������� �� ����� ���� ������
    return std::unique_ptr< Container >();
}




void
Container::sync() {
    // # ����������� �������. �� ��������� � �������������.
}




void
Container::selfReaction( const std::string& event ) {

    ASSERT( !event.empty()
        && "������� ��� ���������� ������ ���� �������." );

    if (event == "destroy") {
        playNotEmpty( about.destroy.sound );

    } else {
        ASSERT( false
            && "������� ��� ���������� �� ��������." );
    }
}




void
Container::collisionReaction( const GE* ge ) {
    
    ASSERT( ge );

    const auto ftr = about.collision.find( ge->sign );
    if (ftr != about.collision.cend()) {
        playNotEmpty( ftr->second.sound );
    }
}








CubeContainer::CubeContainer(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    sign_t                      next,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    int                         side,
    const typelib::coord2_t&    coord,
    const AboutContainer&       about
) :
    Container(
        world,
        sign,
        next,
        sprite,
        needVisualSize,
        // # ��������� ����������� ���������:
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
        coord,
        about
    )
{
}




CubeContainer::~CubeContainer() {
}








SphereContainer::SphereContainer(
    std::shared_ptr< World >    world,
    sign_t                      sign,
    sign_t                      next,
    const std::string&          sprite,
    const typelib::size2Int_t&  needVisualSize,
    size_t                      radius,
    const typelib::coord2_t&    coord,
    const AboutContainer&       about
) :
    Container(
        world,
        sign,
        next,
        sprite,
        needVisualSize,
        radius,
        DENSITY_SPHERE_CONTAINER,
        coord,
        about
    )
{
}




SphereContainer::~SphereContainer() {
}


} // arkanoid
