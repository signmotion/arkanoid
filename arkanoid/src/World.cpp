#include "../include/stdafx.h"
#include "../include/Background.h"
#include "../include/Border.h"
#include "../include/Container.h"
#include "../include/Level.h"
#include "../include/Message.h"
#include "../include/Platform.h"
#include "../include/Racket.h"
#include "../include/Remains.h"
#include "../include/World.h"


namespace arkanoid {


const typelib::coord2Int_t  World::mStartCoordRacket(
    WINDOW_WIDTH  / 2,
    WINDOW_HEIGHT / 5 * 4
);

const std::string  World::mTitleWindow = "Arkanoid demo DC";
const prcore::Timer  World::mTimer = prcore::Timer();




World::World( int width, int height ) :
    // # ��� ��� ����������.
    mPhysics( new b2World( b2Vec2_zero ) ),
    mVisual( width, height, prcore::PIXELFORMAT_ARGB8888 ),
    mImpactCount( 0 ),
    mContactPointCount( 0 )
{
    ASSERT( mPhysics
        && "�� ������� ���������������� ���. ������." );

    // *���������� ���*
    {
        mPhysics->SetContactListener( this );
    }


    // *����������� ���*
    {
        OpenBuffer( width, height, mTitleWindow.c_str() );
        SetMainFrequency( 200.0f );
    }
}




std::shared_ptr< World >
World::valueOf() {
    return std::shared_ptr< World >( new World() );
}




World::~World() {
    // ����� ����� assert'� ��� ������ �� ����������
    // @todo fine ������� �������.
    exit( 0 );
}




void
World::go( size_t startLevel ) {

    for (bool present = loadNextLevel( startLevel );
        present;
        present = loadNextLevel()
    ) {
        // ����. �������
        MainLoop();
    }

    // ���� ��������
#ifdef _DEBUG
    CONSOLE << "\n\n������� ������ ���." << std::endl;
#endif
}




std::shared_ptr< b2World >
World::physics() {
    return mPhysics;
}




std::shared_ptr< const b2World >
World::physics() const {
    return mPhysics;
}




bool
World::loadNextLevel( size_t startLevel ) {
    
    const size_t nextLevel = mLevel ? (mLevel->current + 1) : startLevel;
    if ( !Level::has( nextLevel ) ) {
        // ������� ������ ���
        return false;
    }

#ifdef _DEBUG
    CONSOLE << "\n\n������� " << nextLevel << std::endl;
#endif

    mLevel = std::unique_ptr< Level >( new Level( nextLevel ) );


    // �������� ��� �������� ����������� ���� mLevel

    // ������� ����
#if 1
    mBorderSet.clear();
    {
        // @todo fine ����������� � ���� ������� Box2D.
        const int w = static_cast< int >( WINDOW_WIDTH );
        const int cell = static_cast< int >( CELL_SIZE );
        std::unique_ptr< Border >  top( new EdgeBorder(
            this->shared_from_this(),
            typelib::coord2Int_t( -w * 2,  -cell / 2 ),
            typelib::coord2Int_t(  w * 2,  -cell / 2 )
        ) );
        mBorderSet.push_back( std::move( top ) );
    }
#endif


    // ���
#if 1
    mBackground.reset();
    {
        const auto& about = mLevel->mAboutBackground;
        // # ��� ������������� �� �� ������� ����.
        // @todo �������������, ����� ������� ���� � ���� ����������� ����������.
        const typelib::size2Int_t  size( WINDOW_WIDTH, WINDOW_HEIGHT );
        mBackground = std::unique_ptr< Background >( new Background(
            about.sprite,
            size,
            typelib::coord2Int_t::ZERO()
        ) );
    }
#endif


    // ���������
#if 1
    mPlatformSet.clear();
    {
        std::unique_ptr< Platform >  platform;
        const auto& about = mLevel->mAboutPlatform;
        if (about.kind == "Capsule") {
            const typelib::size2Int_t  size( 128, 16 );
            platform = std::unique_ptr< Platform >( new CapsulePlatform(
                this->shared_from_this(),
                about.sprite,
                size,
                size,
                typelib::coord2Int_t(
                    WINDOW_WIDTH / 2,
                    WINDOW_HEIGHT - size.y * 2
                )
            ) );

        } else {
            ASSERT( false
                && "��� ��������� �� ���������." );
        }

        ASSERT( platform
            && "��������� �� �������." );
        mPlatformSet.push_back( std::move( platform ) );
    }
    ASSERT( (mPlatformSet.size() == 1)
        && "��������� ������������ ���������." );
#endif


    // �������
#if 1
    mRacketSet.clear();
    {
        std::unique_ptr< Racket >  racket;
        const auto& about = mLevel->mAboutRacket;
        if (about.kind == "Sphere") {
            // # ���� ������� ������ ������� �������.
            const size_t radius = (32 - 12) / 2;
            racket = std::unique_ptr< Racket >( new SphereRacket(
                this->shared_from_this(),
                about.sprite,
                typelib::size2Int_t( 32, 32 ),
                radius,
                mStartCoordRacket
            ) );

        } else {
            ASSERT( false
                && "��� ������� �� ���������." );
        }

        ASSERT( racket
            && "������� �� �������." );
        mRacketSet.push_back( std::move( racket ) );
    }
    ASSERT( (mRacketSet.size() == 1)
        && "��������� ������������ �������." );
#endif


    // ���������� � �������
    // # ���������� � ������� ������������� �� ����� �����.
#if 1
    mContainerSet.clear();
    mRemainsSet.clear();
    typelib::coord2Int_t  coord( 0, 0 );
    for (auto itr = mLevel->mMap.cbegin();
         itr != mLevel->mMap.cend();  ++itr
    ) {
        const Level::row_t&  row = *itr;
        // # ��������� ��������� ������ ������.
        for (auto rtr = row.cbegin(); rtr != row.cend(); ++rtr) {
            const sign_t sign = *rtr;
            // # ������ '.' �������� "������ ������".
            if (sign != '.') {
                incarnate( sign, coord );
            }

            coord.x += mLevel->mCell.x;
            ASSERT( ((coord.x <= WINDOW_WIDTH) && (coord.x >= 0))
                && "������� ��������� ������� �� ��������� ������ (������)." );

        } // for (auto rtr = ...

        coord.x = 0;
        coord.y += mLevel->mCell.y;
        ASSERT( ((coord.y <= WINDOW_HEIGHT) && (coord.y >= 0))
            && "������� ��������� ������� �� ��������� ������ (������)." );

    } // for (auto itr = ...

    ASSERT( !mContainerSet.empty()
        && "������� �� ������ ���� ������." );
#endif


    return mLevel;
}




World::Statistics
World::statistics() const {

    Statistics st = {};
    for (auto ctr = mContainerSet.cbegin(); ctr != mContainerSet.cend(); ++ctr ) {
        const Container* container = ctr->get();
        if (container->sign == container->next) {
            ++st.indestructible;
        } else {
            ++st.destructible;
        }
    }

    return st;
}




bool
World::EventMain() {
    EventDraw();
    return true;
}




void
World::EventDraw() {

    using namespace prcore;

    // ��������� � ���������� FPS
    // # ����������� �� FPS ���������� ��� �������� ���� - ��. World().
    static auto lastTime = World::currentTime();
    const auto currentTime = World::currentTime();
    auto deltaTime = currentTime - lastTime;
    // ���: ���� ���������� ����� �������������
    if (deltaTime > 1000) { deltaTime = 1000; }
    // 'deltaTime' ����� ������������ ��� ����������� ��������
    lastTime = currentTime;
    const size_t fps = calcFPS( deltaTime );
    const std::string title =
        mTitleWindow + "  " + boost::lexical_cast< std::string >( fps ) + " fps";
    RenameWindow( title.c_str() );


    static const uint32 bgColor = 0xFF5DA130;
    mVisual.ClearImage( bgColor );


    // ������
    {
        movePlatformToDestination();

        mImpactCount = 0;
        mContactPointCount = 0;

        static const float timeStep     = 1.0f / 60.0f;
        static const size_t velocityItr = 16;
        static const size_t positionItr = 12;
        mPhysics->Step( timeStep, velocityItr, positionItr );
        //mPhysics->ClearForces();
    }

    // �������
    {
        // # ������� ���� �� ��������.

        mBackground->draw( mVisual );

        for (auto ctr = mRemainsSet.cbegin(); ctr != mRemainsSet.cend(); ++ctr ) {
            ( *ctr )->draw( mVisual );
        }

        for (auto ctr = mContainerSet.cbegin(); ctr != mContainerSet.cend(); ++ctr ) {
            ( *ctr )->draw( mVisual );
        }

        for (auto ptr = mPlatformSet.cbegin(); ptr != mPlatformSet.cend(); ++ptr ) {
            ( *ptr )->draw( mVisual );
        }

        for (auto rtr = mRacketSet.cbegin(); rtr != mRacketSet.cend(); ++rtr ) {
            ( *rtr )->draw( mVisual );
        }
    }


    // ������ ���������
    {
        // ���������� ��������� ������ ������������
        if (mImpactCount > 0) {
            // ����� ���� ���������
            std::sort( mImpactSet,  mImpactSet + mImpactCount );
            for (size_t i = 0; i < mImpactCount; ) {
                b2Body* body = mImpactSet[ i++ ];
                ASSERT( body
                    && "�������� ����������� ���. ����." );
                while ( (i < mImpactCount) && (mImpactSet[ i ] == body) ) {
                    ++i;
                }
                reincarnateOrDie( body );
                // ������� �������?
                if ( completed() ) {
                    levelCompletedAction();
                    MainBreak();
                }

            } // for (size_t i = 0; i < mImpactCount; )

        } // if (mImpactCount > 0)
    }


    // �������������
    {
        for (auto ptr = mPlatformSet.cbegin(); ptr != mPlatformSet.cend(); ++ptr ) {
            ( *ptr )->sync();
        }

        for (auto rtr = mRacketSet.cbegin(); rtr != mRacketSet.cend(); ++rtr ) {
            ( *rtr )->sync();
            // �������� ������� �������
            if ( out( *rtr->get() ) ) {
                racketOutAction();
            }
        }
    }


    BlitWrite( 0, 0, mVisual );
    PageFlip();
}




void
World::EventSize( int width, int height ) {
}




void
World::EventMouseButton(
    int mx, int my,
    prcore::MouseButton button,
    int count
) {
    using namespace prcore;

    switch ( button ) {
        case MOUSE_LEFT:
            setPlatformDestination( mx, my );
            break;

        case MOUSE_MIDDLE:
            break;

        case MOUSE_RIGHT:
            break;

        case MOUSE_XBUTTON1:
            break;

        case MOUSE_XBUTTON2:
            break;

        case MOUSE_WHEEL:
            break;
    }
}




void
World::EventKeyboard( int keycode, char charcode, bool press ) {

    using namespace prcore;

    if ((keycode == KEYCODE_UP) && press) {
        pushRacket( true );

    } else if ((keycode == KEYCODE_SPACE) && press) {
        pushRacket( false );

    } else if ((keycode == KEYCODE_ESC) && press) {
        MainBreak();
    }
}




void
World::PreSolve(
    b2Contact*         contact,
    const b2Manifold*  oldManifold
) {
	const b2Manifold* manifold = contact->GetManifold();
	if (manifold->pointCount == 0) {
		return;
	}

	b2Fixture* fixtureA = contact->GetFixtureA();
    const auto typeA = fixtureA->GetBody()->GetType();
	b2Fixture* fixtureB = contact->GetFixtureB();
    const auto typeB = fixtureB->GetBody()->GetType();

    /* - @test
	b2PointState  stateA[ b2_maxManifoldPoints ];
    b2PointState  stateB[ b2_maxManifoldPoints ];
	b2GetPointStates( stateA, stateB, oldManifold, manifold );
    */

	b2WorldManifold  worldManifold;
	contact->GetWorldManifold( &worldManifold );
	for (size_t i = 0;
        (i < static_cast< size_t >( manifold->pointCount ))
          && (mContactPointCount < MAX_CONTACT_POINT);
        ++i
    ) {
        /* - @test
		ContactPoint* cp = mContactPointSet + mContactPointCount;
		cp->a = fixtureA;
		cp->b = fixtureB;
		cp->position = worldManifold.points[ i ];
		cp->normal = worldManifold.normal;
		cp->state = stateB[ i ];
		++mContactPointCount;
        */

        // �������� ����������� �������� ��������
        // ����� �������������� ������ � ������� ��
        if ( (mImpactCount < MAX_IMPACT) && (typeA == b2_staticBody) ) {
            mImpactSet[ mImpactCount ] =
                static_cast< b2Body* >( fixtureA->GetBody() );
            ++mImpactCount;
        }
        if ( (mImpactCount < MAX_IMPACT) && (typeB == b2_staticBody) ) {
            mImpactSet[ mImpactCount ] =
                static_cast< b2Body* >( fixtureB->GetBody() );
            ++mImpactCount;
        }

	} // for (size_t i = 0; ...
}




void
World::PostSolve(
    const b2Contact*         contact,
    const b2ContactImpulse*  impulse
) {
    NOT_USED( contact );
    NOT_USED( impulse );
}




size_t
World::calcFPS( size_t frameTime ) {

    static size_t fpsResult  = 0;
    static size_t fpsCounter = 0;
    static size_t totalTime  = 0;
    
    totalTime += frameTime;
    if (totalTime >= 1000) {
        fpsResult = fpsCounter + 1;
        fpsCounter = totalTime = 0;
    }
    ++fpsCounter;

    return fpsResult;
}




void
World::setPlatformDestination( int x,  int y ) {

    auto& platform = mPlatformSet.front();
    // ����� ���������� - �� ������ ���������
    platform->mDestination.x = x;
    platform->mDestination.y = y;
}




void
World::movePlatformToDestination() {

    // # ��������� ������������ ����� ��� OX.
    auto& platform = mPlatformSet.front();
    const auto velocityX = platform->linearVelocity().x;
    const float distanceX = static_cast< float >(
        platform->mDestination.x - platform->visualCoord().x
    );
    const float nvx = distanceX;
    platform->body()->SetLinearVelocity( b2Vec2( nvx, 0 ) );
}




void
World::pushRacket( bool always ) {

    auto& racket = mRacketSet.front();

    // ������� ������� ������ ���� ��� ����� ���������
    const auto velocity = racket->linearVelocity().length();
    if ( !always && (velocity > 20.0f) ) {
        return;
    }

    const float mass = racket->mass();
    const float force =
        mass * static_cast< float >( std::rand() % 3000 + 2000 );
    const float angle =
        static_cast< float >( std::rand() % 180 ) * 3.1416f / 180.0f;
    const auto fv =
        typelib::vector2_t( cos( angle ),  -sin( angle ) ) * force;
    racket->pushRacket( fv );
}




void
World::incarnate( sign_t sign,  const typelib::coord2Int_t& coord ) {

    ASSERT( mLevel
        && "������� ������ ���� �������� �� ������ ����� ������." );

    const auto ftr = mLevel->mAboutSetSign.find( sign );
    ASSERT( (ftr != mLevel->mAboutSetSign.cend())
        && "���������� � ���������� �����������." );
    const AboutSet&  about = ftr->second;
    const auto& needVisualSize = mLevel->mCell;

    std::unique_ptr< Container >  container = Container::valueOf(
        this->shared_from_this(),
        sign,
        about,
        mLevel->mCell,
        needVisualSize,
        coord
    );

    std::unique_ptr< Remains >  remains = Remains::valueOf(
        about,
        needVisualSize,
        coord
    );

    ASSERT( ( container || remains )
        && "���������� ����� �� ������." );

    if ( container ) {
        mContainerSet.push_back( std::move( container ) );

    } else if ( remains ) {
        mRemainsSet.push_back( std::move( remains ) );
    }
}




bool
World::completed() const {
    const auto st = statistics();
    return (st.destructible == 0);
}




bool
World::out( const Racket& racket ) const {
    const auto c = racket.coord();
    static const int B = 100;
    return (c.x < -B) || (c.x > WINDOW_WIDTH  + B)
        || (c.y < -B) || (c.y > WINDOW_HEIGHT + B);
}




void
World::reincarnateOrDie( b2Body* body ) {

    for (auto ctr = mContainerSet.begin();
         ctr != mContainerSet.end();  ++ctr
    ) {
        const auto b2 = ( *ctr )->body();
        if (b2 != body) {
            continue;
        }

        // �������, ������ �� ���� ������� ��������� ������������ ���
        // �� ��� ����� ���� ������� ����� �����
        const Container* container = ctr->get();
        const bool destroy =
            (container->next == 0) || (container->sign != container->next);
        const bool create =
            (container->next != 0);
        const sign_t sign = container->next;
        const typelib::coord2Int_t coord = container->coord();
        if ( destroy ) {
            // ���������� �������
            mContainerSet.erase( ctr );
        }
        if ( create ) {
            // ������ �� ��� ����� �����
            incarnate( sign, coord );
        }

        // �������� � ������ ���������
        break;

    } // for (auto ctr = ...
}




void
World::levelCompletedAction() {

    const Message message( "message/level-completed.png" );
    message.draw( mVisual );
    BlitWrite( 0, 0, mVisual );
    PageFlip();

    boost::this_thread::sleep( boost::posix_time::seconds( 2 ) );
}




void
World::racketOutAction() {

    const Message message( "message/racket-out.png" );
    message.draw( mVisual );
    BlitWrite( 0, 0, mVisual );
    PageFlip();

    boost::this_thread::sleep( boost::posix_time::seconds( 2 ) );

    // ����� �������
    auto& racket = mRacketSet.front();
    racket->coord( mStartCoordRacket );
    racket->body()->SetLinearVelocity( b2Vec2_zero );
    racket->body()->SetAngularVelocity( 0.0f );
}


} // arkanoid
