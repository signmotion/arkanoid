#pragma once

#include "configure.h"


namespace arkanoid {


/**
* UID материала.
*/
typedef int  uidMaterial_t;




/**
* Материал элемента игры.
*/
class Material {
protected:
    Material(
        float elasticity,
        float staticFriction,
        float dynamicFriction,
        float softness
    );




public:
    static std::unique_ptr< Material >  valueOf(
        float elasticity = 0.00001f,
        float staticFriction = 0.00001f,
        float dynamicFriction = 0.00001f,
        float softness = 0.00001f
    );




    virtual inline ~Material() {
    }




    inline float elasticity() const {
        return mElasticity;
    }




    inline float staticFriction() const {
        return mStaticFriction;
    }




    inline float dynamicFriction() const {
        return mDynamicFriction;
    }




    inline float softness() const {
        return mSoftness;
    }




    /**
    * @return Материал, составленный по двум исходным.
    */
    inline std::unique_ptr< Material >  operator+( const Material& b ) const {
        return Material::valueOf(
            (mElasticity      + b.elasticity()      ) / 2.0f,
            (mStaticFriction  + b.staticFriction()  ) / 2.0f,
            (mDynamicFriction + b.dynamicFriction() ) / 2.0f,
            (mSoftness        + b.softness()        ) / 2.0f
        );
    }




protected:
    const float mElasticity;
    const float mStaticFriction;
    const float mDynamicFriction;
    const float mSoftness;
};


} // arkanoid








namespace std {

inline std::ostream& operator<<(
    std::ostream& out,
    const arkanoid::Material& cm
) {
    out <<
        " e"  << cm.elasticity() <<
        " sf" << cm.staticFriction() <<
        " df" << cm.dynamicFriction() <<
        " s"  << cm.softness()
    ;
    return out;
}

} // std








namespace boost {

inline size_t hash_value( const arkanoid::Material& m ) {
    size_t seed = hash_value( m.elasticity() );
    hash_combine( seed, m.staticFriction() );
    hash_combine( seed, m.dynamicFriction() );
    hash_combine( seed, m.softness() );
    return seed;
}

} // boost
