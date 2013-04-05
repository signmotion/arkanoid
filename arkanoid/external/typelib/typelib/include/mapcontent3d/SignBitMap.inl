namespace typelib {


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >::SignBitMap() {
    // для пустых меток не создаём слой
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >::SignBitMap( const Sign<>& sign, const layerRaw_t& layer ) {
    if ( !sign.empty() && !layer.none() ) {
        // создаём слой только для не пустых и заполненных меток
        //mRaw.emplace( sign, layer );
        mRaw.insert( std::make_pair( sign, layer ) );
        addSID( sign );
    }
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >::SignBitMap(
    const raw_t& r
) :
    mRaw( r )
{
}


        
template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >::~SignBitMap() {
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename SignBitMap< SX, SY, SZ >::raw_t const&
SignBitMap< SX, SY, SZ >::raw() const {
    return mRaw;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename SignBitMap< SX, SY, SZ >::raw_t&
SignBitMap< SX, SY, SZ >::raw() {
    return mRaw;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename SignBitMap< SX, SY, SZ >::sidMap_t const&
SignBitMap< SX, SY, SZ >::sidMap() const {
    return mSIDMap;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignBitMap< SX, SY, SZ >::sid( const Sign<>& sign ) const {
    const auto ftr = mSIDMap.find( sign );
    return (ftr == mSIDMap.cend()) ? UINT_MAX : ftr->second;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignBitMap< SX, SY, SZ >::sid( const std::string& sign ) const {
    return sid( Sign<>( sign ) );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline Sign<> SignBitMap< SX, SY, SZ >::sid( std::size_t n ) const {
    for (auto itr = mSIDMap.cbegin(); itr != mSIDMap.cend(); ++itr) {
        const std::size_t u = itr->second;
        if (u == n) {
            return itr->first;
        }
    }
    return Sign<>::SPACE();
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignBitMap< SX, SY, SZ >::first() const {
    assert( !mRaw.empty() && "В карте нет меток." );
    assert( (mRaw.size() == 1)
        && "Карта меток содержит более одного слоя меток."
           " Чтобы избежать неожиданных ошибок, лучше обратиться к 'raw()' явно." );
    return mRaw.cbegin()->second.get_first();
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignBitMap< SX, SY, SZ >::next( std::size_t i ) const {
    assert( !mRaw.empty() && "В карте нет меток." );
    assert( (mRaw.size() == 1)
        && "Карта меток содержит более одного слоя меток."
           " Чтобы избежать неожиданных ошибок, лучше обратиться к 'raw()' явно." );
    return mRaw.cbegin()->second.get_next( i );
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator=( const SignBitMap< SX, SY, SZ >& b ) {
    mRaw = b.raw();
    return *this;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator=( const Sign<>& sign ) {
    layerRaw_t l;
    l.set();
    *this = signLayerRaw_t( sign, l );

    return *this;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator+=( const Sign<>& s ) {
    *this = s;
    return *this;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator=( const signLayerRaw_t& sl ) {
    const Sign<>& sign = sl.first;
    auto ftr = mRaw.find( sign );
    if (ftr == mRaw.cend()) {
        mRaw.insert( sl );
        addSID( sign );
    } else {
        ftr->second |= sl.second;
    }
    return *this;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator+=( const signLayerRaw_t& sl ) {
    *this = sl;
    return *this;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator-=( const Sign<>& sign ) {
    auto ftr = mRaw.find( sign );
    if (ftr != mRaw.cend()) {
        mRaw.erase( ftr );
    }

    // sidMap также стоит почистить
    deleteSID( sign );

    return *this;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator&=( const SignBitMap< SX, SY, SZ >& b ) {
    for (auto itr = mRaw.begin(); itr != mRaw.end(); ) {
        const Sign<>& sign = itr->first;
        auto btr = b.mRaw.find( sign );
        if (btr == b.mRaw.cend()) {
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



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline SignBitMap< SX, SY, SZ >& SignBitMap< SX, SY, SZ >::operator|=( const SignBitMap< SX, SY, SZ >& b ) {
    for (auto itr = b.mRaw.cbegin(); itr != b.mRaw.cend(); ++itr) {
        const Sign<>& sign = itr->first;
        auto btr = mRaw.find( sign );
        if (btr == mRaw.cend()) {
            // для этой операции несуществующий слой-метку надо добавить
            const layerRaw_t l( itr->second );
            mRaw.insert( std::make_pair( sign, l ) );
            addSID( sign );
        } else {
            // метки существует со своими биткартами, надо объединить
            btr->second |= itr->second;
        }
    }
    return *this;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::operator==( const SignBitMap< SX, SY, SZ >& b ) const {
    return (mRaw == b.raw());
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::operator!=( const SignBitMap< SX, SY, SZ >& b ) const {
    return (mRaw != b.raw());
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignBitMap< SX, SY, SZ >::set( std::size_t i, const Sign<>& sign ) {
    auto ftr = mRaw.find( sign );
    if (ftr == mRaw.cend()) {
        layerRaw_t l;
        ftr = mRaw.insert( std::make_pair( sign, l ) ).first;
        addSID( sign );
    }
    ftr->second.set( i );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignBitMap< SX, SY, SZ >::set( const Sign<>& sign ) {
    *this = sign;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignBitMap< SX, SY, SZ >::set( const coordInt_t& c, const Sign<>& sign ) {
    set( ic( c ), sign );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignBitMap< SX, SY, SZ >::set( int x, int y, int z, const Sign<>& sign ) {
    set( ic( x, y, z ),  sign );
}





    
template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::test( std::size_t i ) const {
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( itr->second.test( i ) ) {
            return true;
        }
    }
    return false;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::test( const coordInt_t& c ) const {
    return test( ic( c ) );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::test( int x, int y, int z ) const {
    return test( ic( x, y, z ) );
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::any() const {
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( itr->second.any() ) {
            return true;
        }
    }
    return false;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::none() const {
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( !itr->second.none() ) {
            return false;
        }
    }
    return true;
}

    


template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignBitMap< SX, SY, SZ >::countUnique() const {
    return mRaw.size();
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignBitMap< SX, SY, SZ >::count() const {
    std::size_t n = 0;
    for (auto itr = mRaw.cbegin(); itr != mRaw.cend(); ++itr) {
        if ( !itr->first.empty() ) {
            n += itr->second.count();
        }
    }
    return n;
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline std::size_t SignBitMap< SX, SY, SZ >::count( const Sign<>& sign ) const {
    auto ftr = mRaw.find( sign );
    return (ftr == mRaw.cend()) ? 0 : ftr->second.count();
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignBitMap< SX, SY, SZ >::compact() {
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




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline typename SignBitMap< SX, SY, SZ >::raw_t::iterator
SignBitMap< SX, SY, SZ >::find( const Sign<>& sign ) {
    return mRaw.find( sign );
}



template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline bool SignBitMap< SX, SY, SZ >::has( const Sign<>& sign ) const {
    return (mRaw.find( sign ) != mRaw.cend());
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline BitMap< SX, SY, SZ > SignBitMap< SX, SY, SZ >::presence() const {
    typedef BitMap< SX, SY, SZ >  bm_t;
    bm_t r;

    for (auto itr = mRaw.begin(); itr != mRaw.end(); ++itr) {
        //const Sign<>& sign = itr->first;
        const bm_t& bm = bm_t( itr->second );
        r |= bm;
    }

    return r;
}




template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignBitMap< SX, SY, SZ >::addSID( const Sign<>& sign ) {
    // добавляем только новую метку
    const auto ftr = mSIDMap.find( sign );
    if (ftr != mSIDMap.cend()) {
        // метка уже есть
        return;
    }

    // находим минимально возможный SID в последовательности

    // 1. Упорядочиваем SID'ы по возрастанию
    typedef std::set< std::size_t >  ss_t;
    ss_t ss;
    std::transform(
        mSIDMap.cbegin(), mSIDMap.cend(),
        std::inserter( ss, ss.begin() ),
        boost::bind( &sidMap_t::value_type::second, _1 )
    );

    // 2. Найходим дыру и закрываем её
    // (SID'ы начинаются с 0)
    std::size_t insertSID = 0;
    for (auto itr = ss.cbegin(); itr != ss.cend(); ++itr) {
        if (itr == ss.cbegin()) {
            // первый элемент пропускаем
            continue;
        }
        const std::size_t u = *itr;
        if ((insertSID + 1) < u) {
            // дырка найдена
            break;
        }
        ++insertSID;
    }

    // до или после первого элемента?
    if ( ss.empty() ) {
        // нет дырок, генерируем SID
        insertSID = ss.size();

    } else {
        // корректируем вычисленный выше SID
        ss_t::const_iterator first = ss.cbegin();
        if (insertSID == *first) {
            ++insertSID;

        } else {
            ss_t::const_iterator last = ss.cend();
            --last;
            if (insertSID == *last) {
                insertSID = ss.size();
            }
        }
    }

    mSIDMap.insert( std::make_pair( sign, insertSID ) );

    assert( (insertSID < UINT_MAX)
        && "Карта меток переполнена (может содержать не более UINT_MAX элементов)." );
}







template< std::size_t SX, std::size_t SY, std::size_t SZ >
inline void SignBitMap< SX, SY, SZ >::deleteSID( const Sign<>& sign ) {
    auto ftr = mSIDMap.find( sign );
    /* - Не гибко.
    assert( (ftr != mSIDMap.end())
        && "Метка должна существовать. Целостность карты нарушена." );
    */
    if (ftr != mSIDMap.end()) {
        mSIDMap.erase( ftr );
    }
}



} // typelib
