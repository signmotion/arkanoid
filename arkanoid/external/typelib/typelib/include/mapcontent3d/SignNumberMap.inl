namespace typelib {


template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >::SignNumberMap() {
    // для пустых меток не создаём слой
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >::SignNumberMap( const Sign<>& sign, const layerRaw_t& layer ) {
    if ( !sign.empty() && !layer.none() ) {
        // создаём слой только для не пустых и заполненных меток
        //mRaw.emplace( sign, layer );
        mRaw.insert( std::make_pair( sign, layer ) );
    }
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >::SignNumberMap( const raw_t& raw ) : raw( raw ) {
}



        
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >::~SignNumberMap() {
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename SignNumberMap< Number, SX, SY, SZ >::raw_t
const& SignNumberMap< Number, SX, SY, SZ >::raw() const {
    return mRaw;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename SignNumberMap< Number, SX, SY, SZ >::raw_t&
SignNumberMap< Number, SX, SY, SZ >::raw() {
    return mRaw;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t
SignNumberMap< Number, SX, SY, SZ >::first() const {
    assert( false && "Метод не реализован." );
    return 0;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t
SignNumberMap< Number, SX, SY, SZ >::next( std::size_t i ) const {
    assert( false && "Метод не реализован." );
    return 0;
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >&
SignNumberMap< Number, SX, SY, SZ >::operator=( const signLayerRaw_t& sv ) {
    const Sign<>& sign = sv.first;
    auto ftr = mRaw.find( sign );
    if (ftr == mRaw.cend()) {
        layerRaw_t l;
        //l.fill( 0 );
        ftr = mRaw.insert( std::make_pair( sign, l ) ).first;
    }
    ftr->second = sv.second;
    return *this;
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >&
SignNumberMap< Number, SX, SY, SZ >::operator=( const SignNumberMap& b ) {
    raw = b.raw;
    return *this;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >&
SignNumberMap< Number, SX, SY, SZ >::operator&=( const SignNumberMap& b ) {
    for (auto itr = mRaw.begin(); itr != mRaw.end(); ) {
        const Sign<>& sign = itr->first;
        auto btr = b.raw().find( sign );
        if (btr == b.raw().cend()) {
            // для этой операции несуществующий слой-метку надо исключить
            mRaw.erase( itr++ );
            ++itr;
        } else {
            // метки существует со своими биткартами, надо объединить
            itr->second &= btr->second;
            ++itr;
        }
    }
    return *this;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignNumberMap< Number, SX, SY, SZ >&
SignNumberMap< Number, SX, SY, SZ >::operator|=( const SignNumberMap& b ) {
    for (auto itr = b.raw().cbegin(); itr != b.raw().cend(); ++itr) {
        const Sign<>& sign = itr->first;
        auto btr = mRaw.find( sign );
        if (btr == mRaw.cend()) {
            // для этой операции несуществующий слой-метку надо добавить
            const layerRaw_t l( itr->second );
            mRaw.insert( std::make_pair( sign, l ) );
        } else {
            // метки существует со своими биткартами, надо объединить
            btr->second |= itr->second;
        }
    }
    return *this;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::operator==( const SignNumberMap& b ) const {
    return (raw == b.raw);
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::operator!=( const SignNumberMap& b ) const {
    return (raw != b.raw);
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignNumberMap< Number, SX, SY, SZ >::set( std::size_t i, const Sign<>& sign ) {
    assert( false && "Метод не реализован." );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignNumberMap< Number, SX, SY, SZ >::set( const Sign<>& sign ) {
    assert( false && "Метод не реализован." );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignNumberMap< Number, SX, SY, SZ >::set( const coordInt_t& c, const Sign<>& sign ) {
    set( ic( c ), sign );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignNumberMap< Number, SX, SY, SZ >::set( int x, int y, int z, const Sign<>& sign ) {
    set( ic( x, y, z ),  sign );
}





    
template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::test( std::size_t i ) const {
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( !typelib::empty( itr->second[i] ) ) {
            return true;
        }
    }
    return false;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::test( const coordInt_t& c ) const {
    return test( ic( c ) );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::test( int x, int y, int z ) const {
    return test( ic( x, y, z ) );
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
SignNumberMap< Number, SX, SY, SZ >::operator()( const Sign<>& sign, std::size_t i ) const {
    const auto ftr = mRaw.find( sign );
    if (ftr == mRaw.cend()) {
        // @todo fine Надо, надо свой Exception...
        assert( false && "Элемент по заданной метке не найден." );
    }
    return ftr->second[i];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
SignNumberMap< Number, SX, SY, SZ >::operator()( const Sign<>& sign, std::size_t i ) {
    auto ftr = mRaw.find( sign );
    if (ftr == mRaw.end()) {
        // @todo fine Надо, надо свой Exception...
        assert( false && "Элемент по заданной метке не найден." );
    }
    return ftr->second[i];
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number const&
SignNumberMap< Number, SX, SY, SZ >::operator()( const Sign<>& sign, const coordInt_t& c ) const {
    const std::size_t i = ic( c );
    return ( *this )( sign, i );
}



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline Number&
SignNumberMap< Number, SX, SY, SZ >::operator()( const Sign<>& sign, const coordInt_t& c ) {
    const std::size_t i = ic( c );
    return ( *this )( sign, i );
}





template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::any() const {
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( itr->second.any() ) {
            return true;
        }
    }
    return false;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::none() const {
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( !itr->second.none() ) {
            return false;
        }
    }
    return true;
}

    



template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignNumberMap< Number, SX, SY, SZ >::countUnique() const {
    return mRaw.size();
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignNumberMap< Number, SX, SY, SZ >::count() const {
    std::size_t n = 0;
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( !itr->first.empty() ) {
            for (std::size_t i = 0; i < volume(); ++i) {
                if ( test( i ) ) {
                    n++;
                }
            }
        }
    }
    return n;
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignNumberMap< Number, SX, SY, SZ >::count( const Sign<>& sign ) const {
    auto ftr = mRaw.find( sign );
    return (ftr == mRaw.cend()) ? 0 : ftr->second.count();
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignNumberMap< Number, SX, SY, SZ >::compact() {
    for (auto itr = mRaw.begin(); itr != mRaw.end(); ) {
        const Sign<>& sign = itr->first;
        if ( sign.empty() ) {
            // (1)
            mRaw.erase( itr++ );
        } else {
            ++itr;
        }
        // (2)
        itr->second.optimize();
    }
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename SignNumberMap< Number, SX, SY, SZ >::raw_t::iterator
SignNumberMap< Number, SX, SY, SZ >::find( const Sign<>& sign ) {
    return mRaw.find( sign );
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignNumberMap< Number, SX, SY, SZ >::has( const Sign<>& sign ) const {
    return (mRaw.find( sign ) != mRaw.cend());
}




template< typename Number, std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ >
SignNumberMap< Number, SX, SY, SZ >::presence( Number from, Number to ) const {
    typedef BitMap< SX, SY, SZ >  bm_t;
    bm_t r;

    for (auto itr = mRaw.begin(); itr != mRaw.end(); ++itr) {
        //const Sign<>& sign = itr->first;
        // можем позволить себе пройтись одномерным индексом (быстро)
        for (std::size_t i = 0; i < volume(); ++i) {
            const Number n = itr->second[i];
            if ( typelib::between( n, from, to ) ) {
                r.set( i );
            }
        }
    }

    return r;
}



} // typelib
