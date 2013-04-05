#pragma once

#include "coord.h"


/**
* 3D-вектор.
*/



namespace typelib {

template< typename Number >
struct VectorT;

typedef VectorT< float >   vector_t;
typedef VectorT< double >  vectorDouble_t;
typedef VectorT< int >     vectorInt_t;

} // typelib




namespace boost {

// Для работы коллекций boost::unordered_set и пр.
// @todo extend Добавить operator>() для работы с коллекциями STL.
// @todo extend Сделать то же для других типов typelib.
template< typename Number >
std::size_t hash_value( const typelib::VectorT< Number >& );

} // boost





namespace std {

template< typename Number >
std::ostream& operator<<( std::ostream&, const typelib::VectorT< Number >& );

} // std





namespace typelib {


/**
* Вектор в 3D.
*
* @see Многие алгоритмы взяты из Ogre3D::Vector3 > 
*      http://ogre3d.org/docs/api/html/OgreVector3_8h_source.html
*/
template< typename Number >
struct VectorT: public CoordT< Number > {
    /**
    * Ссылки.
    */
    typedef std::shared_ptr< VectorT >  Ptr;
    typedef std::unique_ptr< VectorT >  UPtr;


    inline VectorT() : CoordT< Number >( x, y, z ) {
    }

    template< typename T >
    inline VectorT( T x, T y, T z ) : CoordT< Number >( x, y, z ) {
    }

    template< typename T1, typename T2, typename T3 >
    inline VectorT( T1 x, T2 y, T3 z ) : CoordT< Number >( x, y, z ) {
    }

    template< typename T >
    inline VectorT( const T d[3] ) : CoordT< Number >( d ) {
    }


    inline operator CoordT< Number > () const {
        return CoordT< Number >( x, y, z );
    }

    operator vector_t () const;
    operator vectorDouble_t () const;
    operator vectorInt_t () const;

    inline VectorT< Number > operator-() const {
        return VectorT< Number >( -x, -y, -z );
    }

    inline VectorT< Number > operator+( const VectorT< Number >& v ) const {
        return VectorT< Number >( x + v.x,  y + v.y,  z + v.z );
    }

    inline VectorT< Number >& operator+=( const VectorT< Number >& v ) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    template< typename T >
    inline VectorT< Number >& operator+=( T s ) {
        const Number ss = static_cast< Number >( s );
        this->x += ss;
        this->y += ss;
        this->z += ss;
        return *this;
    }

    template< typename T >
    inline VectorT< Number > operator+( T s ) const {
        const Number ss = static_cast< Number >( s );
        return VectorT< Number >( x + ss,  y + ss,  z + ss );
    }

    inline VectorT< Number > operator-( const VectorT< Number >& v ) const {
        return VectorT< Number >( x - v.x,  y - v.y,  z - v.z );
    }

    template< typename T >
    inline VectorT< Number > operator-( T s ) const {
        const Number ss = static_cast< Number >( s );
        return VectorT< Number >( x - ss,  y - ss,  z - ss );
    }

    inline VectorT< Number >& operator-=( const VectorT< Number >& v ) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }

    inline VectorT< Number > operator*( const VectorT< Number >& v ) const {
        return VectorT< Number >( x * v.x,  y * v.y,  z * v.z );
    }

    template< typename T >
    inline VectorT< Number > operator*( T k ) const {
        const Number kk = static_cast< Number >( k );
        return VectorT< Number >( x * kk,  y * kk,  z * kk );
    }

    inline VectorT< Number >& operator*=( const VectorT< Number >& v ) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    template< typename T >
    inline VectorT< Number >& operator*=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x *= kk;
        this->y *= kk;
        this->z *= kk;
        return *this;
    }

    inline VectorT< Number > operator/( const VectorT< Number >& v ) const {
        return VectorT< Number >( x / v.x,  y / v.y,  z / v.z );
    }

    template< typename T >
    inline VectorT< Number > operator/( T k ) const {
        const Number kk = static_cast< Number >( k );
        return VectorT< Number >( x / kk,  y / kk,  z / kk );
    }

    inline VectorT< Number >& operator/=( const VectorT< Number >& v ) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    template< typename T >
    inline VectorT< Number >& operator/=( T k ) {
        const Number kk = static_cast< Number >( k );
        this->x /= kk;
        this->y /= kk;
        this->z /= kk;
        return *this;
    }

    using CoordT< Number >::operator==;
    using CoordT< Number >::operator!=;
    using CoordT< Number >::operator>;
    using CoordT< Number >::operator>=;
    using CoordT< Number >::operator<;
    using CoordT< Number >::operator<=;

    using CoordT< Number >::abs;
    using CoordT< Number >::min;
    using CoordT< Number >::max;

    Number estimateLength() const;
    Number squareLength() const;
    Number length() const;
    Number normalize();

    Number dot( const VectorT< Number >& ) const;

    VectorT< Number > cross( const VectorT< Number >& ) const;

    /**
    * @return Вектор, перпендикулярный заданному.
    */
    VectorT< Number > perpendicular() const;

    /**
    * @return Угол между векторами, радианы.
    */
    Number angle( const VectorT< Number >& ) const;

    using CoordT< Number >::pointer;

    using CoordT< Number >::undefined;

    using CoordT< Number >::ZERO;
    using CoordT< Number >::UNDEFINED;
    using CoordT< Number >::MIN;
    using CoordT< Number >::MAX;

    static inline VectorT< Number > UNIT_X() {
        static const VectorT< Number >  r( 1, 0, 0 );
        return r;
    }

    static inline VectorT< Number > UNIT_Y() {
        static const VectorT< Number >  r( 0, 1, 0 );
        return r;
    }

    static inline VectorT< Number > UNIT_Z() {
        static const VectorT< Number >  r( 0, 0, 1 );
        return r;
    }

    static inline VectorT< Number > UNIT_SCALE() {
        static const VectorT< Number >  r( 1, 1, 1 );
        return r;
    }

};



} // typelib







#include "vector.inl"
