namespace typelib {


template< typename Number >
inline Coord2T< Number >::operator coord2_t () const {
    return coord2_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator coord2Double_t () const {
    return coord2Double_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator coord2Int_t () const {
    return coord2Int_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator size2_t () const {
    return size2_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator size2Double_t () const {
    return size2Double_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator size2Int_t () const {
    return size2Int_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator vector2_t () const {
    return vector2_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator vector2Double_t () const {
    return vector2Double_t( x, y );
}



template< typename Number >
inline Coord2T< Number >::operator vector2Int_t () const {
    return vector2Int_t( x, y );
}




template< typename Number >
inline bool Coord2T< Number >::operator==( const typelib::Coord2T< Number >& b ) const {
    return typelib::equal( x, b.x )
        && typelib::equal( y, b.y );
}




template< typename Number >
inline bool Coord2T< Number >::operator!=( const Coord2T< Number >& b ) const {
    return !typelib::equal( x, b.x )
        || !typelib::equal( y, b.y );
}



} // typelib








namespace boost {

template< typename Number >
inline std::size_t hash_value( const typelib::Coord2T< Number >& a ) {
    std::size_t seed = hash_value( a.x );
    hash_combine( seed, a.y );
    return seed;
}

} // boost









namespace std {

template< typename Number >
inline std::ostream& operator<<( std::ostream& out, const typelib::Coord2T< Number >& c ) {
    out << "[ " << c.x << ", " << c.y << " ]";
    return out;
}

} // std
