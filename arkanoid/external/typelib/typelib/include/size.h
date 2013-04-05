#pragma once

/**
* 3D-размер.
*/



namespace typelib {

template< typename Number >
struct SizeT;

typedef SizeT< float >   size_t;
typedef SizeT< double >  sizeDouble_t;
typedef SizeT< int >     sizeInt_t;


template< typename Number >
struct CoordT;

typedef CoordT< float >   coord_t;
typedef CoordT< double >  coordDouble_t;
typedef CoordT< int >     coordInt_t;

} // typelib




namespace boost {

// Для работы коллекций boost::unordered_set и пр.
// @todo extend Добавить operator>() для работы с коллекциями STL.
// @todo extend Сделать то же для других типов typelib.
template< typename Number >
std::size_t hash_value( const typelib::SizeT< Number >& );

} // boost





namespace std {

template< typename Number >
std::ostream& operator<<( std::ostream&, const typelib::SizeT< Number >& );

} // std





namespace typelib {


/**
* Размер в 3D.
*/
template< typename Number >
struct SizeT {
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< SizeT >  Ptr;
    typedef std::unique_ptr< SizeT >  UPtr;


    struct { Number x, y, z; };


    inline SizeT(
    ) :
        x( static_cast< Number >( 0 ) ),
        y( static_cast< Number >( 0 ) ),
        z( static_cast< Number >( 0 ) )
    {
    }

    template< typename T >
    inline SizeT(
        T n
    ) :
        x( static_cast< Number >( n ) ),
        y( static_cast< Number >( n ) ),
        z( static_cast< Number >( n ) )
    {
    }

    template< typename T >
    inline SizeT(
        T x, T y, T z
    ) :
        x( static_cast< Number >( x ) ),
        y( static_cast< Number >( y ) ),
        z( static_cast< Number >( z ) )
    {
    }

    template< typename T1, typename T2, typename T3 >
    inline SizeT(
        T1 x, T2 y, T2 z
    ) :
        x( static_cast< Number >( x ) ),
        y( static_cast< Number >( y ) ),
        z( static_cast< Number >( z ) )
    {
    }


    template< typename T >
    inline SizeT(
        const T d[3]
    ) :
        x( static_cast< Number >( d[0] ) ),
        y( static_cast< Number >( d[1] ) ),
        z( static_cast< Number >( d[2] ) )
    {
    }

    /**
    * @return Центр.
    */
    inline bool center() const {
        return empty( x ) && empty ( y ) && empty ( z );
    }

    operator size_t () const;
    operator sizeDouble_t () const;
    operator sizeInt_t () const;

    operator coord_t () const;
    operator coordDouble_t () const;
    operator coordInt_t () const;


    inline SizeT< Number > operator-() const {
        return SizeT< Number >( -x, -y, -z );
    }

    inline SizeT< Number > operator+( const SizeT< Number >& v ) const {
        return SizeT< Number >( x + v.x,  y + v.y,  z + v.z );
    }

    inline SizeT< Number >& operator+=( const SizeT< Number >& v ) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    template< typename T >
    inline SizeT< Number >& operator+=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x += ss;
        this->y += ss;
        this->z += ss;
        return *this;
    }

    template< typename T >
    inline SizeT< Number > operator+( T s ) const {
        const Number ss = static_cast< Number >( s );
        return SizeT< Number >( x + ss,  y + ss,  z + ss );
    }

    inline SizeT< Number > operator-( const SizeT< Number >& v ) const {
        return SizeT< Number >( x - v.x,  y - v.y,  z - v.z );
    }

    template< typename T >
    inline SizeT< Number > operator-( T s ) const {
        const Number ss = static_cast< Number >( s );
        return SizeT< Number >( x - ss,  y - ss,  z - ss );
    }

    inline SizeT< Number >& operator-=( const SizeT< Number >& v ) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }

    inline SizeT< Number > operator*( const SizeT< Number >& v ) const {
        return SizeT< Number >( x * v.x,  y * v.y,  z * v.z );
    }

    template< typename T >
    inline SizeT< Number > operator*( T k ) const {
        const Number kk = static_cast< Number >( k );
        return SizeT< Number >( x * kk,  y * kk,  z * kk );
    }

    inline SizeT< Number >& operator*=( const SizeT< Number >& v ) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    template< typename T >
    inline SizeT< Number >& operator*=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x *= kk;
        this->y *= kk;
        this->z *= kk;
        return *this;
    }

    inline SizeT< Number > operator/( const SizeT< Number >& v ) const {
        return SizeT< Number >( x / v.x,  y / v.y,  z / v.z );
    }

    template< typename T >
    inline SizeT< Number > operator/( T k ) const {
        const Number kk = static_cast< Number >( k );
        return SizeT< Number >( x / kk,  y / kk,  z / kk );
    }

    inline SizeT< Number >& operator/=( const SizeT< Number >& v ) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    template< typename T >
    inline SizeT< Number >& operator/=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x /= kk;
        this->y /= kk;
        this->z /= kk;
        return *this;
    }


    bool operator==( const SizeT< Number >& ) const;
    bool operator!=( const SizeT< Number >& ) const;


    // @todo fine Любые равенства для float должны использ. PRECISION.
    inline bool operator>( const SizeT< Number >& c ) const {
        return (x > c.x) && (y > c.y) && (z > c.z);
    }

    inline bool operator>=( const SizeT< Number >& c ) const {
        return (x >= c.x) && (y >= c.y) && (z >= c.z);
    }

    inline bool operator<( const SizeT< Number >& c ) const {
        return (x < c.x) && (y < c.y) && (z < c.z);
    }

    inline bool operator<=( const SizeT< Number >& c ) const {
        return (x <= c.x) && (y <= c.y) && (z <= c.z);
    }


    /**
    * @return Максимальная из сторон.
    */
    inline Number max() const {
        return std::max( std::max( x, y ), z );
    }


    /**
    * @return Минимальная из сторон.
    */
    inline Number min() const {
        return std::min( std::min( x, y ), z );
    }


    Number volume() const;
    Number square() const;


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


    static inline SizeT< Number > ZERO() {
        // @tip http://rsdn.ru/forum/cpp.applied/4771369.flat.aspx
        static const SizeT< Number >  r( 0, 0, 0 );
        return r;
    }


    static inline SizeT< Number > ONE() {
        static const SizeT< Number >  r( 1, 1, 1 );
        return r;
    }


    static inline SizeT< Number > UNDEFINED() {
        static const Number m = std::numeric_limits< Number >::max();
        static const SizeT< Number >  r( m, m, m );
        return r;
    }
};



} // typelib







#include "size.inl"
