#include "../include/stdafx.h"
#include "../include/Background.h"
#include "../include/Border.h"
#include "../include/Container.h"
#include "../include/Level.h"
#include "../include/Platform.h"
#include "../include/Racket.h"
#include "../include/Remains.h"
#include "../include/World.h"


namespace arkanoid {


const std::string  World::mTitleWindow = "Arkanoid demo";
const prcore::Timer  World::mTimer = prcore::Timer();




World::World( int width, int height ) :
    mPhysics( NewtonCreate() ),
    mVisual( width, height, prcore::PIXELFORMAT_ARGB8888 )
{
    ASSERT( mPhysics
        && "�� ������� ���������������� ���. ������." );

    // *���������� ���*
    {
        NewtonSetPlatformArchitecture( mPhysics.get(), 0 );
	    NewtonSetSolverModel( mPhysics.get(), 0 );
        //NewtonSetMinimumFrameRate( mPhysicsWorld, 100.0f );

        // ������ ���. ��� ��������� �������, ��� ������� ����
        // # ��� K = 1 ���. ��� � 2 ���� ������ �����������.
        static const float K = 1.0f;
        static const float minmaxSX = static_cast< float >( WINDOW_WIDTH  ) * K;
        static const float minmaxSY = static_cast< float >( WINDOW_HEIGHT ) * K;
        // # ���������� ��� - ��������.
        static const float minmaxSZ = static_cast< float >( WINDOW_WIDTH  ) * K;
        mMinCoord = typelib::coord2Int_t( -minmaxSX, -minmaxSY );
        mMaxCoord = typelib::coord2Int_t( minmaxSX, minmaxSY );
	    static const dgVector minSize( -minmaxSX, -minmaxSY, -minmaxSZ, 1.0f );
	    static const dgVector maxSize(  minmaxSX,  minmaxSY,  minmaxSZ, 1.0f );
	    NewtonSetWorldSize( mPhysics.get(),  &minSize[ 0 ],  &maxSize[ 0 ] );

        // �������� �� ��������� ��� ��������� ���. ����
        const int defMaterial = NewtonMaterialGetDefaultGroupID( mPhysics.get() );
        NewtonMaterialSetDefaultCollidable( mPhysics.get(), defMaterial, defMaterial, 1 );
        NewtonMaterialSetDefaultElasticity( mPhysics.get(), defMaterial, defMaterial, 0.4f );
        NewtonMaterialSetDefaultFriction(   mPhysics.get(), defMaterial, defMaterial, 1.0f, 0.5f );
        NewtonMaterialSetDefaultSoftness(   mPhysics.get(), defMaterial, defMaterial, 0.05f );

        // ������� ������� �� ���. ����
        NewtonSetBodyLeaveWorldEvent( mPhysics.get(), physicsBodyLeaveWorld );
    }


    // *����������� ���*
    {
        OpenBuffer( width, height, mTitleWindow.c_str() );
        SetMainFrequency( 100.0f );
    }
}




std::shared_ptr< World >
World::valueOf() {
    auto r = std::shared_ptr< World >( new World() );
    return r;
}




World::~World() {
#ifdef _DEBUG
    // ����� ����� assert'� NewtonDynamics ��� ������ �� ����������
    // @todo fine ������� �������.
    exit( 0 );
#endif

    NewtonDestroy( mPhysics.get() );
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




std::shared_ptr< NewtonWorld >
World::physics() {
    return mPhysics;
}




std::shared_ptr< const NewtonWorld >
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
    mBorderSet.clear();
    {
        static const int  THICKNESS = 100;
        static const int  SHIFT = static_cast< int >( CELL_SIZE ) / 2;
        std::unique_ptr< Border >  top( new BoxBorder(
            this->shared_from_this(),
            // # ������� ���� �� ��������.
            "",
            typelib::size2Int_t( 1, 1 ),
            typelib::size2Int_t( WINDOW_WIDTH, THICKNESS ),
            typelib::coord2Int_t( 0, -THICKNESS + SHIFT ),
            typelib::coord2Int_t::ZERO()
        ) );
        mBorderSet.push_back( std::move( top ) );

        std::unique_ptr< Border >  right( new BoxBorder(
            this->shared_from_this(),
            "",
            typelib::size2Int_t( 1, 1 ),
            typelib::size2Int_t( THICKNESS, WINDOW_HEIGHT * 2 ),
            typelib::coord2Int_t(
                WINDOW_WIDTH + THICKNESS / 2 - SHIFT,
                WINDOW_HEIGHT / 2
            ),
            typelib::coord2Int_t::ZERO()
        ) );
        mBorderSet.push_back( std::move( right ) );

        std::unique_ptr< Border >  left( new BoxBorder(
            this->shared_from_this(),
            "",
            typelib::size2Int_t( 1, 1 ),
            typelib::size2Int_t( THICKNESS, WINDOW_HEIGHT * 2 ),
            typelib::coord2Int_t( -THICKNESS / 2 - SHIFT, WINDOW_HEIGHT / 2 ),
            typelib::coord2Int_t::ZERO()
        ) );
        mBorderSet.push_back( std::move( left ) );
    }


    // ���
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


    // ���������
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
                typelib::coord2Int_t( WINDOW_WIDTH / 2,  WINDOW_HEIGHT - size.y * 2 ),
                typelib::coord2Int_t::ZERO()
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


    // �������
    mRacketSet.clear();
    {
        std::unique_ptr< Racket >  racket;
        const auto& about = mLevel->mAboutRacket;
        if (about.kind == "Sphere") {
            racket = std::unique_ptr< Racket >( new SphereRacket(
                this->shared_from_this(),
                about.sprite,
                typelib::size2Int_t( 32, 32 ),
                // # ���� ������� ������ ������� �������.
                (32 - 8) / 2,
                typelib::coord2Int_t( WINDOW_WIDTH / 2,  WINDOW_HEIGHT / 3 * 2 ),
                typelib::coord2Int_t::ZERO()
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


    // ���������� � �������
    // # ���������� � ������� ������������� �� ����� �����.
    mContainerSet.clear();
    mRemainsSet.clear();
    typelib::coord2_t  coord( 0, 0 );
    const auto& needVisualSize = mLevel->mCell;
    for (auto itr = mLevel->mMap.cbegin();
         itr != mLevel->mMap.cend();  ++itr
    ) {
        const Level::row_t&  row = *itr;
        // # ��������� ��������� ������ ������.
        for (auto rtr = row.cbegin(); rtr != row.cend(); ++rtr) {
            const Level::sign_t  sign = *rtr;
#ifdef _DEBUG
            //CONSOLE << "Cell " << coord << " '" << sign << "'" << std::endl;
#endif
            // # ������ '.' �������� "������ ������".
            if (sign != '.') {
                const auto ftr = mLevel->mAboutSetSign.find( sign );
                ASSERT( (ftr != mLevel->mAboutSetSign.cend())
                    && "���������� � ���������� �����������." );
                const Level::AboutSet&  about = ftr->second;
                std::unique_ptr< Container >  container;
                std::unique_ptr< Remains >    remains;
                if (about.kind == "Cube") {
                    container = std::unique_ptr< Container >( new CubeContainer(
                        this->shared_from_this(),
                        about.sprite,
                        needVisualSize,
                        mLevel->mCell.x,
                        coord,
                        typelib::coord2Int_t::ZERO()
                    ) );

                } else if (about.kind == "Sphere") {
                    container = std::unique_ptr< Container >( new SphereContainer(
                        this->shared_from_this(),
                        about.sprite,
                        needVisualSize,
                        mLevel->mCell.x / 2,
                        coord,
                        typelib::coord2Int_t::ZERO()
                    ) );

                } else if (about.kind == "Remains") {
                    remains = std::unique_ptr< Remains >( new Remains(
                        about.sprite,
                        needVisualSize,
                        coord,
                        typelib::coord2Int_t::ZERO()
                    ) );

                } else {
                    ASSERT( false
                        && "��� ���������� �� ���������." );
                }

                ASSERT( ( container || remains || (sign == '.') )
                    && "���������� ����� �� ������." );

                if ( container ) {
                    mContainerSet.push_back( std::move( container ) );

                } else if ( remains ) {
                    mRemainsSet.push_back( std::move( remains ) );
                }

            } // if (sign != '.')

            coord.x += mLevel->mCell.x;
            ASSERT( ((coord.x <= mMaxCoord.x) && (coord.x >= mMinCoord.x))
                && "������� ��������� ������� �� ��������� ������ (������)." );

        } // for (auto rtr = ...

        coord.x = 0;
        coord.y += mLevel->mCell.y;
        ASSERT( ((coord.y <= mMaxCoord.y) && (coord.y >= mMinCoord.y))
            && "������� ��������� ������� �� ��������� ������ (������)." );

    } // for (auto itr = ...

    ASSERT( !mContainerSet.empty()
        && "������� �� ������ ���� ������." );


    return mLevel;
}




void
World::physicsBodyLeaveWorld( const NewtonBody* b,  int threadIndex ) {
    // ������� ���������� �����
    NewtonWorld* nw = NewtonBodyGetWorld( b );
    NewtonDestroyBody( nw, b );
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
        NewtonUpdate( mPhysics.get(),  1.0f / 60.0f );
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

    if ((keycode == KEYCODE_SPACE) && press) {
		pushRacket();

    } else if ((keycode == KEYCODE_ESC) && press) {
		MainBreak();
    }
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
    platform->mDestination.x = x - platform->needVisualSize.x / 2;
    platform->mDestination.y = y - platform->needVisualSize.y / 2;
}




void
World::movePlatformToDestination() {

    // # ��������� ������������ ����� ��� OX.
    auto& platform = mPlatformSet.front();
    const auto velocityX = platform->velocity().x;
    const float distanceX = platform->mDestination.x - platform->coord().x;
    const float forceX = distanceX * 10.0f - velocityX * 100.0f;
    platform->applyForce( typelib::vector2_t( forceX, 0 ) );
}




void
World::pushRacket() {

    auto& racket = mRacketSet.front();
    //const auto force = typelib::vector2_t( 5000, -5000 ) * racket->mass();
    const auto force = typelib::vector2_t( 0, -5000 ) * racket->mass();
    racket->pushRacket( force );
}


} // arkanoid
