#pragma once

#include "configure.h"


namespace arkanoid {


class Border;
class Container;
class Level;
class Platform;
class Racket;


/**
* Класс для работы с игровым миром.
*/
class World :
    public std::enable_shared_from_this< World >,
    private prcore::FrameBuffer
{
public:
    typedef std::list< std::unique_ptr< Border > >     borderSet_t;
    typedef std::list< std::unique_ptr< Container > >  containerSet_t;
    typedef std::list< std::unique_ptr< Platform > >   platformSet_t;
    typedef std::list< std::unique_ptr< Racket > >     racketSet_t;




protected:
    World( int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT );




public:
    // Для инициализации this->shared_from_this()
    static std::shared_ptr< World >  valueOf();




    virtual ~World();




    /**
    * Оживляет мир.
    */
	void go();
    void pulse();




    std::shared_ptr< NewtonWorld >  physics();
    std::shared_ptr< const NewtonWorld >  physics() const;




    /**
    * Загружает след. уровень.
    *
    * @return false если уровней больше нет.
    */
    bool loadNextLevel();




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
    static inline int currentTime() {
        return mCurrentTime;
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
    void movePlatformDestination();
    void pushRacket();




private:
    std::unique_ptr< Level >  mLevel;


    prcore::Bitmap  mVisual;


    /**
    * Элементы мира.
    */
    borderSet_t     mBorderSet;
    containerSet_t  mContainerSet;
    platformSet_t   mPlatformSet;
    racketSet_t     mRacketSet;


    std::shared_ptr< NewtonWorld >  mPhysics;
    typelib::coord2Int_t  mMinCoord;
    typelib::coord2Int_t  mMaxCoord;


    /**
    * Текущее время, мс.
    * Может использоваться для корректного тайминга.
    */
    static int mCurrentTime;
};


} // arkanoid
