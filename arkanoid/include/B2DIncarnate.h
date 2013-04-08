#pragma once


#include "GE.h"


namespace arkanoid {


class World;


/**
* ������, ������������������ � ���. ������ (� ����) Box2D.
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
    * #! ����� init() ������ ���� ����������� ������ ��������.
    */
    B2DIncarnate(
        std::shared_ptr< World >,
        sign_t  sign,
        sign_t  next
    );




    virtual ~B2DIncarnate();




    /**
    * #! ������ ���� ����������� ������ ��������.
    * # ���������� �������� � ������.
    */
    void init( const b2BodyDef&,  const b2FixtureDef& );




public:
    /**
    * �������������� ���������� �������������� �������� �� ����������.
    */
    virtual void sync() = 0;




    /**
    * ������ ������� �������� �� �������.
    */
    virtual void selfReaction( const std::string& event ) = 0;




    /**
    * ������ ������� ������������ �������� � ������ ���������.
    */
    virtual void collisionReaction( const GE* ) = 0;




    inline const b2Body* body() const {
        return mBody;
    }


    inline b2Body* body() {
        return mBody;
    }




    /**
    * @return ����� ����.
    */
    inline float mass() const {
        return mBody->GetMass();
    };




    /**
    * @return �������� �������� ����, �/�.
    */
    inline typelib::vector2_t linearVelocity() const {
        const b2Vec2 v = mBody->GetLinearVelocity();
        return typelib::vector2_t( v.x, v.y );
    };




    /**
    * @return ������� �������� ����, �/�.
    */
    inline float angularVelocity() const {
        return mBody->GetAngularVelocity();
    };




    /**
    * @return ���������� ����, �.
    */
    inline typelib::coord2_t coord() const {
        const b2Vec2& v = mBody->GetPosition();
        return typelib::coord2_t( v.x, v.y );
    };



    // # ���������� �������� � ������.
    template< typename T >
    inline void coord( T x, T y ) {
        coord( typelib::coord2_t( x, y ) );
    };




    // # ���������� �������� � ������.
    inline void coord( const typelib::coord2_t& c ) {
        // @todo optimize ��������.
        mBody->SetTransform( b2Vec2( c.x, c.y ),  mBody->GetAngle() );
    };




    /**
    * @return ���� �������� ��������, �������.
    */
    inline float rotation() const {
        return mBody->GetAngle();
    };



    
    inline void rotation( float angle ) const {
        // @todo optimize ��������.
        mBody->SetTransform( mBody->GetPosition(), angle );
    }




    /**
    * ������������ �� ���� �����.
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
    * ���. ����.
    */
    b2Body*  mBody;

};



} // arkanoid
