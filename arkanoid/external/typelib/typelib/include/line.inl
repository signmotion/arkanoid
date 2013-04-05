namespace typelib {


template< typename Number >
inline LineT< Number >::operator line_t () const {
    return line_t( a, b );
}



template< typename Number >
inline LineT< Number >::operator lineInt_t () const {
    return lineInt_t( a, b );
}



template< typename Number >
inline LineT< Number >::operator lineDouble_t () const {
    return lineDouble_t( a, b );
}




template< typename Number >
inline bool LineT< Number >::operator==( const typelib::LineT< Number >& l ) const {
    return (a == l.a) && (b == l.b);
}




template< typename Number >
inline bool LineT< Number >::operator!=( const LineT< Number >& l ) const {
    return (a != l.a) || (b != l.b);
}




// @todo optimize 2 метода: с и без p1, p2.
template< typename Number >
inline Number LineT< Number >::distance(
    const LineT< Number >&  l,
    CoordT< Number >*       p1,
    CoordT< Number >*       p2
) const {
    // @source http://gamedev.ru/code/forum/?id=160417&page=2#m22
    typedef VectorT< Number >  vector_t;

    const vector_t v  = b - a;
    const vector_t vl = l.b - l.a;
    vector_t n  = v.cross( vl );
    const vector_t dp = l.a - a;

    // линии параллельны?
    if ( n.dot( n ) < PRECISION) {
        const vector_t pp1 = a;
        const vector_t pp2 =
            static_cast< vector_t >( l.a ) -
            v * ( dp.dot( v ) / v.dot( v ) );
        if ( p1 ) { *p1 = pp1; }
        if ( p2 ) { *p2 = pp2; }

        return (pp2 - pp1).length();
    }

    n.normalize();
    const Number d = dp.dot( n );

    Number vv   = v.dot( v );
    Number vvl  = v.dot( vl );
    Number vlvl = vl.dot( vl );

    const vector_t pp1 =
        static_cast< vector_t >( a ) +
        v * ( (dp - n * d).dot( vl * vvl - v * vlvl ) /
        (vvl * vvl - vv * vlvl) );
    const vector_t pp2 = pp1 + n * d;
    if ( p1 ) { *p1 = pp1; }
    if ( p2 ) { *p2 = pp2; }

    return std::abs( d );
}


} // typelib








namespace boost {

template< typename Number >
inline std::size_t hash_value( const typelib::LineT< Number >& a ) {
    std::size_t seed = hash_value( a.x );
    hash_combine( seed, a.y );
    hash_combine( seed, a.z );
    return seed;
}


} // boost









namespace std {


template< typename Number >
inline std::ostream& operator<<( std::ostream& out, const typelib::LineT< Number >& c ) {
    out << "[ " << c.x << ", " << c.y << ", " << c.z << " ]";
    return out;
}


} // std
