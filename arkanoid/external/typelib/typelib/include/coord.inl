namespace typelib {


template< typename Number >
inline CoordT< Number >::operator coord_t () const {
    return coord_t( x, y, z );
}



template< typename Number >
inline CoordT< Number >::operator coordInt_t () const {
    return coordInt_t( x, y, z );
}



template< typename Number >
inline CoordT< Number >::operator coordDouble_t () const {
    return coordDouble_t( x, y, z );
}



template< typename Number >
inline CoordT< Number >::operator vectorDouble_t () const {
    return vectorDouble_t( x, y, z );
}



template< typename Number >
inline CoordT< Number >::operator vector_t () const {
    return vector_t( x, y, z );
}



template< typename Number >
inline CoordT< Number >::operator vectorInt_t () const {
    return vectorInt_t( x, y, z );
}




template< typename Number >
inline bool CoordT< Number >::operator==( const typelib::CoordT< Number >& b ) const {
    return typelib::equal( x, b.x )
        && typelib::equal( y, b.y )
        && typelib::equal( z, b.z );
}




template< typename Number >
inline bool CoordT< Number >::operator!=( const CoordT< Number >& b ) const {
    return !typelib::equal( x, b.x )
        || !typelib::equal( y, b.y )
        || !typelib::equal( z, b.z );
}




inline bool relCoordInt_t::operator==( const relCoordInt_t& b ) const {
    return (c == b.c)
        && (n == b.n);
}




inline bool relCoordInt_t::operator!=( const relCoordInt_t& b ) const {
    return (c != b.c)
        || (n != b.n);
}



} // typelib








namespace boost {

template< typename Number >
inline std::size_t hash_value( const typelib::CoordT< Number >& a ) {
    std::size_t seed = hash_value( a.x );
    hash_combine( seed, a.y );
    hash_combine( seed, a.z );
    return seed;
}




inline std::size_t hash_value( const typelib::relCoordInt_t& a ) {
    std::size_t seed = hash_value( a.c );
    hash_combine( seed, a.n );
    return seed;
}


} // boost









namespace std {


template< typename Number >
inline std::ostream& operator<<( std::ostream& out, const typelib::CoordT< Number >& c ) {
    out << "[ " << c.x << ", " << c.y << ", " << c.z << " ]";
    return out;
}




inline std::ostream& operator<<( std::ostream& out, const typelib::relCoordInt_t& c ) {
    out << "[ \"" << c.n << "\", " << c.c.x << ", " << c.c.y << ", " << c.c.z << " ]";
    return out;
}


} // std
