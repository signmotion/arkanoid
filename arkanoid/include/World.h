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
* Класс для работы с игровым миром.
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
    * Оставшиеся контейнеры по типам.
    */
    struct Statistics {
        size_t  destructible;
        size_t  indestructible;
    };




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




    std::shared_ptr< b2World >  physics();
    std::shared_ptr< const b2World >  physics() const;




    /**
    * Загружает след. уровень.
    *
    * @param startLevel Если указан, игра начинается с этого уровня.
    *
    * @return false если уровней больше нет.
    */
    bool loadNextLevel( size_t startLevel = 1 );




    /**
    * @return Статистика по оставшимся контейнерам.
    */
    Statistics statistics() const;




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
    * @return Кадры в секунду (Frame Per Second).
    */
    static size_t World::calcFPS( size_t frameTime );




    void setPlatformDestination( int x, int y );

    void movePlatformToDestination();

    void pushRacket( bool always );




    /**
    * Воплощает в мире элемент по указанной метке.
    * # Уровень должен быть загружен.
    */
    void incarnate( sign_t,  const typelib::coord2Int_t& );




    /**
    * @return Уровень пройден. Определяется по оставшимся контейнерам.
    */
    bool completed() const;




    /**
    * @return Ракетка покинула границы мира.
    */
    bool out( const Racket& ) const;




    /**
    * Удаляет указанный элемент из мира. На его месте может быть
    * создан новый.
    *
    * # Если для контейнера не указан next(), к. исчезает. В противном
    *   случае на месте контейнера появляется элемент с меткой из next().
    * # Если next() возвращает метку этого же контейнера, к. остаётся в мире.
    */
    void reincarnateOrDie( b2Body* );




    /**
    * Показывает сообщения игроку.
    */
    void levelCompletedAction();
    void racketOutAction();




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


    /**
    * Элементы мира, на которые было оказано воздействие.
    */
    impact_t  mImpactSet[ MAX_IMPACT ];
    size_t    mImpactCount;


    std::shared_ptr< b2World >  mPhysics;
	ContactPoint  mContactPointSet[ MAX_CONTACT_POINT ];
	size_t        mContactPointCount;


    /**
    * Начальная позиция ракетки.
    */
    static const typelib::coord2Int_t  mStartCoordRacket;


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
