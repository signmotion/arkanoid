#pragma once

/**
* 2D-вектор.
*/



namespace typelib {

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
std::size_t hash_value( const typelib::Vector2T< Number >& );

} // boost





namespace std {

template< typename Number >
std::ostream& operator<<( std::ostream&, const typelib::Vector2T< Number >& );

} // std





namespace typelib {


/**
* Вектор в 2D.
*/
template< typename Number >
struct Vector2T: public Coord2T< Number > {
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< Vector2T >  Ptr;
    typedef std::unique_ptr< Vector2T >  UPtr;


    inline Vector2T() : Coord2T< Number >( x, y ) {
    }

    template< typename T >
    inline Vector2T( T x, T y ) : Coord2T< Number >( x, y ) {
    }

    template< typename T1, typename T2 >
    inline Vector2T( T1 x, T2 y ) : Coord2T< Number >( x, y ) {
    }


    inline operator Coord2T< Number > () const {
        return Coord2T< Number >( x, y );
    }

    operator vector2_t () const;
    operator vector2Double_t () const;
    operator vector2Int_t () const;

    inline Vector2T< Number > operator-() const {
        return Vector2T< Number >( -x, -y );
    }

    inline Vector2T< Number > operator+( const Vector2T< Number >& v ) const {
        return Vector2T< Number >( x + v.x,  y + v.y );
    }

    inline Vector2T< Number >& operator+=( const Vector2T< Number >& v ) {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    template< typename T >
    inline Vector2T< Number >& operator+=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x += ss;
        this->y += ss;
        return *this;
    }

    template< typename T >
    inline Vector2T< Number > operator+( T s ) const {
        const Number ss = static_cast< Number >( s );
        return Vector2T< Number >( x + ss,  y + ss );
    }

    inline Vector2T< Number > operator-( const Vector2T< Number >& v ) const {
        return Vector2T< Number >( x - v.x,  y - v.y );
    }

    template< typename T >
    inline Vector2T< Number > operator-( T s ) const {
        const Number ss = static_cast< Number >( s );
        return Vector2T< Number >( x - ss,  y - ss );
    }

    inline Vector2T< Number >& operator-=( const Vector2T< Number >& v ) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    inline Vector2T< Number > operator*( const Vector2T< Number >& v ) const {
        return Vector2T< Number >( x * v.x,  y * v.y );
    }

    template< typename T >
    inline Vector2T< Number > operator*( T k ) const {
        const Number kk = static_cast< Number >( k );
        return Vector2T< Number >( x * kk,  y * kk );
    }

    inline Vector2T< Number >& operator*=( const Vector2T< Number >& v ) {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    template< typename T >
    inline Vector2T< Number >& operator*=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x *= kk;
        this->y *= kk;
        return *this;
    }

    inline Vector2T< Number > operator/( const Vector2T< Number >& v ) const {
        return Vector2T< Number >( x / v.x,  y / v.y );
    }

    template< typename T >
    inline Vector2T< Number > operator/( T k ) const {
        const Number kk = static_cast< Number >( k );
        return Vector2T< Number >( x / kk,  y / kk );
    }

    inline Vector2T< Number >& operator/=( const Vector2T< Number >& v ) {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    template< typename T >
    inline Vector2T< Number >& operator/=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x /= kk;
        this->y /= kk;
        return *this;
    }

    using Coord2T< Number >::operator==;
    using Coord2T< Number >::operator!=;
    using Coord2T< Number >::operator>;
    using Coord2T< Number >::operator>=;
    using Coord2T< Number >::operator<;
    using Coord2T< Number >::operator<=;

    using Coord2T< Number >::abs;
    using Coord2T< Number >::min;
    using Coord2T< Number >::max;

    Number estimateLength() const;
    Number squareLength() const;
    Number length() const;
    Number normalize();

    Number dot( const Vector2T< Number >& ) const;

    Number cross( const Vector2T< Number >& ) const;

    /**
    * @return Вектор, перпендикулярный заданному.
    */
    Vector2T< Number > perpendicular() const;

    /**
    * @return Угол между векторами, радианы.
    */
    Number angle( const Vector2T< Number >& ) const;

    using Coord2T< Number >::pointer;

    using Coord2T< Number >::undefined;

    using Coord2T< Number >::ZERO;
    using Coord2T< Number >::UNDEFINED;
    using Coord2T< Number >::MIN;
    using Coord2T< Number >::MAX;

    static inline Vector2T< Number > UNIT_X() {
        static const Vector2T< Number >  r( 1, 0 );
        return r;
    }

    static inline Vector2T< Number > UNIT_Y() {
        static const Vector2T< Number >  r( 0, 1 );
        return r;
    }

    static inline Vector2T< Number > UNIT_SCALE() {
        static const Vector2T< Number >  r( 1, 1 );
        return r;
    }

};



} // typelib







#include "vector2.inl"
