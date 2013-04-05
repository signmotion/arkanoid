namespace typelib {


template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline StructMap< Struct, SX, SY, SZ >::StructMap( Struct value ) {
    mRaw.fill( value );
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline StructMap< Struct, SX, SY, SZ >::StructMap(
    const raw_t& r
) :
    mRaw( r )
{
}


        
template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline StructMap< Struct, SX, SY, SZ >::~StructMap() {
}




template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename StructMap< Struct, SX, SY, SZ >::raw_t const& StructMap< Struct, SX, SY, SZ >::raw() const {
    return mRaw;
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename StructMap< Struct, SX, SY, SZ >::raw_t& StructMap< Struct, SX, SY, SZ >::raw() {
    return mRaw;
}





template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t StructMap< Struct, SX, SY, SZ >::first() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Struct v ) -> bool {
        return !v.empty();
    } );
    return (ftr == mRaw.cend()) ? 0 : std::distance( mRaw.cbegin(), ftr );
}




template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t StructMap< Struct, SX, SY, SZ >::next( std::size_t i ) const {
    const auto ftr = std::find_if( mRaw.cbegin() + i,  mRaw.cend(),  [] ( Struct v ) -> bool {
        return !v.empty();
    } );
    return (ftr == mRaw.cend()) ? 0 : std::distance( mRaw.cbegin(), ftr );
}




template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline StructMap< Struct, SX, SY, SZ >& StructMap< Struct, SX, SY, SZ >::operator=( Struct value ) {
    mRaw.fill( value );
    return *this;
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline StructMap< Struct, SX, SY, SZ >& StructMap< Struct, SX, SY, SZ >::operator=( const StructMap& b ) {
    mRaw = b.raw();
    return *this;
}




template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::operator==( const StructMap& b ) const {
    // не можем обойтись простым "==", т.к. Struct может быть с плав. точкой
    const auto ftr = std::equal( mRaw.cbegin(),  mRaw.cend(),  b.raw().cbegin(),  [] ( Struct v1, Struct v2 ) -> bool {
        return (v1 == v2);
    } );
    return (ftr != mRaw.cend());
}


    
template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::operator!=( const StructMap& b ) const {
    return !(*this == b);
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void StructMap< Struct, SX, SY, SZ >::set( std::size_t i, const Struct& value ) {
    mRaw[ i ] = value;
}


template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void StructMap< Struct, SX, SY, SZ >::set( const Struct& value ) {
    *this = value;
}


template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void StructMap< Struct, SX, SY, SZ >::set( const coordInt_t& c, const Struct& value ) {
    set( ic( c ),  value );
}


template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void StructMap< Struct, SX, SY, SZ >::set( int x, int y, int z, const Struct& value ) {
    set( ic( x, y, z ),  value );
}





template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::test( std::size_t i ) const {
    return !typelib::empty( mRaw[ i ] );
}


template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::test( const coordInt_t& c ) const {
    return test( ic( c ) );
}

template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::test( int x, int y, int z ) const {
    return test( ic( x, y, z ) );
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::test( std::size_t i, const Struct& value ) const {
    return (mRaw[ i ] == value);
}


template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::test( const coordInt_t& c, const Struct& value ) const {
    return test( ic( c ), value );
}

template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::test( int x, int y, int z, const Struct& value ) const {
    return test( ic( x, y, z ), value );
}




template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct const&
StructMap< Struct, SX, SY, SZ >::operator()( std::size_t i ) const {
    return mRaw[ i ];
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct&
StructMap< Struct, SX, SY, SZ >::operator()( std::size_t i ) {
    return mRaw[ i ];
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct const&
StructMap< Struct, SX, SY, SZ >::operator()( const coordInt_t& c ) const {
    const std::size_t i = ic( c );
    return ( *this )[ i ];
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct&
StructMap< Struct, SX, SY, SZ >::operator()( const coordInt_t& c ) {
    const std::size_t i = ic( c );
    return ( *this )[ i ];
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct const&
StructMap< Struct, SX, SY, SZ >::operator[]( std::size_t i ) const {
    return ( *this )( i );
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct&
StructMap< Struct, SX, SY, SZ >::operator[]( std::size_t i ) {
    return ( *this )( i );
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct const&
StructMap< Struct, SX, SY, SZ >::operator[]( const coordInt_t& c ) const {
    return ( *this )( c );
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Struct&
StructMap< Struct, SX, SY, SZ >::operator[]( const coordInt_t& c ) {
    return ( *this )( c );
}





template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::any() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Struct v ) -> bool {
        return !v.empty();
    } );
    return (ftr != mRaw.cend());
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::none() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Struct v ) -> bool {
        return !v.empty();
    } );
    return (ftr == mRaw.cend());
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool StructMap< Struct, SX, SY, SZ >::full() const {
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Struct v ) -> bool {
        return v.empty();
    } );
    return (ftr == mRaw.cend());
}

    


template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t StructMap< Struct, SX, SY, SZ >::count() const {
    const std::size_t n = std::count_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Struct v ) -> bool {
        return !v.empty();
    } );
    return n;
}



template< typename Struct, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t StructMap< Struct, SX, SY, SZ >::count( const Struct& value ) const {
    const std::size_t n = std::count_if( mRaw.cbegin(),  mRaw.cend(),  [ &value ] ( Struct v ) -> bool {
        return (v == value);
    } );
    return n;
}



} // typelib
