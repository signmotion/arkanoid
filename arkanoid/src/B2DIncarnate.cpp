#include "../include/stdafx.h"
#include "../include/B2DIncarnate.h"
#include "../include/World.h"


namespace arkanoid {
    
    
B2DIncarnate::B2DIncarnate(
    std::shared_ptr< World >  world
) :
    mWorld( world ),
    mBody( nullptr )
{
    ASSERT( !mWorld.expired()
        && "Получен разрушенный мир." );
    ASSERT( mWorld.lock()->physics()
        && "Физический мир должен быть инициализирован." );

    // #! Метод init() должен быть обязательно вызван потомком.
}




B2DIncarnate::~B2DIncarnate() {
    if ( mBody && world() ) {
        world()->DestroyBody( mBody );
    }
}




void
B2DIncarnate::init(
    const b2BodyDef&     bd,
    const b2FixtureDef&  fd
) {
    mBody = world()->CreateBody( &bd );
    mBody->CreateFixture( &fd );
    mBody->ResetMassData();

    //mBody->SetUserData( this );
}




const b2World*
B2DIncarnate::world() const {
    return mWorld.lock()->physics().get();
}




b2World*
B2DIncarnate::world() {
    return mWorld.lock()->physics().get();
}


} // arkanoid
