#pragma once

#include "configure.h"
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
        const typelib::coord2_t&     coord,
        const typelib::coord2_t&     rotation
    );


    virtual ~Remains();
};


} // arkanoid
