namespace typelib {


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline NumberMap< Number, SX, SY, SZ >::NumberMap( Number value ) {
    mRaw.fill( value );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline NumberMap< Number, SX, SY, SZ >::NumberMap(
    const raw_t& r
) :
    mRaw( r )
{
}


        
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline NumberMap< Number, SX, SY, SZ >::~NumberMap() {
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename NumberMap< Number, SX, SY, SZ >::raw_t const& NumberMap< Number, SX, SY, SZ >::raw() const {
    return mRaw;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename NumberMap< Number, SX, SY, SZ >::raw_t& NumberMap< Number, SX, SY, SZ >::raw() {
    return mRaw;
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t NumberMap< Number, SX, SY, SZ >::first() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return (ftr == mRaw.cend()) ? volume() : std::distance( mRaw.cbegin(), ftr );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t NumberMap< Number, SX, SY, SZ >::next( std::size_t i ) const {
    const auto ftr = std::find_if( mRaw.cbegin() + i,  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return (ftr == mRaw.cend()) ? volume() : std::distance( mRaw.cbegin(), ftr );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline NumberMap< Number, SX, SY, SZ >& NumberMap< Number, SX, SY, SZ >::operator=( Number value ) {
    mRaw.fill( value );
    return *this;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline NumberMap< Number, SX, SY, SZ >& NumberMap< Number, SX, SY, SZ >::operator=( const NumberMap& b ) {
    mRaw = b.raw();
    return *this;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::operator==( const NumberMap& b ) const {
    // не можем обойтись простым "==", т.к. Number может быть с плав. точкой
    const auto ftr = std::equal( mRaw.cbegin(),  mRaw.cend(),  b.raw().cbegin(),  [] ( Number v1, Number v2 ) -> bool {
        return equal( v1, v2 );
    } );
    return (ftr != mRaw.cend());
}


    
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::operator!=( const NumberMap& b ) const {
    return !(*this == b);
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void NumberMap< Number, SX, SY, SZ >::set( std::size_t i, const Number& value ) {
    mRaw[ i ] = value;
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void NumberMap< Number, SX, SY, SZ >::set( const Number& value ) {
    *this = value;
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void NumberMap< Number, SX, SY, SZ >::set( const coordInt_t& c, const Number& value ) {
    set( ic( c ),  value );
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void NumberMap< Number, SX, SY, SZ >::set( int x, int y, int z, const Number& value ) {
    set( ic( x, y, z ),  value );
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::test( std::size_t i ) const {
    return !typelib::empty( mRaw[ i ] );
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::test( const coordInt_t& c ) const {
    return test( ic( c ) );
}

template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::test( int x, int y, int z ) const {
    return test( ic( x, y, z ) );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::test( std::size_t i, const Number& value ) const {
    return equal( mRaw[ i ], value );
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::test( const coordInt_t& c, const Number& value ) const {
    return test( ic( c ), value );
}

template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::test( int x, int y, int z, const Number& value ) const {
    return test( ic( x, y, z ), value );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
NumberMap< Number, SX, SY, SZ >::operator()( std::size_t i ) const {
    return mRaw[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
NumberMap< Number, SX, SY, SZ >::operator()( std::size_t i ) {
    return mRaw[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
NumberMap< Number, SX, SY, SZ >::operator()( const coordInt_t& c ) const {
    const std::size_t i = ic( c );
    return ( *this )[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
NumberMap< Number, SX, SY, SZ >::operator()( const coordInt_t& c ) {
    const std::size_t i = ic( c );
    return ( *this )[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
NumberMap< Number, SX, SY, SZ >::operator[]( std::size_t i ) const {
    return ( *this )( i );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
NumberMap< Number, SX, SY, SZ >::operator[]( std::size_t i ) {
    return ( *this )( i );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
NumberMap< Number, SX, SY, SZ >::operator[]( const coordInt_t& c ) const {
    return ( *this )( c );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
NumberMap< Number, SX, SY, SZ >::operator[]( const coordInt_t& c ) {
    return ( *this )( c );
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::any() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return (ftr != mRaw.cend());
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::none() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return (ftr == mRaw.cend());
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool NumberMap< Number, SX, SY, SZ >::full() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return typelib::empty( v );
    } );
    return (ftr == mRaw.cend());
}

    


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t NumberMap< Number, SX, SY, SZ >::count() const {
    const std::size_t n = std::count_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return n;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t NumberMap< Number, SX, SY, SZ >::count( const Number& value ) const {
    const std::size_t n = std::count_if( mRaw.cbegin(),  mRaw.cend(),  [ &value ] ( Number v ) -> bool {
        return equal( v, value );
    } );
    return n;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number NumberMap< Number, SX, SY, SZ >::min() const {
    return *std::min( mRaw.cbegin(), mRaw.cend() );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number NumberMap< Number, SX, SY, SZ >::max() const {
    return *std::max( mRaw.cbegin(), mRaw.cend() );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::pair< Number, Number >  NumberMap< Number, SX, SY, SZ >::minmax() const {
    if ( mRaw.empty() ) {
        return std::make_pair( static_cast< Number >( 0 ),  static_cast< Number >( 0 ) );
    }
    const auto r = std::minmax_element( mRaw.cbegin(), mRaw.cend() );
    return std::make_pair( *r.first, *r.second );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number NumberMap< Number, SX, SY, SZ >::sum() const {
    return std::accumulate(
        mRaw.cbegin(),
        mRaw.cend(),
        static_cast< Number >( 0 )
    );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number NumberMap< Number, SX, SY, SZ >::avg() const {
    return sum() / static_cast< Number >( volume() );
}



} // typelib
