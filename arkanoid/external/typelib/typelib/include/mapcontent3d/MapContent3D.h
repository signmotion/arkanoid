#pragma once

#include "../../configure.h"
#include "StaticMapContent3D.h"


// @todo fine ������� ���������� ������� > 5 ����� � MapContent3D.inl.


namespace typelib {


template< typename T, std::size_t SX, std::size_t SY, std::size_t SZ >
class MapContent3D;

template< typename T, std::size_t S >
class CubeMapContent3D;


/**
* ����� ����������. 3D. ������� �����.
*
* @template S* ��. StaticMapContent3D.
*
* @see ������� � StaticMapContent3D.
*/
template< typename T, std::size_t SX, std::size_t SY, std::size_t SZ >
class MapContent3D :
    public StaticMapContent3D< SX, SY, SZ > {
public:
    typedef std::shared_ptr< MapContent3D >  Ptr;
    typedef std::unique_ptr< MapContent3D >  UPtr;




public:

    inline MapContent3D() {
        static_assert( ((SX % 2) == 1), "����� ������� �� X ������ ���� ��������." );
        static_assert( ((SY % 2) == 1), "����� ������� �� Y ������ ���� ��������." );
        static_assert( ((SZ % 2) == 1), "����� ������� �� Z ������ ���� ��������." );
    }



    inline virtual ~MapContent3D() {
    }




    /**
    * @return ������ �� ������ ������� �����.
    *         (!) 1D-���������� � ������� �������� 'raw'.
    *         ���� ������� �� ������, ������������ ��������,
    *         ������ ��� ����������� ����� ����� volume().
    *
    * @see raw, next(), ic(), ci()
    */
    virtual index_t first() const = 0;




    /**
    * @return ������ ������ ������� �����.
    *         ���� ������� �� ������, ������������ ��������,
    *         ������ ��� ����������� ����� ����� volume().
    *
    * @see raw, next(), ic(), ci()
    */
    inline virtual index_t firstEmpty() const {
        assert( false
            && "@todo ..." );
    }



    /**
    * @return ��������� �� ������ ������� ����� �� 1D-����������.
    *         ���� ������� �� ������, ������������ ��������,
    *         ������ ��� ����������� ����� ����� volume().
    *
    * @see first(), ic(), ci()
    */
    virtual index_t next( index_t i ) const = 0;



    /**
    * @return ��������� ������ ������� ����� �� 1D-����������.
    *         ���� ������� �� ������, ������������ ��������,
    *         ������ ��� ����������� ����� ����� volume().
    *
    * @see first(), ic(), ci()
    */
    virtual index_t nextEmpty( index_t i ) const {
        assert( false
            && "@todo ..." );
    }




    /**
    * @return ������� ���������� �� ������ - !T.empty() - ��������
    *         �� �����. ���� ���� �����: edgeZ() - g�� ��� Z. ����
    *         �������� �� ����� ���, ��������� �� �������� (�������
    *         ��������� ����� �� empty()).
    */
    inline std::pair< int, int >  edgeZ() const {
        std::pair< int, int >
            r( maxCoord().z + 1,  minCoord().z - 1 );
        std::size_t i = first();
        do {
            const coordInt_t c = ci( i );
            if (c.z < r.first) {
                r.first = c.z;
            }
            if (c.z > r.second) {
                r.second = c.z;
            }

            i = next( i );

        } while (i != 0);

        return r;
    }





    /**
    * @return ��������� � ��������� ������� ������ �� ������.
    *
    * ���� �������� ������ ������� �� ������� 3D-������� (������ ����� ��
    * �������), ���������� 'false'.
    *
    * @param � ��������������� ������.
    * @param k ����� �������� ������. ��������� ������ - ��. ����. � ������.
    * @param borderState ������������ ������ �� ��������� ����� ��� �����������.
    *
    * @todo ������� borderState � template.
    */
    inline bool filled( const coordInt_t& c, std::size_t k, bool borderState ) const {
        assert( inside( c ) && "���������� ����� �� ��������� �����." );
        const coordInt_t coordCell = c + isc( k );
        if ( outside( coordCell ) ) {
            return borderState;
        }
        return test( coordCell );
    }



    /**
    * @return ���������� �� *����* 6-�� ������ ������ - �� ������.
    *         ����������� ������ 1, 2, 3, 4, 9, 18 - ��. ����. � ������.
    *
    * @see filled(), any6Filled()
    */
    inline bool all6Filled( const coordInt_t& c, bool borderState ) const {
        return
            // �������
            filled( c, 1, borderState )
            // ������
         && filled( c, 2, borderState )
            // ������
         && filled( c, 3, borderState )
            // �����
         && filled( c, 4, borderState )
            // �������
         && filled( c, 9, borderState )
            // �������
         && filled( c, 18, borderState );
    }




    /**
    * @return ���������� �� *����* 26-�� ������ ������ - �� ������.
    *
    * @see filled(), any26Filled()
    */
    inline bool all26Filled( const coordInt_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 26; ++k) {
            if ( !filled( c, k, borderState ) ) {
                return false;
            }
        }
        return true;
    }




    /**
    * @return ���������� � *�����* �� 6-�� ������ ������ - �� ������.
    *
    * @see filled(), all6Filled()
    */
    inline bool any6Filled( const coordInt_t& c, bool borderState ) const {
        return
            // �������
            filled( c, 1, borderState )
            // ������
         || filled( c, 2, borderState )
            // ������
         || filled( c, 3, borderState )
            // �����
         || filled( c, 4, borderState )
            // �������
         || filled( c, 9, borderState )
            // �������
         || filled( c, 18, borderState );
    }




    /**
    * @return ���������� � *�����* �� 26-�� ������ ������ - �� ������.
    *
    * @see filled(), all26Filled()
    */
    inline bool any26Filled( const coordInt_t& c, bool borderState ) const {
        for (std::size_t k = 1; k <= 26; ++k) {
            if ( filled( c, k, borderState ) ) {
                return true;
            }
        }
        return false;
    }





    /**
    * @param i ���������� ����������.
    *
    * @see ic()
    */
    virtual void set( std::size_t i, const T& value ) = 0;


    virtual void set( const T& value ) = 0;


    inline void set( const coordInt_t& c, const T& value ) {
        set( ic( c ),  value );
    }


    inline bool set( int x, int y, int z, const T& value ) {
        return set( ic( x, y, z ),  value );
    }



    /**
    * @param i ���������� ����������.
    *
    * @see ic()
    */
    void reset( std::size_t i ) {
        set( i, T() );
    }


    inline void reset( const coordInt_t& c ) {
        reset( ic( c ) );
    }


    inline void reset( int x, int y, int z ) {
        reset( ic( x, y, z ) );
    }


    inline void reset() {
        set( T() );
    }




    /**
    * @return ���������� ��������� ������.
    *//* - @todo ...
    virtual T value( std::size_t i ) const = 0;

    virtual T value( const coordInt_t& c ) const = 0;

    virtual T value( int x, int y, int z ) const = 0;
    */



    /**
    * @return ���������� ��������� ������ - �� ������.
    */
    virtual bool test( std::size_t i ) const = 0;

    virtual bool test( const coordInt_t& c ) const = 0;

    virtual bool test( int x, int y, int z ) const = 0;




    /**
    * @return ���������� �� ������ ������.
    */
    virtual std::size_t count() const = 0;



    /**
    * @return ����� �� �������� ������ (��� ������ - ������).
    */
    inline bool empty() const {
        return (count() == 0);
    }

};





/**
* �� ��, ��� StaticMapContent3D, �� � ���� ����.
*/
template< typename T, std::size_t S >
class CubeMapContent3D :
    public MapContent3D< T, S, S, S > {
};




} // typelib
