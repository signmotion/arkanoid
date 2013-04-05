namespace typelib {


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >::BitMap( bool value ) {
    mRaw.resize( volume() );
    /* - Иначе. См. ниже.
    value ? mRaw.set() : mRaw.reset();
    */
    mRaw.set_range( 0, volume() - 1, value );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >::BitMap( const raw_t& r ) :
    mRaw( r )
{
}


        
template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >::~BitMap() {
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename BitMap< SX, SY, SZ >::raw_t const& BitMap< SX, SY, SZ >::raw() const {
    return mRaw;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename BitMap< SX, SY, SZ >::raw_t& BitMap< SX, SY, SZ >::raw() {
    return mRaw;
}





template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t BitMap< SX, SY, SZ >::first() const {
    return mRaw.get_first();
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t BitMap< SX, SY, SZ >::next( std::size_t i ) const {
    return mRaw.get_next( i );
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >& BitMap< SX, SY, SZ >::operator=( bool x ) {
    mRaw = x;
    return *this;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >& BitMap< SX, SY, SZ >::operator=( const BitMap< SX, SY, SZ >& b ) {
    mRaw = b.raw();
    return *this;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >& BitMap< SX, SY, SZ >::operator&=(const BitMap< SX, SY, SZ >& b) {
    mRaw &= b.raw();
    return *this;
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >& BitMap< SX, SY, SZ >::operator|=(const BitMap< SX, SY, SZ >& b) {
    mRaw |= b.raw();
    return *this;
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >& BitMap< SX, SY, SZ >::operator^=(const BitMap< SX, SY, SZ >& b) {
    mRaw ^= b.raw();
    return *this;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ > BitMap< SX, SY, SZ >::operator&(const BitMap< SX, SY, SZ >& b) const {
    return BitMap( mRaw & b.raw() );
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ > BitMap< SX, SY, SZ >::operator|(const BitMap< SX, SY, SZ >& b) const {
    return BitMap( mRaw | b.raw() );
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ > BitMap< SX, SY, SZ >::operator^(const BitMap< SX, SY, SZ >& b) const {
    return BitMap( mRaw ^ b.raw() );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::operator==( const BitMap< SX, SY, SZ >& b ) const {
    return (mRaw == b.raw());
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::operator!=( const BitMap< SX, SY, SZ >& b ) const {
    return (mRaw != b.raw());
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::set() {
    mRaw.set();
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::set( std::size_t i, const bool& value ) {
    mRaw[ i ] = value;
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::set( const bool& value ) {
    mRaw.set_range( 0, volume() - 1, value );
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::set( const coordInt_t& c ) {
    set( ic( c ), true );
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::set( int x, int y, int z ) {
    set( ic( x, y, z ),  true );
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::flip( const coordInt_t& c ) {
    flip( ic( c ) );
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::flip( std::size_t i ) {
    mRaw.flip( i );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::flip() {
    /* - Не можем просто воспользоваться flip'ом: bm::bvector работает с
            полотном в bm::id_max бит.
    mRaw.flip();
    */
    for (std::size_t i = 0; i < volume(); ++i) {
        mRaw.flip( i );
    }
}



    
template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::test( std::size_t i ) const {
    return mRaw.test( i );
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::test( const coordInt_t& c ) const {
    return BitMap< SX, SY, SZ >::test( ic( c ) );
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::test( int x, int y, int z ) const {
    return test( ic( x, y, z ) );
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::any() const {
    return mRaw.any();
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::none() const {
    return mRaw.none();
}


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool BitMap< SX, SY, SZ >::full() const {
    return (mRaw.count() == volume());
}

    
template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ > BitMap< SX, SY, SZ >::operator~() const {
    BitMap b( *this );
    b.raw() = ~mRaw;
    return b;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t BitMap< SX, SY, SZ >::count() const {
    return mRaw.count();
}





template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void BitMap< SX, SY, SZ >::assignSurfaceOr( int z, const raw_t& mapXY ) {
    if ( mapXY.none() ) {
        // пустые плоскости не вносят изменений в бит-карту
        return;
    }

    /* - Проход по значимым битам - эффективнее. См. ниже.
    for (int y = minCoord().y; y <= maxCoord().y; ++y) {
        for (int x = minCoord().x; x <= maxCoord().x; ++x) {
            // в плоскости только один уровень z, нулевой
            const std::size_t iMapXY = ic( x, y, 0 );
            ...
        }
    }
    */

    // ищем всё значимое на бит-плоскости (2D) и отражаем на бит-карту (3D)
    std::size_t iMapXY = mapXY.get_first();
    do {
        const coordInt_t cMapXY = ci< SX, SY, 1 >( iMapXY );
        const coordInt_t c( cMapXY.x, cMapXY.y, z );
        const std::size_t i = ic( c );
        // объединяем по "OR"
        //if ( !test( i ) ) {
            set( i, true );
        //}

        iMapXY = mapXY.get_next( iMapXY );

    } while (iMapXY != 0);

}





} // typelib
