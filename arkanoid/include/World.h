#pragma once

#include "configure.h"


namespace arkanoid {


class Background;
class Border;
class Container;
class Level;
class Platform;
class Racket;
class Remains;


/**
* Класс для работы с игровым миром.
*/
class World :
    public std::enable_shared_from_this< World >,
    private prcore::FrameBuffer
{
public:
    typedef std::unique_ptr< Background >              background_t;

    typedef std::list< std::unique_ptr< Border > >     borderSet_t;
    typedef std::list< std::unique_ptr< Container > >  containerSet_t;
    typedef std::list< std::unique_ptr< Platform > >   platformSet_t;
    typedef std::list< std::unique_ptr< Racket > >     racketSet_t;
    typedef std::list< std::unique_ptr< Remains > >    remainsSet_t;




protected:
    World( int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT );




public:
    // Для инициализации this->shared_from_this()
    static std::shared_ptr< World >  valueOf();




    virtual ~World();




    /**
    * Оживляет мир.
    */
	void go( size_t startLevel );




    std::shared_ptr< NewtonWorld >  physics();
    std::shared_ptr< const NewtonWorld >  physics() const;




    /**
    * Загружает след. уровень.
    *
    * @param startLevel Если указан, игра начинается с этого уровня.
    *
    * @return false если уровней больше нет.
    */
    bool loadNextLevel( size_t startLevel = 1 );




    /**
    * Рендеринг с Twilight Prophecy SDK.
    */
    bool EventMain();
    void EventDraw();
    void EventKeyboard( int keycode,  char charcode,  bool press );
    void EventSize( int width, int height );
    void EventMouseButton(
        int mx, int my,
        prcore::MouseButton,
        int count
    );




    /**
    * @return Текущее время в мире, мс.
    */
    static inline size_t currentTime() {
        return mTimer.GetTick();
    }




private:
    /**
    * Слушатели событий физического мира.
    */
    static void physicsBodyLeaveWorld( const NewtonBody*,  int threadIndex );




    /**
    * @return Кадры в секунду (Frame Per Second).
    */
    static size_t World::calcFPS( size_t frameTime );




private:
    void setPlatformDestination( int x, int y );
    void movePlatformToDestination();
    void pushRacket();




private:
    std::unique_ptr< Level >  mLevel;


    prcore::Bitmap  mVisual;


    /**
    * Элементы мира.
    */
    background_t    mBackground;

    borderSet_t     mBorderSet;
    containerSet_t  mContainerSet;
    platformSet_t   mPlatformSet;
    racketSet_t     mRacketSet;
    remainsSet_t    mRemainsSet;


    std::shared_ptr< NewtonWorld >  mPhysics;
    typelib::coord2Int_t  mMinCoord;
    typelib::coord2Int_t  mMaxCoord;


    /**
    * Название окна.
    */
    static const std::string  mTitleWindow;


    /**
    * Текущее время, мс.
    * Может использоваться для корректного тайминга.
    */
    static const prcore::Timer  mTimer;
};


} // arkanoid
