#include "../include/stdafx.h"
#include "../include/Border.h"
#include "../include/World.h"


namespace arkanoid {


Border::Border(
    std::shared_ptr< World >  world,
    const typelib::coord2_t&  a,
    const typelib::coord2_t&  b
) :
    PIncarnate( world, 0, 0 )
{
    ASSERT( (a != b)
        && "Координаты должны задавать отрезок, не точку." );

    b2EdgeShape shape;
	shape.Set( b2Vec2( a.x, a.y ),  b2Vec2( b.x, b.y ) );

    b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.friction = 0.0f;
    fd.restitution = 1.0f;

	b2BodyDef bd;
    bd.type = b2_staticBody;
    const auto c = (a + b) / 2;
    // # Координаты задаются в метрах.
    const auto pc = c;
	bd.position.Set( pc.x, pc.y );

    PIncarnate::init( bd, fd );
}




Border::~Border() {
}




void
Border::sync() {
    // # Статический. Не нуждается в синхронизации.
}




void
Border::selfReaction( const std::string& event ) {
    // # Не реагирует.
}




void
Border::collisionReaction( const GE* ge ) {
    // # Не реагирует.
}








EdgeBorder::EdgeBorder(
    std::shared_ptr< World >  world,
    const typelib::coord2_t&  a,
    const typelib::coord2_t&  b
) :
    Border( world, a, b )
{
}




EdgeBorder::~EdgeBorder() {
}


} // arkanoid
