namespace typelib {


template< typename T >
inline ObjectPtrDMap2D< T >::ObjectPtrDMap2D(
    std::size_t sx,  std::size_t sy,
    T value
) :
    DMapContent2D< T >( sx, sy ),
    mRaw( volume(),  value )
{
}



template< typename T >
inline ObjectPtrDMap2D< T >::ObjectPtrDMap2D(
    std::size_t sx,  std::size_t sy,
    const raw_t&  r
) :
    DMapContent2D< T >( sx, sy ),
    mRaw( volume(),  T() )
{
}


        
template< typename T >
inline ObjectPtrDMap2D< T >::~ObjectPtrDMap2D() {
}




template< typename T >
inline typename ObjectPtrDMap2D< T >::raw_t const&
ObjectPtrDMap2D< T >::raw() const {
    return mRaw;
}



template< typename T >
inline typename ObjectPtrDMap2D< T >::raw_t&
ObjectPtrDMap2D< T >::raw() {
    return mRaw;
}





template< typename T >
inline DynamicMapContent2D::index_t
ObjectPtrDMap2D< T >::first() const {
    assert( false
        && "Не реализовано." );
    return volume();
}




template< typename T >
inline DynamicMapContent2D::index_t
ObjectPtrDMap2D< T >::firstEmpty() const {
    assert( false
        && "Не реализовано." );
    return volume();
}




template< typename T >
inline DynamicMapContent2D::index_t
ObjectPtrDMap2D< T >::next( index_t i ) const {
    assert( false
        && "Не реализовано." );
    return volume();
}




template< typename T >
inline DynamicMapContent2D::index_t
ObjectPtrDMap2D< T >::nextEmpty( index_t i ) const {
    assert( false
        && "Не реализовано." );
    return volume();
}




template< typename T >
inline ObjectPtrDMap2D< T >&
ObjectPtrDMap2D< T >::operator=( T value ) {
    std::fill( mRaw.begin(), mRaw.end(), value );
    return *this;
}



template< typename T >
inline ObjectPtrDMap2D< T >&
ObjectPtrDMap2D< T >::operator=( const ObjectPtrDMap2D& b ) {
    mRaw = b.raw();
    return *this;
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::operator==( const ObjectPtrDMap2D& b ) const {
    const auto ftr = std::equal(
        mRaw.cbegin(),
        mRaw.cend(),
        b.raw().cbegin(),
        [] ( T v1, T v2 ) -> bool {
            return (v1 == v2);
    } );

    return (ftr != mRaw.cend());
}



    
template< typename T >
inline bool
ObjectPtrDMap2D< T >::operator!=( const ObjectPtrDMap2D& b ) const {
    return !(*this == b);
}




template< typename T >
inline void
ObjectPtrDMap2D< T >::set( index_t i, const T& value ) {
    //mRaw[ i ] = value;
    assert( false
        && "Не реализовано." );
}




template< typename T >
inline void
ObjectPtrDMap2D< T >::set( const T& value ) {
    //*this = value;
    assert( false
        && "Не реализовано." );
}




template< typename T >
inline void
ObjectPtrDMap2D< T >::set( const coord2Int_t& c, const T& value ) {
    set( ic( c ),  value );
}




template< typename T >
inline void
ObjectPtrDMap2D< T >::set( int x, int y, const T& value ) {
    set( ic( x, y ),  value );
}





template< typename T >
inline bool
ObjectPtrDMap2D< T >::test( index_t i ) const {
    return !(mRaw[ i ] == T());
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::test( const coord2Int_t& c ) const {
    return test( ic( c ) );
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::test( int x, int y ) const {
    return test( ic( x, y ) );
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::test( index_t i, const T& value ) const {
    return equal( mRaw[ i ], value );
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::test( const coord2Int_t& c, const T& value ) const {
    return test( ic( c ), value );
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::test( int x, int y, const T& value ) const {
    return test( ic( x, y, z ), value );
}




template< typename T >
inline T const&
ObjectPtrDMap2D< T >::operator()( index_t i ) const {
    return mRaw[ i ];
}




template< typename T >
inline T&
ObjectPtrDMap2D< T >::operator()( index_t i ) {
    return mRaw[ i ];
}




template< typename T >
inline T const&
ObjectPtrDMap2D< T >::operator()( const coord2Int_t& c ) const {
    const auto i = ic( c );
    return ( *this )[ i ];
}




template< typename T >
inline T&
ObjectPtrDMap2D< T >::operator()( const coord2Int_t& c ) {
    const auto i = ic( c );
    return ( *this )[ i ];
}




template< typename T >
inline T const&
ObjectPtrDMap2D< T >::operator[]( index_t i ) const {
    return ( *this )( i );
}





template< typename T >
inline T&
ObjectPtrDMap2D< T >::operator[]( index_t i ) {
    return ( *this )( i );
}




template< typename T >
inline T const&
ObjectPtrDMap2D< T >::operator[]( const coord2Int_t& c ) const {
    return ( *this )( c );
}




template< typename T >
inline T&
ObjectPtrDMap2D< T >::operator[]( const coord2Int_t& c ) {
    return ( *this )( c );
}




template< typename T >
inline bool ObjectPtrDMap2D< T >::any() const {
    assert( false
        && "Не реализовано." );
    return false;
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::none() const {
    assert( false
        && "Не реализовано." );
    return false;
}




template< typename T >
inline bool
ObjectPtrDMap2D< T >::full() const {
    assert( false
        && "Не реализовано." );
    return false;
}




template< typename T >
inline std::size_t
ObjectPtrDMap2D< T >::count() const {
    assert( false
        && "Не реализовано." );
    return 0;
}




template< typename T >
inline std::size_t
ObjectPtrDMap2D< T >::count( const T& value ) const {
    assert( false
        && "Не реализовано." );
    return 0;
}




} // typelib
