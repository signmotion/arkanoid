#pragma once

// Отключим вредный макрос в WinDef.h
#define NOMINMAX


#include "other.h"
#include <limits>


/**
* 2D-размеры.
*/



namespace typelib {

template< typename Number >
struct Size2T;

typedef Size2T< float >   size2_t;
typedef Size2T< double >  size2Double_t;
typedef Size2T< int >     size2Int_t;


template< typename Number >
struct Coord2T;

typedef Coord2T< float >   coord2_t;
typedef Coord2T< double >  coord2Double_t;
typedef Coord2T< int >     coord2Int_t;


} // typelib




namespace boost {

// Для работы коллекций boost::unordered_set и пр.
// @todo extend Добавить operator>() для работы с коллекциями STL.
// @todo extend Сделать то же для других типов typelib.
template< typename Number >
std::size_t hash_value( const typelib::Size2T< Number >& );

} // boost





namespace std {

template< typename Number >
std::ostream& operator<<( std::ostream&, const typelib::Size2T< Number >& );

} // std





namespace typelib {



/**
* 2 размера заданного типа.
*/
template< typename Number >
struct Size2T {
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Size2T >  Ptr;
    typedef std::unique_ptr< Size2T >  UPtr;


    struct { Number x, y; };


    inline Size2T(
    ) :
        x( static_cast< Number >( 0 ) ),
        y( static_cast< Number >( 0 ) )
    {
    }

    template< typename T >
    inline Size2T(
        T x, T y
    ) :
        x( static_cast< Number >( x ) ),
        y( static_cast< Number >( y ) )
    {
    }

    template< typename T1, typename T2 >
    inline Size2T(
        T1 x, T2 y
    ) :
        x( static_cast< Number >( x ) ),
        y( static_cast< Number >( y ) )
    {
    }

    /**
    * @return Центр.
    */
    inline bool center() const {
        return empty( x ) && empty ( y );
    }

    operator size2_t () const;
    operator size2Double_t () const;
    operator size2Int_t () const;

    operator coord2_t () const;
    operator coord2Double_t () const;
    operator coord2Int_t () const;

    inline Size2T< Number > operator-() const {
        return Size2T< Number >( -x, -y );
    }

    inline Size2T< Number > operator+( const Size2T< Number >& c ) const {
        return Size2T< Number >( x + c.x,  y + c.y );
    }

    inline Size2T< Number >& operator+=( const Size2T< Number >& c ) {
        this->x += c.x;
        this->y += c.y;
        return *this;
    }

    template< typename T >
    inline Size2T< Number >& operator+=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x += ss;
        this->y += ss;
        return *this;
    }

    template< typename T >
    inline Size2T< Number > operator+( T s ) const {
        const Number ss = static_cast< Number >( s );
        return Size2T< Number >( x + ss,  y + ss );
    }

    inline Size2T< Number > operator-( const Size2T< Number >& c ) const {
        return Size2T< Number >( x - c.x,  y - c.y );
    }

    template< typename T >
    inline Size2T< Number > operator-( T s ) const {
        const Number ss = static_cast< Number >( s );
        return Size2T< Number >( x - ss,  y - ss );
    }

    inline Size2T< Number >& operator-=( const Size2T< Number >& c ) {
        this->x -= c.x;
        this->y -= c.y;
        return *this;
    }

    template< typename T >
    inline Size2T< Number >& operator-=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x -= ss;
        this->y -= ss;
        return *this;
    }

    inline Size2T< Number > operator*( const Size2T< Number >& c ) const {
        return Size2T< Number >( x * c.x,  y * c.y );
    }

    template< typename T >
    inline Size2T< Number > operator*( T k ) const {
        const Number kk = static_cast< Number >( k );
        return Size2T< Number >( x * kk,  y * kk );
    }

    inline Size2T< Number >& operator*=( const Size2T< Number >& c ) {
        this->x *= c.x;
        this->y *= c.y;
        return *this;
    }

    template< typename T >
    inline Size2T< Number > operator*=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x *= kk;
        this->y *= kk;
        return *this;
    }

    inline Size2T< Number > operator/( const Size2T< Number >& c ) const {
        return Size2T< Number >( x / c.x,  y / c.y );
    }

    template< typename T >
    inline Size2T< Number > operator/( T k ) const {
        const Number kk = static_cast< Number >( k );
        return Size2T< Number >( x / kk,  y / kk );
    }

    inline Size2T< Number >& operator/=( const Size2T< Number >& c ) {
        this->x /= c.x;
        this->y /= c.y;
        return *this;
    }

    template< typename T >
    inline Size2T< Number > operator/=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x /= kk;
        this->y /= kk;
        return *this;
    }


    bool operator==( const Size2T< Number >& ) const;
    bool operator!=( const Size2T< Number >& ) const;


    // @todo fine Любые равенства для float должны использ. PRECISION.
    inline bool operator>( const Size2T< Number >& c ) const {
        return (x > c.x) && (y > c.y);
    }

    inline bool operator>=( const Size2T< Number >& c ) const {
        return (x >= c.x) && (y >= c.y);
    }

    inline bool operator<( const Size2T< Number >& c ) const {
        return (x < c.x) && (y < c.y);
    }

    inline bool operator<=( const Size2T< Number >& c ) const {
        return (x <= c.x) && (y <= c.y);
    }


    /**
    * @return Максимальная из сторон.
    */
    inline Number max() const {
        return std::max( x, y );
    }


    /**
    * @return Минимальная из сторон.
    */
    inline Number min() const {
        return std::min( x, y );
    }


    /**
    * Доступ к элементам структуры через указатель.
    */
    inline Number* pointer() {
        return reinterpret_cast< Number* >( &x );
    }


    /**
    * @return Размер не определён.
    */
    inline bool undefined() const {
        return (*this == UNDEFINED());
    }


    static inline Size2T< Number > ZERO() {
        // @tip http://rsdn.ru/forum/cpp.applied/4771369.flat.aspx
        static const Size2T< Number >  r( 0, 0 );
        return r;
    }


    static inline Size2T< Number > UNDEFINED() {
        static const Number m = std::numeric_limits< Number >::max();
        static const Size2T< Number >  r( m, m );
        return r;
    }
};


} // typelib







#include "size2.inl"
