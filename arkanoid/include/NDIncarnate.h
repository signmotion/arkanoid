#pragma once


#include "configure.h"
#include "Material.h"


namespace arkanoid {


class CollidableMaterial;
class Material;
class World;


/**
* ������, ������������������ � ������ (� ����) Newton Dynamics.
*
* �������� ��� � 2D-����� � ��������� XZ (z � 3D = y � 2D).
*
* @see http://newtondynamics.com/forum/viewtopic.php?f=15&t=1102
*/
class NDIncarnate {
protected:
    NDIncarnate(
        std::shared_ptr< World >,
        // #! 'collision' ����� ���������.
        NewtonCollision*            collision,
        float                       mass,
        const typelib::coord2_t&    coord,
        const typelib::coord2_t&    rotation,
        const typelib::vector2_t&   momentInertia,
        std::unique_ptr< Material >
    );




    virtual ~NDIncarnate();




public:

    inline const NewtonBody* body() const {
        return mBody;
    }




    inline NewtonBody* body() {
        return mBody;
    }




    /**
    * @return ����� ����.
    */
    inline float mass() const {
        float m, ix, iy, iz;
        NewtonBodyGetMassMatrix( mBody, &m, &ix, &iy, &iz );
        return m;
    };




    /**
    * @return ��������.
    */
    inline uidMaterial_t uidMaterial() const {
        return mUIDMaterial;
    };


    inline const Material* material() const {
        return mMaterial.get();
    };




    /**
    * @return ���������� ����.
    */
    inline typelib::coord2_t coord() const {
        float tm[16];
        NewtonBodyGetMatrix( mBody, tm );

        return typelib::coord2_t( tm[12], tm[14] );
    };




    template< typename T >
    inline void coord( T x, T y ) {
        coord( typelib::coord2_t( x, y ) );
    };




    inline void coord( const typelib::coord2_t& c ) {
        float tm[16];
        NewtonBodyGetMatrix( mBody, tm );
        tm[12] = c.x;
        //tm[13] = c.y;
        tm[14] = c.y;
        NewtonBodySetMatrix( mBody, tm );
    };




    /**
    * @return ���� �������� �������� �� XY � ��������.
    */
    inline typelib::coord2_t rotation() const {
        float tm[ 16 ];
        NewtonBodyGetMatrix( mBody, tm );
        const dgMatrix t = ( dgMatrix )( tm );
        const dgVector v = t.CalcPitchYawRoll();

        return typelib::coord2_t( v.m_x, v.m_z );
    }




    /**
    * @return �������� ����.
    */
    inline typelib::vector2_t velocity() const {
        float v[ 3 ];
        NewtonBodyGetVelocity( mBody, v );

        return typelib::vector2_t( v[ 0 ],  v[ 2 ] );
    };




    /**
    * ������������ �� ���� �����.
    */
    inline void applyForce( const typelib::vector2_t&  force ) {
        mForce = force;
    }

    inline void applyAddForce( const typelib::vector2_t&  force ) {
        mForce += force;
    }




    /**
    * @return �������������� ���� � ������� ������.
    */
    inline const CollidableMaterial* collidableMaterial() const {
        return mCollidableMaterial.get();
    };




    inline void getTM( float tm[ 16 ] ) const {
        NewtonBodyGetMatrix( mBody, tm );
    }




    inline void setTM( const float tm[16] ) {
        NewtonBodySetMatrix( mBody, tm );
    }




    const NewtonWorld* world() const;




    NewtonWorld* world();




    inline bool operator==( const NDIncarnate& b ) const {
        // ���������� �������� ��������� ���. ���
        return (mBody == b.body());
    }





protected:
    /**
    * ���� ����� ������������ ���� ����������� ����.
    * ���������� ������ ����.
    */
    virtual void applyForceAndTorque();


    /**
    * ����� ���������� ������� ��� ����� ��������� ��������� ����
    * (�������� � 'matrix').
    */
    virtual void setTransform( const dgMatrix&  matrix ) = 0;


    //virtual void autoActivation( size_t state ) = 0;


    /**
    * ���������� ��� ������������ ���.
    */
    virtual void contactProcess(
        NDIncarnate*  other,
        const NewtonJoint*  contactJoint
    ) = 0;





    /**
    * ���������� �������.
    */
    static void init(
        float tm[ 16 ],
        const typelib::coord2_t&  coord,
        const typelib::coord2_t&  rotation
    );




    static void contactProcess(
        const NewtonJoint*  contactJoint,
        float  timestep,
        int    threadIndex
    );




private:
    static inline void applyForceAndTorque(
        const NewtonBody*  b,
        float  timestep,
        int    threadIndex
    ) {
        auto body = static_cast< NDIncarnate* >( NewtonBodyGetUserData( b ) );
        ASSERT( body
            && "���� �� �������." );
        body->applyForceAndTorque();
    }




    static inline void setTransform(
        const NewtonBody*  b,
        const float*  matrix,
        int  threadIndex
    ) {
        auto body = static_cast< NDIncarnate* >( NewtonBodyGetUserData( b ) );
        ASSERT( body
            && "���� �� �������." );
#if 1
        dgMatrix& m = *( ( dgMatrix* )( matrix ) );
        // # y = 0
        m.m_posit.m_y = 0.0f;
#else
        // ������������ ���������� � ���� �������� ����: �������� � 2D
        const dgMatrix m(
            dgVector( matrix[0],  matrix[1],  0,  0 ),
            dgVector( matrix[4],  matrix[5],  0,  0 ),
            dgVector( 0,          0,          1,  0 ),
            dgVector( matrix[12], matrix[13], 0,  0 )
        );
        NewtonBodySetMatrix( b, &m[0][0] );
#endif
        body->setTransform( m );
    }




    static inline void autoDestruction( const NewtonBody* b ) {
        //auto body = static_cast< NDIncarnate* >( NewtonBodyGetUserData( b ) );
        //ASSERT( body
        //    && "���� �� �������." );
        // ������������� ����������� ��������, ������� ���. ����
        NewtonBodySetDestructorCallback( b, nullptr );
        NewtonBodySetUserData( b, nullptr );
        /* - @todo fine optimize �� ������� ���������. �����������.
        delete b;
        */
    }




protected:
    std::weak_ptr< World >  mWorld;


    /**
    * ���. ����.
    */
    NewtonBody*  mBody;


    /**
    * ����, ����������� ������ �� ����.
    *
    * # ��� ����������� ����������� ��-�� �������� ���.
    */
    typelib::vector2_t  mForce;


    /**
    * �������� ���. ����.
    */
    const int  mUIDMaterial;
    const std::unique_ptr< Material >  mMaterial;


    /**
    * �������������� � ������� �����������.
    */
    const std::unique_ptr< CollidableMaterial >  mCollidableMaterial;
};



} // arkanoid
