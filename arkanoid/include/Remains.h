#pragma once

#include "configure.h"
#include "structure.h"
#include "PPIncarnate.h"


namespace arkanoid {


/**
* # ������� - ��, ��� ����� �������� ����� ����������� ����������.
*/
class Remains :
    public PPIncarnate
    // # ������� �� �������� ������ ���. ����.
{
public:
    Remains(
        const std::string&           sprite,
        const typelib::size2Int_t&   needVisualSize,
        const typelib::coord2_t&     coord
    );


    virtual ~Remains();




    static std::unique_ptr< Remains >  valueOf(
        const AboutSet&,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::coord2_t&
    );

};


} // arkanoid
