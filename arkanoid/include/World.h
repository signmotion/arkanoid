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
* ����� ��� ������ � ������� �����.
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
    // ��� ������������� this->shared_from_this()
    static std::shared_ptr< World >  valueOf();




    virtual ~World();




    /**
    * �������� ���.
    */
	void go( size_t startLevel );




    std::shared_ptr< NewtonWorld >  physics();
    std::shared_ptr< const NewtonWorld >  physics() const;




    /**
    * ��������� ����. �������.
    *
    * @param startLevel ���� ������, ���� ���������� � ����� ������.
    *
    * @return false ���� ������� ������ ���.
    */
    bool loadNextLevel( size_t startLevel = 1 );




    /**
    * ��������� � Twilight Prophecy SDK.
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
    * @return ������� ����� � ����, ��.
    */
    static inline size_t currentTime() {
        return mTimer.GetTick();
    }




private:
    /**
    * ��������� ������� ����������� ����.
    */
    static void physicsBodyLeaveWorld( const NewtonBody*,  int threadIndex );




    /**
    * @return ����� � ������� (Frame Per Second).
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
    * �������� ����.
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
    * �������� ����.
    */
    static const std::string  mTitleWindow;


    /**
    * ������� �����, ��.
    * ����� �������������� ��� ����������� ��������.
    */
    static const prcore::Timer  mTimer;
};


} // arkanoid
