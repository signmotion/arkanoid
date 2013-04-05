namespace boost {

template< typename Number >
inline std::size_t hash_value( const typelib::Vector2T< Number >& a ) {
    return hash_value( static_cast< typelib::Coord2T< Number > >( a ) );
}


} // boost






namespace typelib {


template< typename Number >
inline Vector2T< Number >::operator vector2Double_t () const {
    return vectorDouble_t( x, y );
}



template< typename Number >
inline Vector2T< Number >::operator vector2_t () const {
    return vector_t( x, y );
}



template< typename Number >
inline Vector2T< Number >::operator vector2Int_t () const {
    return vectorInt_t( x, y );
}




template< typename Number >
inline Number Vector2T< Number >::estimateLength() const {
    return estimateDistance();
}




template< typename Number >
inline Number Vector2T< Number >::squareLength() const {
    return squareDistance();
}



template< typename Number >
inline Number Vector2T< Number >::length() const {
    return distance();
}



template< typename Number >
inline Number Vector2T< Number >::normalize() {
    const Number l = length();
    if (l > static_cast< Number >( 0 )) {
        const Number il = static_cast< Number >( 1 ) / l;
        x *= il;
        y *= il;
    }
    return l;
}




template< typename Number >
inline Number Vector2T< Number >::dot( const Vector2T< Number >& v ) const {
    return x * v.x + y * v.y;
}




template< typename Number >
inline Number Vector2T< Number >::cross( const Vector2T< Number >& v ) const {
    return (x * v.y - y * v.x);
}




template< typename Number >
inline Vector2T< Number > Vector2T< Number >::perpendicular() const {
    return Vector2T< Number >( y, -x );
}




template< typename Number >
inline Number Vector2T< Number >::angle( const Vector2T< Number >& v ) const {
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
inline std::ostream& operator<<( std::ostream& out, const typelib::Vector2T< Number >& c ) {
    out << "[ " << c.x << ", " << c.y << " ]";
    return out;
}


} // std
