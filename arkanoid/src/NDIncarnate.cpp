#include "../include/stdafx.h"
#include "../include/NDIncarnate.h"
#include "../include/World.h"
#include "../include/CollidableMaterial.h"


namespace arkanoid {
    
    
NDIncarnate::NDIncarnate(
    std::shared_ptr< World >     world,
    NewtonCollision*             collision,
    float                        mass,
    const typelib::coord2_t&     coord,
    const typelib::coord2_t&     rotation,
    const typelib::vector2_t&    momentInertia,
    std::unique_ptr< Material >  material
) :
    mWorld( world ),
    mBody(),
    mForce( typelib::vector2_t::ZERO() ),
    mUIDMaterial( NewtonMaterialCreateGroupID( world->physics().get() ) ),
    mMaterial( std::move( material ) ),
    mCollidableMaterial()
{
    ASSERT( !mWorld.expired()
        && "ѕолучен разрушенный мир." );
    ASSERT( mWorld.lock()->physics()
        && "‘изический мир должен быть инициализирован." );
    ASSERT( collision
        && "‘орма тела должна быть указана." );
    /* - ћожно не указывать: на объекты с 0-й массой не действуют силы.
    ASSERT( (mass > 0.0f) && "ћасса должна быть указана." );
    */
    ASSERT( mMaterial
        && "ћатериал дл€ физ. тела должен быть указан." );

    // создаЄм тело дл€ физ. движка

    NewtonWorld* w = mWorld.lock()->physics().get();

    const auto ws = NewtonWorldFloatSize();

    // @todo optimize ‘ормы можно использовать повторно.
    float tm[ 16 ];
    init( tm, coord, rotation );
    mBody = NewtonCreateBody( w, collision, tm );
    ASSERT( mBody
        && "‘из. тело не создано." );

    NewtonReleaseCollision( w, collision );

    NewtonBodySetMassMatrix(
        mBody, mass,
        momentInertia.x, momentInertia.y, momentInertia.y
    );


    // материал дл€ этого тела
    // # —труктура взаимодействи€ проиницализирована согласно
    //   требовани€м Newton Dynamics.
    NewtonBodySetMaterialGroupID( mBody, mUIDMaterial );


    // конфигурируем тело
    NewtonBodySetUserData( mBody, this );

    NewtonBodySetForceAndTorqueCallback( mBody,  applyForceAndTorque );
    NewtonBodySetTransformCallback(      mBody,  setTransform        );
    NewtonBodySetDestructorCallback(     mBody,  autoDestruction     );


    // говорим, когда телу остановитьс€
    NewtonBodySetAutoSleep( mBody, 1 );
    NewtonBodySetLinearDamping( mBody, 0.0f );
    NewtonBodySetAngularDamping( mBody, &dgVector( 0.0f, 0.0f, 0.0f, 1.0f )[0] );
}




NDIncarnate::~NDIncarnate() {
    // предотвращаем бесконечную рекурсию, удал€ем физ. тело
    NewtonBodySetDestructorCallback( mBody, nullptr );
    NewtonBodySetUserData( mBody, nullptr );
    NewtonDestroyBody( NewtonBodyGetWorld( mBody ), mBody );
}




const NewtonWorld*
NDIncarnate::world() const {
    return mWorld.lock()->physics().get();
}




NewtonWorld*
NDIncarnate::world() {
    return mWorld.lock()->physics().get();
}




void
NDIncarnate::applyForceAndTorque() {

    // на тело может действовать сила
    // сила по€вл€етс€ из-за событий; например, нажатие на клавиши дл€
    // перемещени€ платформы
    auto b = NDIncarnate::body();
    float mass, ix, iy, iz;
    NewtonBodyGetMassMatrix( b, &mass, &ix, &iy, &iz );
    const float force[ 4 ] =
        { mForce.x,  0.0f,  mForce.y,  1.0f };
    NewtonBodySetForce( b, force );

    mForce = typelib::vector2_t::ZERO();
}




void
NDIncarnate::init(
    float tm[ 16 ],
    const typelib::coord2_t&  coord,
    const typelib::coord2_t&  rotation
) {
    // пространственное положение элемента
	const dgMatrix m(
        dgRollMatrix(  rotation.x * static_cast< float >( M_PI ) / 180.0f ) *
        dgYawMatrix(   0.0f                                               ) *
        dgPitchMatrix( rotation.y * static_cast< float >( M_PI ) / 180.0f )
    );
    const dgMatrix t(
        dgQuaternion( m ),
        dgVector( coord.x, 0.0f, coord.y, 1.0f )
    );
    tm[0]  = t[0][0];   tm[1]  = t[0][1];   tm[2]  = t[0][2];   tm[3]  = t[0][3];
    tm[4]  = t[1][0];   tm[5]  = t[1][1];   tm[6]  = t[1][2];   tm[7]  = t[1][3];
    tm[8]  = t[2][0];   tm[9]  = t[2][1];   tm[10] = t[2][2];   tm[11] = t[2][3];
    tm[12] = t[3][0];   tm[13] = t[3][1];   tm[14] = t[3][2];   tm[15] = t[3][3];
}




void
NDIncarnate::contactProcess(
    const NewtonJoint*  contactJoint,
    float  timestep,
    int    threadIndex
) {
    NewtonBody* const a = NewtonJointGetBody0( contactJoint );
    auto bodyA = static_cast< NDIncarnate* >( NewtonBodyGetUserData( a ) );
    NewtonBody* const b = NewtonJointGetBody1( contactJoint );
    auto bodyB = static_cast< NDIncarnate* >( NewtonBodyGetUserData( b ) );
    bodyA->contactProcess( bodyB, contactJoint );

#if 0
// @test
    NewtonBody* const bodyA = NewtonJointGetBody0( contactJoint );
    NewtonBody* const bodyB = NewtonJointGetBody1( contactJoint );

    for (auto ctr = NewtonContactJointGetFirstContact( contactJoint );  ctr;
         ctr = NewtonContactJointGetNextContact( contactJoint, ctr )
    ) {
        NewtonMaterial* const material = NewtonContactGetMaterial( ctr );

        dgVector point;
        dgVector normal;
        NewtonMaterialGetContactPositionAndNormal( material, bodyA, &point.m_x, &normal.m_x );
      
        dgVector dirA;
        dgVector dirB;
        NewtonMaterialGetContactTangentDirections (material, bodyA, &dirA.m_x, &dirB.m_x );

        dgVector forceA;
        NewtonMaterialGetContactForce( material, bodyA, &forceA.m_x );

        /* forceB = -forceA
        dgVector forceB;
        NewtonMaterialGetContactForce( material, bodyB, &forceB.m_x );
        */

        const float speed = NewtonMaterialGetContactNormalSpeed( material );

        bool test = true;

    } // for (auto ctr = NewtonContactJointGetFirstContact( contactJoint ) ...
#endif
}


} // arkanoid
