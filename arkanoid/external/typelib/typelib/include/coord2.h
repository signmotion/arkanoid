#pragma once

// Отключим вредный макрос в WinDef.h
#define NOMINMAX


#include "other.h"
#include <limits>


/**
* 2D-координаты.
*/



namespace typelib {

template< typename Number >
struct Coord2T;

typedef Coord2T< float >   coord2_t;
typedef Coord2T< double >  coord2Double_t;
typedef Coord2T< int >     coord2Int_t;


template< typename Number >
struct Size2T;

typedef Size2T< float >   size2_t;
typedef Size2T< double >  size2Double_t;
typedef Size2T< int >     size2Int_t;


template< typename Number >
struct Vector2T;

typedef Vector2T< float >   vector2_t;
typedef Vector2T< double >  vector2Double_t;
typedef Vector2T< int >     vector2Int_t;


} // typelib




namespace boost {

// Для работы коллекций boost::unordered_set и пр.
// @todo extend Добавить operator>() для работы с коллекциями STL.
// @todo extend Сделать то же для других типов typelib.
template< typename Number >
std::size_t hash_value( const typelib::Coord2T< Number >& );

} // boost





namespace std {

template< typename Number >
std::ostream& operator<<( std::ostream&, const typelib::Coord2T< Number >& );

} // std





namespace typelib {



/**
* Координаты в 2D заданного типа.
*/
template< typename Number >
struct Coord2T {
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Coord2T >  Ptr;
    typedef std::unique_ptr< Coord2T >  UPtr;


    struct { Number x, y; };


    inline Coord2T(
    ) :
        x( static_cast< Number >( 0 ) ),
        y( static_cast< Number >( 0 ) )
    {
    }

    template< typename T >
    inline Coord2T(
        T x, T y
    ) :
        x( static_cast< Number >( x ) ),
        y( static_cast< Number >( y ) )
    {
    }

    template< typename T1, typename T2 >
    inline Coord2T(
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

    operator coord2_t () const;
    operator coord2Double_t () const;
    operator coord2Int_t () const;

    operator size2_t () const;
    operator size2Double_t () const;
    operator size2Int_t () const;

    operator vector2_t () const;
    operator vector2Double_t () const;
    operator vector2Int_t () const;

    inline Coord2T< Number > operator-() const {
        return Coord2T< Number >( -x, -y );
    }

    inline Coord2T< Number > operator+( const Coord2T< Number >& c ) const {
        return Coord2T< Number >( x + c.x,  y + c.y );
    }

    inline Coord2T< Number >& operator+=( const Coord2T< Number >& c ) {
        this->x += c.x;
        this->y += c.y;
        return *this;
    }

    template< typename T >
    inline Coord2T< Number >& operator+=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x += ss;
        this->y += ss;
        return *this;
    }

    template< typename T >
    inline Coord2T< Number > operator+( T s ) const {
        const Number ss = static_cast< Number >( s );
        return Coord2T< Number >( x + ss,  y + ss );
    }

    inline Coord2T< Number > operator-( const Coord2T< Number >& c ) const {
        return Coord2T< Number >( x - c.x,  y - c.y );
    }

    template< typename T >
    inline Coord2T< Number > operator-( T s ) const {
        const Number ss = static_cast< Number >( s );
        return Coord2T< Number >( x - ss,  y - ss );
    }

    inline Coord2T< Number >& operator-=( const Coord2T< Number >& c ) {
        this->x -= c.x;
        this->y -= c.y;
        return *this;
    }

    template< typename T >
    inline Coord2T< Number >& operator-=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x -= ss;
        this->y -= ss;
        return *this;
    }

    inline Coord2T< Number > operator*( const Coord2T< Number >& c ) const {
        return Coord2T< Number >( x * c.x,  y * c.y );
    }

    template< typename T >
    inline Coord2T< Number > operator*( T k ) const {
        const Number kk = static_cast< Number >( k );
        return Coord2T< Number >( x * kk,  y * kk );
    }

    inline Coord2T< Number >& operator*=( const Coord2T< Number >& c ) {
        this->x *= c.x;
        this->y *= c.y;
        return *this;
    }

    template< typename T >
    inline Coord2T< Number >& operator*=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x *= kk;
        this->y *= kk;
        return *this;
    }

    inline Coord2T< Number > operator/( const Coord2T< Number >& c ) const {
        return Coord2T< Number >( x / c.x,  y / c.y );
    }

    template< typename T >
    inline Coord2T< Number > operator/( T k ) const {
        const Number kk = static_cast< Number >( k );
        return Coord2T< Number >( x / kk,  y / kk );
    }

    inline Coord2T< Number >& operator/=( const Coord2T< Number >& c ) {
        this->x /= c.x;
        this->y /= c.y;
        return *this;
    }

    template< typename T >
    inline Coord2T< Number >& operator/=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x /= kk;
        this->y /= kk;
        return *this;
    }


    bool operator==( const Coord2T< Number >& ) const;
    bool operator!=( const Coord2T< Number >& ) const;


    // @todo fine Любые равенства для float должны использ. PRECISION.
    inline bool operator>( const Coord2T< Number >& c ) const {
        return (x > c.x) && (y > c.y);
    }

    inline bool operator>=( const Coord2T< Number >& c ) const {
        return (x >= c.x) && (y >= c.y);
    }

    inline bool operator<( const Coord2T< Number >& c ) const {
        return (x < c.x) && (y < c.y);
    }

    inline bool operator<=( const Coord2T< Number >& c ) const {
        return (x <= c.x) && (y <= c.y);
    }


    /**
    * @return Модуль.
    */
    inline Coord2T< Number > abs() const {
        return
            Coord2T< Number >( std::abs( x ),  std::abs( y ) );
    }


    /**
    * @return Максимальная из координат.
    */
    inline Number max() const {
        return std::max( x, y );
    }


    /**
    * @return Минимальная из координат.
    */
    inline Number min() const {
        return std::min( x, y );
    }


    /**
    * @return Оценка расстояния до центра координат.
    *
    * Работает быстрее distance().
    */
    inline Number estimateDistance() const {
        return (x * x + y * y);
    }


    /**
    * @return Квадрат расстояния до центра координат.
    */
    inline Number squareDistance() const {
        return (x * x + y * y);
    }


    /**
    * @return Расстояние до центра координат.
    *
    * @see estimateDistance()
    */
    template< typename T >
    inline T distance() const {
        return static_cast< T >(
            std::sqrtf( static_cast< float >( x * x + y * y ) )
        );
    }

    inline Number distance() const {
        return distance< Number >();
    }


    /**
    * @return Расстояние до указанной координаты.
    */
    template< typename T >
    inline Number distance( const Coord2T< T >& coord ) const {
        const auto a = x - static_cast< Number >( coord.x );
        const auto b = y - static_cast< Number >( coord.y );
        return static_cast< Number >(
            std::sqrtf( static_cast< float >( a * a + b * b ) )
        );
    }



    /**
    * Доступ к элементам структуры через указатель.
    */
    inline Number* pointer() {
        return reinterpret_cast< Number* >( &x );
    }


    /**
    * @return Координата не определена.
    */
    inline bool undefined() const {
        return (*this == UNDEFINED());
    }


    static inline Coord2T< Number > ZERO() {
        // @tip http://rsdn.ru/forum/cpp.applied/4771369.flat.aspx
        static const Coord2T< Number >  r( 0, 0 );
        return r;
    }


    // @todo fine Детализировать для разных типов. Решить конфликты для INT.
    static inline Coord2T< Number > UNDEFINED() {
        static const Number m = std::numeric_limits< Number >::max();
        static const Coord2T< Number >  r( m, m );
        return r;
    }


    static inline Coord2T< Number > MIN() {
        static const Number m = std::numeric_limits< Number >::min();
        static const Coord2T< Number >  r( m, m );
        return r;
    }


    static inline Coord2T< Number > MAX() {
        static const Number m = std::numeric_limits< Number >::max();
        static const Coord2T< Number >  r( m, m );
        return r;
    }
};


} // typelib







#include "coord2.inl"
