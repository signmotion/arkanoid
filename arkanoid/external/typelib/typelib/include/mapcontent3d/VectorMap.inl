namespace typelib {


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline VectorMap< Number, SX, SY, SZ >::VectorMap() {
    mRaw.fill( static_cast< Number >( 0 ) );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline VectorMap< Number, SX, SY, SZ >::VectorMap( Number x, Number y, Number z ) {
    for (auto itr = mRaw.begin(); itr != mRaw.end(); itr += 3) {
        *(itr + 0) = x;
        *(itr + 1) = y;
        *(itr + 2) = z;
    }
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline VectorMap< Number, SX, SY, SZ >::VectorMap(
    const raw_t& r
) :
    mRaw( r )
{
}


        
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline VectorMap< Number, SX, SY, SZ >::~VectorMap() {
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename VectorMap< Number, SX, SY, SZ >::raw_t const& VectorMap< Number, SX, SY, SZ >::raw() const {
    return mRaw;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename VectorMap< Number, SX, SY, SZ >::raw_t& VectorMap< Number, SX, SY, SZ >::raw() {
    return mRaw;
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t VectorMap< Number, SX, SY, SZ >::first() const {
    assert( false && "Не реализовано. @todo..." );
    return 0;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t VectorMap< Number, SX, SY, SZ >::next( std::size_t i ) const {
    assert( false && "Не реализовано. @todo..." );
    return 0;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline VectorMap< Number, SX, SY, SZ >& VectorMap< Number, SX, SY, SZ >::operator=( const VectorT< Number >& value ) {
    for (auto itr = mRaw.begin(); itr != mRaw.end(); itr += 3) {
        *(itr + 0) = value.x;
        *(itr + 1) = value.y;
        *(itr + 2) = value.z;
    }
    return *this;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline VectorMap< Number, SX, SY, SZ >& VectorMap< Number, SX, SY, SZ >::operator=( const VectorMap& b ) {
    mRaw = b.raw();
    return *this;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::operator==( const VectorMap& b ) const {
    assert( false && "Не реализовано. @todo..." );
}


    
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::operator!=( const VectorMap& b ) const {
    return (*this != b);
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void VectorMap< Number, SX, SY, SZ >::set( std::size_t i, const Number& value ) {
    const std::size_t iii = i * 3;
    mRaw[ iii + 0 ] = mRaw[ iii + 1 ] = mRaw[ iii + 2 ] = value;
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void VectorMap< Number, SX, SY, SZ >::set( const Number& value ) {
    assert( false && "Не реализовано. @todo..." );
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void VectorMap< Number, SX, SY, SZ >::set( const coordInt_t& c, const Number& value ) {
    set( ic( c ),  value );
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void VectorMap< Number, SX, SY, SZ >::set( int x, int y, int z, const Number& value ) {
    set( ic( x, y, z ),  value );
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::test( std::size_t i ) const {
    const std::size_t iii = i * 3;
    return !typelib::empty( mRaw[ iii + 0 ] )
        && !typelib::empty( mRaw[ iii + 1 ] )
        && !typelib::empty( mRaw[ iii + 2 ] );
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::test( const coordInt_t& c ) const {
    return test( ic( c ) );
}

template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::test( int x, int y, int z ) const {
    return test( ic( x, y, z ) );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::test( std::size_t i, const Number& value ) const {
    return equal( mRaw[ i ], value );
}


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::test( const coordInt_t& c, const Number& value ) const {
    return test( ic( c ), value );
}

template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::test( int x, int y, int z, const Number& value ) const {
    return test( ic( x, y, z ), value );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
VectorMap< Number, SX, SY, SZ >::operator()( std::size_t i ) const {
    assert( false && "Не реализовано. @todo..." );
    return mRaw[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
VectorMap< Number, SX, SY, SZ >::operator()( std::size_t i ) {
    assert( false && "Не реализовано. @todo..." );
    return mRaw[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
VectorMap< Number, SX, SY, SZ >::operator()( const coordInt_t& c ) const {
    assert( false && "Не реализовано. @todo..." );
    const std::size_t i = ic( c );
    return ( *this )[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
VectorMap< Number, SX, SY, SZ >::operator()( const coordInt_t& c ) {
    assert( false && "Не реализовано. @todo..." );
    const std::size_t i = ic( c );
    return ( *this )[ i ];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
VectorMap< Number, SX, SY, SZ >::operator[]( std::size_t i ) const {
    assert( false && "Не реализовано. @todo..." );
    return ( *this )( i );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
VectorMap< Number, SX, SY, SZ >::operator[]( std::size_t i ) {
    assert( false && "Не реализовано. @todo..." );
    return ( *this )( i );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
VectorMap< Number, SX, SY, SZ >::operator[]( const coordInt_t& c ) const {
    assert( false && "Не реализовано. @todo..." );
    return ( *this )( c );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
VectorMap< Number, SX, SY, SZ >::operator[]( const coordInt_t& c ) {
    assert( false && "Не реализовано. @todo..." );
    return ( *this )( c );
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::any() const {
    assert( false && "Не реализовано. @todo..." );
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return (ftr != mRaw.cend());
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::none() const {
    assert( false && "Не реализовано. @todo..." );
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return (ftr == mRaw.cend());
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool VectorMap< Number, SX, SY, SZ >::full() const {
    assert( false && "Не реализовано. @todo..." );
    const auto ftr = std::find_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return typelib::empty( v );
    } );
    return (ftr == mRaw.cend());
}

    


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t VectorMap< Number, SX, SY, SZ >::count() const {
    assert( false && "Не реализовано. @todo..." );
    const std::size_t n = std::count_if( mRaw.cbegin(),  mRaw.cend(),  [] ( Number v ) -> bool {
        return !typelib::empty( v );
    } );
    return n;
}


} // typelib
