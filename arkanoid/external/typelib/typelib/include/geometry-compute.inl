namespace typelib {
    namespace compute {
        namespace geometry {
            namespace ellipsoid {


inline real_t volume( real_t ra,  real_t rb,  real_t rc ) {
    return 4.0f / 3.0f * (constant::pi * ra * rb * rc);
}




inline real_t radiusByVolume( real_t volume,  real_t ra,  real_t rb ) {
    return (3.0f * volume) / (4.0f * constant::pi * ra * rb);
}


            } // ellipsoid
        } // geometry
    } // compute
} // typelib
