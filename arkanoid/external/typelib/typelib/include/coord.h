#pragma once

// �������� ������� ������ � WinDef.h
#define NOMINMAX


#include "other.h"
#include <limits>


/**
* 3D-����������.
*/



namespace typelib {

template< typename Number >
struct CoordT;

typedef CoordT< float >   coord_t;
typedef CoordT< double >  coordDouble_t;
typedef CoordT< int >     coordInt_t;

struct relCoordInt_t;


template< typename Number >
struct VectorT;

typedef VectorT< float >   vector_t;
typedef VectorT< double >  vectorDouble_t;
typedef VectorT< int >     vectorInt_t;


} // typelib




namespace boost {

// ��� ������ ��������� boost::unordered_set � ��.
// @todo extend �������� operator>() ��� ������ � ����������� STL.
// @todo extend ������� �� �� ��� ������ ����� typelib.
template< typename Number >
std::size_t hash_value( const typelib::CoordT< Number >& );

} // boost





namespace std {

template< typename Number >
std::ostream& operator<<( std::ostream&, const typelib::CoordT< Number >& );

} // std





namespace typelib {



/**
* ���������� � 3D.
*/
template< typename Number >
struct CoordT {
    /**
    * ������.
    */
    typedef std::shared_ptr< CoordT >  Ptr;
    typedef std::unique_ptr< CoordT >  UPtr;


    struct { Number x, y, z; };


    inline CoordT(
    ) :
        x( static_cast< Number >( 0 ) ),
        y( static_cast< Number >( 0 ) ),
        z( static_cast< Number >( 0 ) )
    {
    }

    template< typename T >
    inline CoordT(
        T x, T y, T z
    ) :
        x( static_cast< Number >( x ) ),
        y( static_cast< Number >( y ) ),
        z( static_cast< Number >( z ) )
    {
    }

    template< typename T1, typename T2, typename T3 >
    inline CoordT(
        T1 x, T2 y, T3 z
    ) :
        x( static_cast< Number >( x ) ),
        y( static_cast< Number >( y ) ),
        z( static_cast< Number >( z ) )
    {
    }

    template< typename T >
    inline CoordT(
        const T d[3]
    ) :
        x( static_cast< Number >( d[0] ) ),
        y( static_cast< Number >( d[1] ) ),
        z( static_cast< Number >( d[2] ) )
    {
    }

    inline CoordT< Number >& operator=( const CoordT< Number >& c ) {
        this->x = c.x;
        this->y = c.y;
        this->z = c.z;
        return *this;
    }

    /**
    * @return �����.
    */
    inline bool center() const {
        return empty( x ) && empty ( y ) && empty( z );
    }

    operator coord_t () const;
    operator coordDouble_t () const;
    operator coordInt_t () const;

    operator vector_t () const;
    operator vectorDouble_t () const;
    operator vectorInt_t () const;

    inline CoordT< Number > operator-() const {
        return CoordT< Number >( -x, -y, -z );
    }

    inline CoordT< Number > operator+( const CoordT< Number >& c ) const {
        return CoordT< Number >( x + c.x,  y + c.y,  z + c.z );
    }

    inline CoordT< Number >& operator+=( const CoordT< Number >& c ) {
        this->x += c.x;
        this->y += c.y;
        this->z += c.z;
        return *this;
    }

    template< typename T >
    inline CoordT< Number >& operator+=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x += ss;
        this->y += ss;
        this->z += ss;
        return *this;
    }

    template< typename T >
    inline CoordT< Number > operator+( T s ) const {
        const Number ss = static_cast< Number >( s );
        return CoordT< Number >( x + ss,  y + ss,  z + ss );
    }

    inline CoordT< Number > operator-( const CoordT< Number >& c ) const {
        return CoordT< Number >( x - c.x,  y - c.y,  z - c.z );
    }

    template< typename T >
    inline CoordT< Number > operator-( T s ) const {
        const Number ss = static_cast< Number >( s );
        return CoordT< Number >( x - ss,  y - ss,  z - ss );
    }

    inline CoordT< Number >& operator-=( const CoordT< Number >& c ) {
        this->x -= c.x;
        this->y -= c.y;
        this->z -= c.z;
        return *this;
    }

    template< typename T >
    inline CoordT< Number >& operator-=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x -= ss;
        this->y -= ss;
        this->z -= ss;
        return *this;
    }

    inline CoordT< Number > operator*( const CoordT< Number >& c ) const {
        return CoordT< Number >( x * c.x,  y * c.y,  z * c.z );
    }

    template< typename T >
    inline CoordT< Number > operator*( T k ) const {
        const Number kk = static_cast< Number >( k );
        return CoordT< Number >( x * kk,  y * kk,  z * kk );
    }

    inline CoordT< Number >& operator*=( const CoordT< Number >& c ) {
        this->x *= c.x;
        this->y *= c.y;
        this->z *= c.z;
        return *this;
    }

    template< typename T >
    inline CoordT< Number >& operator*=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x *= kk;
        this->y *= kk;
        this->z *= kk;
        return *this;
    }

    inline CoordT< Number > operator/( const CoordT< Number >& c ) const {
        return CoordT< Number >( x / c.x,  y / c.y,  z / c.z );
    }

    template< typename T >
    inline CoordT< Number > operator/( T k ) const {
        const Number kk = static_cast< Number >( k );
        return CoordT< Number >( x / kk,  y / kk,  z / kk );
    }

    inline CoordT< Number >& operator/=( const CoordT< Number >& c ) {
        this->x /= c.x;
        this->y /= c.y;
        this->z /= c.z;
        return *this;
    }

    template< typename T >
    inline CoordT< Number >& operator/=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x /= kk;
        this->y /= kk;
        this->z /= kk;
        return *this;
    }


    bool operator==( const CoordT< Number >& ) const;
    bool operator!=( const CoordT< Number >& ) const;


    // @todo fine ����� ��������� ��� float ������ �������. PRECISION.
    inline bool operator>( const CoordT< Number >& c ) const {
        return (x > c.x) && (y > c.y) && (z > c.z);
    }

    inline bool operator>=( const CoordT< Number >& c ) const {
        return (x >= c.x) && (y >= c.y) && (z >= c.z);
    }

    inline bool operator<( const CoordT< Number >& c ) const {
        return (x < c.x) && (y < c.y) && (z < c.z);
    }

    inline bool operator<=( const CoordT< Number >& c ) const {
        return (x <= c.x) && (y <= c.y) && (z <= c.z);
    }


    /**
    * @return ������.
    */
    inline CoordT< Number > abs() const {
        return
            CoordT< Number >( std::abs( x ),  std::abs( y ),  std::abs( z ) );
    }


    /**
    * @return ������������ �� ���������.
    */
    inline Number max() const {
        return std::max( std::max( x, y ), z );
    }


    /**
    * @return ����������� �� ���������.
    */
    inline Number min() const {
        return std::min( std::min( x, y ), z );
    }


    /**
    * @return ������ ���������� �� ������ ���������.
    *
    * �������� ������� distance().
    */
    inline Number estimateDistance() const {
        return (x * x + y * y + z * z);
    }


    /**
    * @return ������ ���������� �� ��������� ����������.
    *
    * �������� ������� distance( CoordT ).
    */
    template< typename T >
    inline Number estimateDistance( const CoordT< T >& coord ) const {
        const auto a = x - static_cast< Number >( coord.x );
        const auto b = y - static_cast< Number >( coord.y );
        const auto c = z - static_cast< Number >( coord.z );
        return (a * a + b * b + c * c);
    }


    /**
    * @return ������� ���������� �� ������ ���������.
    */
    inline Number squareDistance() const {
        return (x * x + y * y + z * z);
    }


    /**
    * @return ���������� �� ������ ���������.
    *
    * @see estimateDistance()
    */
    template< typename T >
    inline T distance() const {
        return static_cast< T >( std::sqrt( x * x + y * y + z * z ) );
    }

    inline Number distance() const {
        return distance< Number >();
    }


    /**
    * @return ���������� �� ��������� ����������.
    */
    template< typename T >
    inline Number distance( const CoordT< T >& coord ) const {
        const auto a = x - static_cast< Number >( coord.x );
        const auto b = y - static_cast< Number >( coord.y );
        const auto c = z - static_cast< Number >( coord.z );
        return static_cast< Number >(
            std::sqrtf( static_cast< float >( a * a + b * b + c * c ) )
        );
    }


    /**
    * ������ � ��������� ��������� ����� ���������.
    */
    inline Number const* pointer() const {
        return reinterpret_cast< Number* >( &x );
    }

    inline Number* pointer() {
        return reinterpret_cast< Number* >( &x );
    }


    /**
    * @return ���������� �� ����������.
    */
    inline bool undefined() const {
        return (*this == UNDEFINED());
    }


    static inline CoordT< Number > ZERO() {
        // @tip http://rsdn.ru/forum/cpp.applied/4771369.flat.aspx
        static const CoordT< Number >  r( 0, 0, 0 );
        return r;
    }


    static inline CoordT< Number > UNDEFINED() {
        static const Number m = std::numeric_limits< Number >::max();
        static const CoordT< Number >  r( m, m, m );
        return r;
    }


    static inline CoordT< Number > MIN() {
        static const Number m = std::numeric_limits< Number >::min();
        static const CoordT< Number >  r( m, m, m );
        return r;
    }


    static inline CoordT< Number > MAX() {
        static const Number m = std::numeric_limits< Number >::max();
        static const CoordT< Number >  r( m, m, m );
        return r;
    }
};





/**
* ���������� � 3D ������������ ��������� ������������ (UID, �����, ��������).
*/
struct relCoordInt_t {
    /**
    * ������.
    */
    typedef std::shared_ptr< relCoordInt_t >  Ptr;
    typedef std::unique_ptr< relCoordInt_t >  UPtr;


    const std::string n;
    const coordInt_t c;


    inline relCoordInt_t() : n( "" ),  c() {
    }


    inline relCoordInt_t(
        const std::string& relativeName,
        const coordInt_t& relativeCoord
    ) : n( relativeName ),  c( relativeCoord )
    {
        assert( ( n.empty() && c.center() )
            && "���������� ���������� (������ 'relativeName') � ���� ������� ����� ���� ������������ ������ ��� coordInt_t(0; 0; 0)." );
    }


    inline relCoordInt_t(
        const std::string& relativeName,
        int x, int y, int z
    ) : n( relativeName ),  c( x, y, z )
    {
        assert( ( n.empty() && c.center() )
            && "���������� ���������� (������ 'relativeName') � ���� ������� ����� ���� ������������ ������ ��� (0; 0; 0)." );
    }


    /*
    // �������� ������� �� ������� "���������������"
    // ������ ����� ���������� (0; 0; 0)
    inline relCoordInt_t(
    ) : n( "" ),  c( 0, 0, 0 )
    {
    }
    */


    /**
    * @return ������� ���������� ��������� ��������.
    */
    inline bool root() const {
        assert( ( n.empty() && c.center() )
            && "���������� ���������� (������ 'n') � ���� ������� ����� ���� ������������ ������ ��� (0; 0; 0)." );
        return n.empty();
    }


    inline relCoordInt_t& operator=( const relCoordInt_t& b ) {
        const_cast< std::string& >( n ) = b.n;
        const_cast< coordInt_t& >( c ) = b.c;
        return *this;
    }


    bool operator==( const relCoordInt_t& b ) const;

    bool operator!=( const relCoordInt_t& b ) const;


    static inline relCoordInt_t ZERO() {
        // @tip http://rsdn.ru/forum/cpp.applied/4771369.flat.aspx
        static const relCoordInt_t r( "", 0, 0, 0 );
        return r;
    }

};


} // typelib







#include "coord.inl"
