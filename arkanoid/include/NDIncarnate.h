#pragma once


#include "configure.h"
#include "Material.h"


namespace arkanoid {


class CollidableMaterial;
class Material;
class World;


/**
* Объект, зарегистрированный в движке (в мире) Newton Dynamics.
*
* Работаем как с 2D-телом в плоскости XZ (z в 3D = y в 2D).
*
* @see http://newtondynamics.com/forum/viewtopic.php?f=15&t=1102
*/
class NDIncarnate {
protected:
    NDIncarnate(
        std::shared_ptr< World >,
        // #! 'collision' будет разрушена.
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
    * @return Масса тела.
    */
    inline float mass() const {
        float m, ix, iy, iz;
        NewtonBodyGetMassMatrix( mBody, &m, &ix, &iy, &iz );
        return m;
    };




    /**
    * @return Материал.
    */
    inline uidMaterial_t uidMaterial() const {
        return mUIDMaterial;
    };


    inline const Material* material() const {
        return mMaterial.get();
    };




    /**
    * @return Координаты тела.
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
    * @return Углы поворота элемента по XY в радианах.
    */
    inline typelib::coord2_t rotation() const {
        float tm[ 16 ];
        NewtonBodyGetMatrix( mBody, tm );
        const dgMatrix t = ( dgMatrix )( tm );
        const dgVector v = t.CalcPitchYawRoll();

        return typelib::coord2_t( v.m_x, v.m_z );
    }




    /**
    * @return Скорость тела.
    */
    inline typelib::vector2_t velocity() const {
        float v[ 3 ];
        NewtonBodyGetVelocity( mBody, v );

        return typelib::vector2_t( v[ 0 ],  v[ 2 ] );
    };




    /**
    * Воздействует на тело силой.
    */
    inline void applyForce( const typelib::vector2_t&  force ) {
        mForce = force;
    }

    inline void applyAddForce( const typelib::vector2_t&  force ) {
        mForce += force;
    }




    /**
    * @return Взаимодействие тела с другими телами.
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
        // достаточно сравнить указатели физ. тел
        return (mBody == b.body());
    }





protected:
    /**
    * Тело может генерировать свои собственные силы.
    * Вызывается каждый такт.
    */
    virtual void applyForceAndTorque();


    /**
    * Метод вызывается движком при любом изменении положения тела
    * (значения в 'matrix').
    */
    virtual void setTransform( const dgMatrix&  matrix ) = 0;


    //virtual void autoActivation( size_t state ) = 0;


    /**
    * Вызывается при столкновении тел.
    */
    virtual void contactProcess(
        NDIncarnate*  other,
        const NewtonJoint*  contactJoint
    ) = 0;





    /**
    * Инициирует матрицу.
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
            && "Тело не найдено." );
        body->applyForceAndTorque();
    }




    static inline void setTransform(
        const NewtonBody*  b,
        const float*  matrix,
        int  threadIndex
    ) {
        auto body = static_cast< NDIncarnate* >( NewtonBodyGetUserData( b ) );
        ASSERT( body
            && "Тело не найдено." );
#if 1
        dgMatrix& m = *( ( dgMatrix* )( matrix ) );
        // # y = 0
        m.m_posit.m_y = 0.0f;
#else
        // корректируем координаты и углы поворота тела: работаем в 2D
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
        //    && "Тело не найдено." );
        // предотвращаем бесконечную рекурсию, удаляем физ. тело
        NewtonBodySetDestructorCallback( b, nullptr );
        NewtonBodySetUserData( b, nullptr );
        /* - @todo fine optimize Не удаляет корректно. Разобраться.
        delete b;
        */
    }




protected:
    std::weak_ptr< World >  mWorld;


    /**
    * Физ. тело.
    */
    NewtonBody*  mBody;


    /**
    * Сила, действующая сейчас на тело.
    *
    * # Все перемещения выполняются из-за действия сил.
    */
    typelib::vector2_t  mForce;


    /**
    * Материал физ. тела.
    */
    const int  mUIDMaterial;
    const std::unique_ptr< Material >  mMaterial;


    /**
    * Взаимодействие с другими материалами.
    */
    const std::unique_ptr< CollidableMaterial >  mCollidableMaterial;
};



} // arkanoid
