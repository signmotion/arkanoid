namespace typelib {


template< typename Number >
inline SizeT< Number >::operator size_t () const {
    return size_t( x, y, z );
}



template< typename Number >
inline SizeT< Number >::operator sizeDouble_t () const {
    return sizeDouble_t( x, y, z );
}



template< typename Number >
inline SizeT< Number >::operator sizeInt_t () const {
    return size2Int_t( x, y, z );
}



template< typename Number >
inline SizeT< Number >::operator coord_t () const {
    return coord_t( x, y, z );
}



template< typename Number >
inline SizeT< Number >::operator coordDouble_t () const {
    return coordDouble_t( x, y, z );
}



template< typename Number >
inline SizeT< Number >::operator coordInt_t () const {
    return coordInt_t( x, y, z );
}




template< typename Number >
inline bool SizeT< Number >::operator==( const typelib::SizeT< Number >& b ) const {
    return typelib::equal( x, b.x )
        && typelib::equal( y, b.y )
        && typelib::equal( z, b.z );
}




template< typename Number >
inline bool SizeT< Number >::operator!=( const SizeT< Number >& b ) const {
    return !typelib::equal( x, b.x )
        || !typelib::equal( y, b.y )
        || !typelib::equal( z, b.z );
}




template< typename Number >
inline Number SizeT< Number >::volume() const {
    return (x * y * z);
}




template< typename Number >
inline Number SizeT< Number >::square() const {
    return static_cast< Number >( 2 ) * (x * y + y * z + x * z);
}



} // typelib








namespace boost {

template< typename Number >
inline std::size_t hash_value( const typelib::SizeT< Number >& a ) {
    std::size_t seed = hash_value( a.x );
    hash_combine( seed, a.y );
    hash_combine( seed, a.z );
    return seed;
}

} // boost









namespace std {

template< typename Number >
inline std::ostream& operator<<( std::ostream& out, const typelib::SizeT< Number >& s ) {
    out << s.x << " x " << s.y << " x " << s.z;
    return out;
}

} // std
