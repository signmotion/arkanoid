#pragma once


#include "GE.h"


namespace arkanoid {


class World;


/**
* Объект, зарегистрированный в физ. движке (в мире) Box2D.
*
* @see http://box2d.org
*/
class B2DIncarnate :
    public GE
{
public:
    typedef std::vector< typelib::coord2_t >  polygon_t;




protected:
    /**
    * #! Метод init() должен быть обязательно вызван потомком.
    */
    B2DIncarnate(
        std::shared_ptr< World >,
        sign_t  sign,
        sign_t  next
    );




    virtual ~B2DIncarnate();




    /**
    * #! Должен быть обязательно вызван потомком.
    * # Координаты задаются в метрах.
    */
    void init( const b2BodyDef&,  const b2FixtureDef& );




public:
    /**
    * Синхронизирует визуальные характеристики элемента по физическим.
    */
    virtual void sync() = 0;




    /**
    * Играет реакцию элемента на событие.
    */
    virtual void selfReaction( const std::string& event ) = 0;




    /**
    * Играет реакцию столкновения элемента с другим элементом.
    */
    virtual void collisionReaction( const GE* ) = 0;




    inline const b2Body* body() const {
        return mBody;
    }


    inline b2Body* body() {
        return mBody;
    }




    /**
    * @return Масса тела.
    */
    inline float mass() const {
        return mBody->GetMass();
    };




    /**
    * @return Линейная скорость тела, м/с.
    */
    inline typelib::vector2_t linearVelocity() const {
        const b2Vec2 v = mBody->GetLinearVelocity();
        return typelib::vector2_t( v.x, v.y );
    };




    /**
    * @return Угловая скорость тела, м/с.
    */
    inline float angularVelocity() const {
        return mBody->GetAngularVelocity();
    };




    /**
    * @return Координаты тела, м.
    */
    inline typelib::coord2_t coord() const {
        const b2Vec2& v = mBody->GetPosition();
        return typelib::coord2_t( v.x, v.y );
    };



    // # Координаты задаются в метрах.
    template< typename T >
    inline void coord( T x, T y ) {
        coord( typelib::coord2_t( x, y ) );
    };




    // # Координаты задаются в метрах.
    inline void coord( const typelib::coord2_t& c ) {
        // @todo optimize Напрямую.
        mBody->SetTransform( b2Vec2( c.x, c.y ),  mBody->GetAngle() );
    };




    /**
    * @return Угол поворота элемента, радианы.
    */
    inline float rotation() const {
        return mBody->GetAngle();
    };



    
    inline void rotation( float angle ) const {
        // @todo optimize Напрямую.
        mBody->SetTransform( mBody->GetPosition(), angle );
    }




    /**
    * Воздействует на тело силой.
    */
    inline void applyForce( const typelib::vector2_t&  force ) {
        mBody->ApplyForceToCenter( b2Vec2( force.x, force.y ) );
    }




    const b2World* world() const;

    b2World* world();




    inline bool operator==( const B2DIncarnate& b ) const {
        return (body() == b.body());
    }




protected:
    std::weak_ptr< World >  mWorld;


    /**
    * Физ. тело.
    */
    b2Body*  mBody;

};



} // arkanoid
