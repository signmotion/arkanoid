#pragma once

#include "configure.h"
#include "structure.h"


namespace arkanoid {


class Background;
class Border;
class Container;
class Level;
class PIncarnate;
class Platform;
class Racket;
class Remains;


/**
* ����� ��� ������ � ������� �����.
*/
class World :
    public std::enable_shared_from_this< World >,
    private prcore::FrameBuffer,
    private b2ContactListener
{
public:
    typedef std::unique_ptr< Background >              background_t;

    typedef std::list< std::unique_ptr< Border > >     borderSet_t;
    typedef std::list< std::unique_ptr< Container > >  containerSet_t;
    typedef std::list< std::unique_ptr< Platform > >   platformSet_t;
    typedef std::list< std::unique_ptr< Racket > >     racketSet_t;
    typedef std::list< std::unique_ptr< Remains > >    remainsSet_t;




    typedef b2Body*  impact_t;
    static const size_t MAX_IMPACT = 512;




    struct ContactPoint {
	    b2Fixture*    a;
	    b2Fixture*    b;
	    b2Vec2        normal;
	    b2Vec2        position;
	    b2PointState  state;
    };
    static const size_t MAX_CONTACT_POINT = 2048;




    /**
    * ���������� ���������� �� �����.
    */
    struct Statistics {
        size_t  destructible;
        size_t  indestructible;
    };




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




    std::shared_ptr< b2World >  physics();
    std::shared_ptr< const b2World >  physics() const;




    /**
    * ��������� ����. �������.
    *
    * @param startLevel ���� ������, ���� ���������� � ����� ������.
    *
    * @return false ���� ������� ������ ���.
    */
    bool loadNextLevel( size_t startLevel = 1 );




    /**
    * @return ���������� �� ���������� �����������.
    */
    Statistics statistics() const;




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
	inline virtual void BeginContact( b2Contact* contact ) {
    }


	inline virtual void EndContact( b2Contact* contact ) {
    }


	virtual void PreSolve(
        b2Contact*         contact,
        const b2Manifold*  oldManifold
    );


	virtual void PostSolve(
        const b2Contact*         contact,
        const b2ContactImpulse*  impulse
    );




    /**
    * @return ����� � ������� (Frame Per Second).
    */
    static size_t World::calcFPS( size_t frameTime );




    void setPlatformDestination( int x, int y );

    void movePlatformToDestination();

    void pushRacket( bool always );




    /**
    * ��������� � ���� ������� �� ��������� �����.
    * # ������� ������ ���� ��������.
    */
    void incarnate( sign_t,  const typelib::coord2Int_t& );




    /**
    * @return ������� �������. ������������ �� ���������� �����������.
    */
    bool completed() const;




    /**
    * @return ������� �������� ������� ����.
    */
    bool out( const Racket& ) const;




    /**
    * ������� ��������� ������� �� ����. �� ��� ����� ����� ����
    * ������ �����.
    *
    * # ���� ��� ���������� �� ������ next(), �. ��������. � ���������
    *   ������ �� ����� ���������� ���������� ������� � ������ �� next().
    * # ���� next() ���������� ����� ����� �� ����������, �. ������� � ����.
    */
    void reincarnateOrDie( b2Body* );




    /**
    * ���������� ��������� ������.
    */
    void levelCompletedAction();
    void racketOutAction();




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


    /**
    * �������� ����, �� ������� ���� ������� �����������.
    */
    impact_t  mImpactSet[ MAX_IMPACT ];
    size_t    mImpactCount;


    std::shared_ptr< b2World >  mPhysics;
	ContactPoint  mContactPointSet[ MAX_CONTACT_POINT ];
	size_t        mContactPointCount;


    /**
    * ��������� ������� �������.
    */
    static const typelib::coord2Int_t  mStartCoordRacket;


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
