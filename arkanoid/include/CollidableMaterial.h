#pragma once

#include "configure.h"
#include "Material.h"


namespace arkanoid {


/**
* Как взаимодействует пара материалов элементов игры.
*/
class CollidableMaterial {
public:
    /**
    * UID материалов, с которым происходит взаимодействие.
    */
    typedef std::map<
        uidMaterial_t,
        std::unique_ptr< Material >
    >  to_t;




protected:
    CollidableMaterial(
        uidMaterial_t,
        // #! Список будет разрушен: std::unique_ptr.
        to_t&,
        uidMaterial_t  uidDefMaterial,
        std::unique_ptr< Material >  defMaterial
    );




    CollidableMaterial(
        uidMaterial_t,
        uidMaterial_t  uidDefMaterial,
        std::unique_ptr< Material >  defMaterial
    );




public:
    static std::unique_ptr< CollidableMaterial >  valueOf(
        uidMaterial_t,
        // #! Список будет разрушен: std::unique_ptr.
        to_t&,
        uidMaterial_t  uidDefMaterial = 0,
        std::unique_ptr< Material >  defMaterial = nullptr
    );




    static std::unique_ptr< CollidableMaterial >  valueOf(
        uidMaterial_t,
        uidMaterial_t  uidDefMaterial,
        std::unique_ptr< Material >  defMaterial
    );




    virtual inline ~CollidableMaterial() {
    }




    inline uidMaterial_t it() const {
        return mIt;
    }




    inline to_t const& to() const {
        return mTo;
    }




    inline uidMaterial_t uidDefMaterial() const {
        return mDef.first;
    }




    inline Material* defMaterial() const {
        return mDef.second.get();
    }




protected:
    const uidMaterial_t  mIt;
    to_t  mTo;

    /**
    * Значения по умолчанию.
    */
    const to_t::value_type  mDef;
};



} // arkanoid








namespace std {

inline std::ostream& operator<<(
    std::ostream&  out,
    const arkanoid::CollidableMaterial&  cm
) {
    out << cm.it() << " (" << cm.to().size() << ")";
    return out;
}

} // std








namespace boost {

inline size_t hash_value( const arkanoid::CollidableMaterial& cm ) {
    size_t seed = hash_value( cm.it() );
    for (auto itr = cm.to().cbegin(); itr != cm.to().cend(); ++itr) {
        hash_combine( seed, itr->first );
        hash_combine( seed, itr->second );
    }
    hash_combine( seed, cm.uidDefMaterial() );
    hash_combine( seed, cm.defMaterial() );
    return seed;
}

} // boost
