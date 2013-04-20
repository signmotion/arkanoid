#include "../include/stdafx.h"
#include "../include/PIncarnate.h"
#include "../include/World.h"


namespace arkanoid {
    
    
PIncarnate::PIncarnate(
    std::shared_ptr< World >  world,
    sign_t  sign,
    sign_t  next
) :
    GE( sign, next ),
    mWorld( world ),
    mBody( nullptr )
{
    ASSERT( !mWorld.expired()
        && "Получен разрушенный мир." );
    ASSERT( mWorld.lock()->physics()
        && "Физический мир должен быть инициализирован." );

    // #! Метод init() должен быть обязательно вызван потомком.
}




PIncarnate::~PIncarnate() {
    if ( mBody && world() ) {
        world()->DestroyBody( mBody );
    }
}




void
PIncarnate::init(
    const b2BodyDef&     bd,
    const b2FixtureDef&  fd
) {
    mBody = world()->CreateBody( &bd );
    mBody->CreateFixture( &fd );
    mBody->ResetMassData();

    mBody->SetUserData( this );
}




const b2World*
PIncarnate::world() const {
    return mWorld.lock()->physics().get();
}




b2World*
PIncarnate::world() {
    return mWorld.lock()->physics().get();
}


} // arkanoid
