#pragma once

// �������� ������� ������ � WinDef.h
#define NOMINMAX


#include "coord.h"
#include "vector.h"
#include <limits>


/**
* ����� � 3D.
*/



namespace typelib {

template< typename Number >
struct LineT;

typedef LineT< float >   line_t;
typedef LineT< double >  lineDouble_t;
typedef LineT< int >     lineInt_t;

} // typelib




namespace boost {

// ��� ������ ��������� boost::unordered_set � ��.
// @todo extend �������� operator>() ��� ������ � ����������� STL.
// @todo extend ������� �� �� ��� ������ ����� typelib.
template< typename Number >
std::size_t hash_value( const typelib::LineT< Number >& );

} // boost





namespace std {

template< typename Number >
std::ostream& operator<<( std::ostream&, const typelib::LineT< Number >& );

} // std





namespace typelib {



/**
* ����� � 3D.
*/
template< typename Number >
struct LineT {
    /**
    * ������.
    */
    typedef std::shared_ptr< LineT >  Ptr;
    typedef std::unique_ptr< LineT >  UPtr;


    struct { CoordT< Number >  a, b; };


    inline LineT(
    ) :
        a( 0 ),
        b( 0 )
    {
    }

    /**
    * �����, �������� 2 �������.
    */
    inline LineT(
        CoordT< Number > a,  CoordT< Number > b
    ) :
        a( a ),
        b( a )
    {
    }

    template< typename T1, typename T2 >
    inline LineT(
        const T1 a[ 3 ],  const T2 b[ 3 ]
    ) :
        a( a ),
        b( b )
    {
    }

    /**
    * �����, �������� ������ � ��������-������������.
    */
    inline LineT(
        CoordT< Number > p,  VectorT< Number > v
    ) :
        a( p ),
        b( p + CoordT< Number >( v ) )
    {
    }


    /**
    * @return ���������� ����������� �����.
    *
    * @alias ratio( m1, m2 ), ��� m1 == m2
    */
    inline CoordT< Number > centerRatio() const {
        return (a + b) / 2.0;
    }

    /**
    * @return ���������� �����, ������� ����� ������� � ����������� m1:m2.
    *
    * @source http://matema.narod.ru/1.7.htm
    *
    * @see centerRatio()
    */
    inline CoordT< Number > ratio( Number m1, Number m2 ) const {
        const Number mm = m1 + m2;
        return CoordT< Number >(
            (m2 * a.x + m1 * b.x) / mm,
            (m2 * a.y + m1 * b.y) / mm,
            (m2 * a.z + m1 * b.z) / mm,
        );
    }

    operator line_t () const;
    operator lineDouble_t () const;
    operator lineInt_t () const;

    inline LineT< Number > operator-() const {
        return LineT< Number >( -a, -b );
    }

    inline LineT< Number > operator+( const LineT< Number >& l ) const {
        return LineT< Number >( a + l.a,  b + l.b );
    }

    inline LineT< Number >& operator+=( const LineT< Number >& l ) {
        this->a += l.a;
        this->b += l.b;
        return *this;
    }

    template< typename T >
    inline LineT< Number >& operator+=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->a += ss;
        this->b += ss;
        return *this;
    }

    template< typename T >
    inline LineT< Number > operator+( T s ) const {
        const Number ss = static_cast< Number >( s );
        return LineT< Number >( a + ss,  b + ss );
    }

    inline LineT< Number > operator-( const LineT< Number >& l ) const {
        return LineT< Number >( a - l.a,  b - l.b );
    }

    template< typename T >
    inline LineT< Number > operator-( T s ) const {
        const Number ss = static_cast< Number >( s );
        return LineT< Number >( a - ss,  b - ss );
    }

    inline LineT< Number >& operator-=( const LineT< Number >& l ) {
        this->a -= l.a;
        this->b -= l.b;
        return *this;
    }

    template< typename T >
    inline LineT< Number >& operator-=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->a -= ss;
        this->b -= ss;
        return *this;
    }

    inline LineT< Number > operator*( const LineT< Number >& l ) const {
        return LineT< Number >( a * l.a,  b * l.b );
    }

    template< typename T >
    inline LineT< Number > operator*( T k ) const {
        const Number kk = static_cast< Number >( k );
        return LineT< Number >( a * kk,  b * kk );
    }

    inline LineT< Number >& operator*=( const LineT< Number >& l ) {
        this->a *= l.a;
        this->b *= l.b;
        return *this;
    }

    template< typename T >
    inline LineT< Number > operator*=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->a *= kk;
        this->b *= kk;
        return *this;
    }

    inline LineT< Number > operator/( const LineT< Number >& l ) const {
        return LineT< Number >( a / l.a,  b / l.b );
    }

    template< typename T >
    inline LineT< Number > operator/( T k ) const {
        const Number kk = static_cast< Number >( k );
        return LineT< Number >( a / kk,  b / kk );
    }

    inline LineT< Number >& operator/=( const LineT< Number >& l ) {
        this->a /= l.a;
        this->b /= l.b;
        return *this;
    }

    template< typename T >
    inline LineT< Number > operator/=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->a /= kk;
        this->b /= kk;
        return *this;
    }


    bool operator==( const LineT< Number >& ) const;
    bool operator!=( const LineT< Number >& ) const;


    // @todo fine ����� ��������� ��� float ������ �������. PRECISION.
    inline bool operator>( const LineT< Number >& l ) const {
        return (a > l.a) && (b > l.b);
    }

    inline bool operator>=( const LineT< Number >& l ) const {
        return (a >= l.a) && (b >= l.b);
    }

    inline bool operator<( const LineT< Number >& l ) const {
        return (a < l.a) && (b < l.b);
    }

    inline bool operator<=( const LineT< Number >& l ) const {
        return (a <= l.a) && (b <= l.b);
    }


    /**
    * @return ������ ����� �������.
    *
    * �������� ������� length().
    */
    inline Number estimateLength() const {
        const CoordT< Number > delta = a - b;
        return delta.estimateDistance();
    }


    /**
    * @return ����� �������, ��������� ������.
    *
    * @see estimateLength()
    */
    template< typename T >
    inline T length() const {
        const CoordT< Number > delta = a - b;
        return delta.distance< T >();
    }

    inline Number length() const {
        return length< Number >();
    }


    /**
    * @return ���������� (�����������) ����� �������.
    *
    * @param p1 ����� �� ���� ������, �� ������� ������� ����������.
    * @param p2 ����� �� ������ 'l', �� ������� ������� ����������.
    */
    inline Number distance(
        const LineT< Number >&  l,
        CoordT< Number >*       p1 = nullptr,
        CoordT< Number >*       p2 = nullptr
    ) const;


    /**
    * ������ � ��������� ��������� ����� ���������.
    */
    inline Number const* pointer() const {
        return a.pointer();
    }

    inline Number* pointer() {
        return a.pointer();
    }


    /**
    * @return ����� �� ����������.
    */
    inline bool undefined() const {
        return (*this == UNDEFINED());
    }


    static inline LineT< Number > ZERO() {
        static const LineT< Number > r( 0, 0 );
        return r;
    }


    static inline LineT< Number > UNDEFINED() {
        static const Number m = std::numeric_limits< Number >::max();
        static const LineT< Number > r( m, m );
        return r;
    }
};


} // typelib







#include "line.inl"
