namespace boost {

template< typename Number >
inline std::size_t hash_value( const typelib::VectorT< Number >& a ) {
    return hash_value( static_cast< typelib::CoordT< Number > >( a ) );
}


} // boost






namespace typelib {


template< typename Number >
inline VectorT< Number >::operator vectorDouble_t () const {
    return vectorDouble_t( x, y, z );
}



template< typename Number >
inline VectorT< Number >::operator vector_t () const {
    return vector_t( x, y, z );
}



template< typename Number >
inline VectorT< Number >::operator vectorInt_t () const {
    return vectorInt_t( x, y, z );
}




template< typename Number >
inline Number VectorT< Number >::estimateLength() const {
    return estimateDistance();
}




template< typename Number >
inline Number VectorT< Number >::squareLength() const {
    return squareDistance();
}



template< typename Number >
inline Number VectorT< Number >::length() const {
    return distance();
}



template< typename Number >
inline Number VectorT< Number >::normalize() {
    const Number l = length();
    if (l > static_cast< Number >( 0 )) {
        const Number il = static_cast< Number >( 1 ) / l;
        x *= il;
        y *= il;
        z *= il;
    }
    return l;
}




template< typename Number >
inline Number VectorT< Number >::dot( const VectorT< Number >& v ) const {
    return x * v.x + y * v.y + z * v.z;
}




template< typename Number >
inline VectorT< Number > VectorT< Number >::cross( const VectorT< Number >& v ) const {
    return VectorT< Number >(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}




template< typename Number >
inline VectorT< Number > VectorT< Number >::perpendicular() const {
    VectorT< Number > p = this->cross( VectorT< Number >::UNIT_X() );
    if (p.estimateLength() < PRECISION) {
        p = this->cross( VectorT< Number >::UNIT_Y() );
    }
    p.normalize();

    return p;
}




template< typename Number >
inline Number VectorT< Number >::angle( const VectorT< Number >& v ) const {
    Number ll = length() * v.length();
    if (ll < PRECISION) {
        ll = PRECISION;
    }
    Number f = dot( v ) / ll;
    f = typelib::clamp( f, -1.0, 1.0 );

    return std::acos( f );
}



} // typelib






namespace std {


template< typename Number >
inline std::ostream& operator<<( std::ostream& out, const typelib::VectorT< Number >& c ) {
    out << "[ " << c.x << ", " << c.y << ", " << c.z << " ]";
    return out;
}


} // std
