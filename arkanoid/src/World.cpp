#include "../include/stdafx.h"
#include "../include/Border.h"
#include "../include/Container.h"
#include "../include/Level.h"
#include "../include/Platform.h"
#include "../include/Racket.h"
#include "../include/World.h"


namespace arkanoid {


World::World( int width, int height ) :
    mPhysics( NewtonCreate() ),
    mVisual( width, height, prcore::PIXELFORMAT_ARGB8888 )
{
    ASSERT( mPhysics
        && "Не удалось инициализировать физ. движок." );

    // *физический мир*
    {
        NewtonSetPlatformArchitecture( mPhysics.get(), 0 );
	    NewtonSetSolverModel( mPhysics.get(), 0 );
        //NewtonSetMinimumFrameRate( mPhysicsWorld, 100.0f );

        // делаем физ. мир намеренно бОльшим, чем игровое окно
        // # При K = 1 физ. мир в 2 раза больше визуального.
        static const float K = 1.0f;
        static const float minmaxSX = static_cast< float >( WINDOW_WIDTH  ) * K;
        static const float minmaxSY = static_cast< float >( WINDOW_HEIGHT ) * K;
        // # Физический мир - объёмный.
        static const float minmaxSZ = static_cast< float >( WINDOW_WIDTH  ) * K;
        mMinCoord = typelib::coord2Int_t( -minmaxSX, -minmaxSY );
        mMaxCoord = typelib::coord2Int_t( minmaxSX, minmaxSY );
	    static const dgVector minSize( -minmaxSX, -minmaxSY, -minmaxSZ, 1.0f );
	    static const dgVector maxSize(  minmaxSX,  minmaxSY,  minmaxSZ, 1.0f );
	    NewtonSetWorldSize( mPhysics.get(),  &minSize[ 0 ],  &maxSize[ 0 ] );

        // материал по умолчанию для элементов физ. мира
        const int defMaterial = NewtonMaterialGetDefaultGroupID( mPhysics.get() );
        NewtonMaterialSetDefaultCollidable( mPhysics.get(), defMaterial, defMaterial, 1 );
        NewtonMaterialSetDefaultElasticity( mPhysics.get(), defMaterial, defMaterial, 0.4f );
        NewtonMaterialSetDefaultFriction(   mPhysics.get(), defMaterial, defMaterial, 1.0f, 0.5f );
        NewtonMaterialSetDefaultSoftness(   mPhysics.get(), defMaterial, defMaterial, 0.05f );

        // слушаем события из физ. мира
        NewtonSetBodyLeaveWorldEvent( mPhysics.get(), physicsBodyLeaveWorld );
    }


    // *графический мир*
    {
        OpenBuffer( width, height, "Arkanoid demo" );
    }
}




std::shared_ptr< World >
World::valueOf() {
    auto r = std::shared_ptr< World >( new World() );
    return r;
}




World::~World() {
#ifdef _DEBUG
    // грубо гасим assert'ы NewtonDynamics при выходе из приложения
    // @todo fine Сделать красиво.
    exit( 0 );
#endif
    NewtonDestroy( mPhysics.get() );
}




void
World::go() {

    const bool present = loadNextLevel();
    if ( !present ) {
        // игра пройдена
        return;
    }

    // след. уровень
    MainLoop();
}




void
World::pulse() {
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
World::loadNextLevel() {

    const size_t q = mLevel ? (mLevel->current + 1) : 1;
    mLevel = std::unique_ptr< Level >( new Level( q ) );


    // построим мир согласно полученному выше mLevel

    // границы мира
    {
        static const int  THICKNESS = 100;
        static const int  SHIFT = static_cast< int >( CELL_SIZE ) / 2;
        std::unique_ptr< Border >  top( new BoxBorder(
            this->shared_from_this(),
            // # Границы мира не рисуются.
            "",
            typelib::size2Int_t( 1, 1 ),
            typelib::size2Int_t( WINDOW_WIDTH, THICKNESS ),
            typelib::coord2Int_t( 0, -THICKNESS + SHIFT ),
            typelib::coord2_t::ZERO()
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
            typelib::coord2_t::ZERO()
        ) );
        mBorderSet.push_back( std::move( right ) );

        std::unique_ptr< Border >  left( new BoxBorder(
            this->shared_from_this(),
            "",
            typelib::size2Int_t( 1, 1 ),
            typelib::size2Int_t( THICKNESS, WINDOW_HEIGHT * 2 ),
            typelib::coord2Int_t( -THICKNESS / 2 - SHIFT, WINDOW_HEIGHT / 2 ),
            typelib::coord2_t::ZERO()
        ) );
        mBorderSet.push_back( std::move( left ) );
    }


    // платформа
    {
        std::unique_ptr< Platform >  platform;
        const Level::AboutPlatform&  about = mLevel->mAboutPlatform;
        if (about.kind == "Capsule") {
            platform = std::unique_ptr< Platform >( new CapsulePlatform(
                this->shared_from_this(),
                about.sprite,
                typelib::size2Int_t( 128, 32 ),
                typelib::size2Int_t( 128, 32 ),
                typelib::coord2Int_t( WINDOW_WIDTH / 2,  WINDOW_HEIGHT - 32 * 2 ),
                typelib::coord2_t::ZERO()
            ) );

        } else {
            ASSERT( false
                && "Вид платформы не распознан." );
        }

        ASSERT( platform
            && "Платформа не создана." );
        mPlatformSet.push_back( std::move( platform ) );
    }
    ASSERT( (mPlatformSet.size() == 1)
        && "Ожидается единственная платформа." );


    // ракетка
    {
        std::unique_ptr< Racket >  racket;
        const Level::AboutRacket&  about = mLevel->mAboutRacket;
        if (about.kind == "Sphere") {
            racket = std::unique_ptr< Racket >( new SphereRacket(
                this->shared_from_this(),
                about.sprite,
                typelib::size2Int_t( 32, 32 ),
                // # Сама ракетка меньше размера спрайта.
                (32 - 8) / 2,
                typelib::coord2Int_t( WINDOW_WIDTH / 2,  WINDOW_HEIGHT / 3 * 2 ),
                typelib::coord2_t::ZERO()
            ) );

        } else {
            ASSERT( false
                && "Вид ракетки не распознан." );
        }

        ASSERT( racket
            && "Ракетка не создана." );
        mRacketSet.push_back( std::move( racket ) );
    }
    ASSERT( (mRacketSet.size() == 1)
        && "Ожидается единственная ракетка." );


    // контейнеры
    typelib::coord2_t  coord( 0, 0 );
    const auto& needVisualSize = mLevel->mCell;
    for (auto itr = mLevel->mContainerMap.cbegin();
         itr != mLevel->mContainerMap.cend();  ++itr
    ) {
        const Level::row_t&  row = *itr;
        // # Допустимо указывать пустую строку.
        for (auto rtr = row.cbegin(); rtr != row.cend(); ++rtr) {
            const Level::sign_t  sign = *rtr;
#ifdef _DEBUG
            CONSOLE << "Cell " << coord << " '" << sign << "'" << std::endl;
#endif
            // # Символ '.' означает "пустая ячейка".
            if (sign != '.') {
                const auto ftr = mLevel->mAboutContainerSign.find( sign );
                ASSERT( (ftr != mLevel->mAboutContainerSign.cend())
                    && "Информация о контейнере отсутствует." );
                const Level::AboutContainer&  about = ftr->second;
                std::unique_ptr< Container >  container;
                if (about.kind == "Cube") {
                    container = std::unique_ptr< Container >( new CubeContainer(
                        this->shared_from_this(),
                        about.sprite,
                        needVisualSize,
                        mLevel->mCell.x,
                        coord,
                        typelib::coord2_t::ZERO()
                    ) );

                } else if (about.kind == "Sphere") {
                    container = std::unique_ptr< Container >( new SphereContainer(
                        this->shared_from_this(),
                        about.sprite,
                        needVisualSize,
                        mLevel->mCell.x / 2,
                        coord,
                        typelib::coord2_t::ZERO()
                    ) );

                } else {
                    ASSERT( false
                        && "Вид контейнера не распознан." );
                }

                ASSERT( ( container || (sign == '.') )
                    && "Подходящий контейнер не создан." );
                mContainerSet.push_back( std::move( container ) );

            } // if (sign != '.')

            coord.x += mLevel->mCell.x;
            ASSERT( ((coord.x <= mMaxCoord.x) && (coord.x >= mMinCoord.x))
                && "Попытка поместить элемент за пределами уровня (ширина)." );

        } // for (auto rtr = ...

        coord.x = 0;
        coord.y += mLevel->mCell.y;
        ASSERT( ((coord.y <= mMaxCoord.y) && (coord.y >= mMinCoord.y))
            && "Попытка поместить элемент за пределами уровня (высота)." );

    } // for (auto itr = ...

    ASSERT( !mContainerSet.empty()
        && "Уровень не должен бть пустым." );


    return mLevel;
}




void
World::physicsBodyLeaveWorld( const NewtonBody* b,  int threadIndex ) {
    // удаляем физический образ
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

    static const uint32 bgColor = 0xFF5DA130;
    mVisual.ClearImage( bgColor );


    // физика
    {
        movePlatformDestination();
        NewtonUpdate( mPhysics.get(),  1.0f / 100.0f );
    }

    // графика
    {
        // # Границы мира не рисуются.

        for (auto ctr = mContainerSet.cbegin();
             ctr != mContainerSet.cend(); ++ctr
        ) {
            ( *ctr )->draw( mVisual );
        }

        for (auto ptr = mPlatformSet.cbegin();
             ptr != mPlatformSet.cend(); ++ptr
        ) {
            ( *ptr )->draw( mVisual );
        }

        for (auto rtr = mRacketSet.cbegin();
             rtr != mRacketSet.cend(); ++rtr
        ) {
            ( *rtr )->draw( mVisual );
        }
    }


    BlitWrite( 0, 0, mVisual );
	PageFlip();

    pulse();
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
    // точка назначения - по центру платформы
    platform->mDestination.x = x - platform->needVisualSize.x / 2;
    platform->mDestination.y = y - platform->needVisualSize.y / 2;
}




void
World::movePlatformDestination() {

    // # Платформа перемещается вдоль оси OX.
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
