#pragma once

#include "configure.h"
#include "structure.h"
#include "VIncarnate.h"
#include "SIncarnate.h"


namespace arkanoid {


/**
* # ������� - ��, ��� ����� �������� ����� ����������� ����������.
*/
class Remains :
    public VIncarnate,
    public SIncarnate
    // # ������� �� �������� ������ ���. ����.
{
public:
    /**
    * ���������� �� ��������, ���������� �� ����� ���������� ������.
    *
    * @todo fine ��������� �����������: ������ ����� ���� �����������.
    */
    const AboutRemains  about;




public:
    Remains(
        const std::string&           sprite,
        const typelib::size2Int_t&   needVisualSize,
        const typelib::coord2_t&     coord,
        const AboutRemains&
    );


    virtual ~Remains();




    static std::unique_ptr< Remains >  valueOf(
        const AboutRemains&,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::coord2_t&
    );

};


} // arkanoid
