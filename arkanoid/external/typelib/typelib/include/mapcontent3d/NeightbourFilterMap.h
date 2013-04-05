#pragma once

#include "../other.h"
#include "FilterMap.h"
#include "BitMap.h"


namespace typelib {


/**
* ������ ��� MapContent3D.
* ��������� �� ����� ���������� ������ �� ��������, ����� � ��������
* �� ����� NMin � �� ����� NMax ������� ������������.
*
* @template borderState ������������ ������ �� ��������� ����� ��� �����������.
*
* ������� �������
*   - �������� ��������, � ������� ��� �������
*       typelib::NeightbourFilterMap< 0, 0 >
*   - �������� ��������, � ������� ������ 1 �����
*       typelib::NeightbourFilterMap< 1, 1 >
*   - �������� ��������, � ������� �� ����� 4 �������
*       typelib::NeightbourFilterMap< 0, 4 >
*   - �������� ��������, ������� ��������� �������� ��������
*       typelib::NeightbourFilterMap< 26, 26 >
*   - ��. ����� "shape-visualtest".
*/
template< std::size_t NMin, std::size_t NMax, bool borderState >
class NeightbourFilterMap : public FilterMap {
public:

    template< std::size_t SX, std::size_t SY, std::size_t SZ >
    inline void operator()( BitMap< SX, SY, SZ >&  bm ) const {

        typedef BitMap< SX, SY, SZ >  bm_t;

        static_assert( (NMin <= NMax),
            "�������� ������� �������� � ������� \"�������-�������\"." );
        static_assert( ( (NMin <= 26) && (NMax <= 26) ),
            "����� � ������� ����� ��������� �� ����� 26 �������. ��. MapContent3D." );


#ifdef _DEBUG
        std::cout << typeid( *this ).name() << " Count before: " << bm.count() << std::endl;
#endif

        const BitMap< SX, SY, SZ >  copy( bm );
        for (int z = bm_t::minCoord().z; z <= bm_t::maxCoord().z; ++z) {
            for (int y = bm_t::minCoord().y; y <= bm_t::maxCoord().y; ++y) {
                for (int x = bm_t::minCoord().x; x <= bm_t::maxCoord().x; ++x) {

                    const typelib::coordInt_t c( x, y, z );
                    const std::size_t i = bm_t::ic( x, y, z );
                    if ( !copy.test( i ) ) {
                        continue;
                    }

                    std::size_t n = 0;
                    for (std::size_t k = 1; k <= 26; ++k) {
                        const bool has = copy.filled( c, k, borderState );
                        if ( has ) {
                            ++n;
                            // ��� �� ����� �������� ��������� �������,
                            // ���� �������� ������ ���������
                            if (n > NMax) {
                                break;
                            }
                        }
                    }
                    if ( !typelib::between( n, NMin, NMax ) ) {
                        bm.reset( i );
                    }

                } // for (int x = 

            } // for (int y = 

        } // for (int z = 

#ifdef _DEBUG
        std::cout << typeid( *this ).name() << " Count after: " << bm.count() << std::endl;
#endif
    }


};



} // typelib
