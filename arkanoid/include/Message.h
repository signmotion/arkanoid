#pragma once

#include "configure.h"
#include "VIncarnate.h"


namespace arkanoid {


/**
* # ��������� - ��� ����� ���������� / �������� ������.
*/
class Message :
    public VIncarnate
{
public:
    /**
    * ���� ���������� �� �������, ��������� ����� �������� �� ������ ����.
    */
    Message(
        const std::string&        sprite,
        const typelib::coord2_t&  coord = typelib::coord2_t::ZERO()
    );


    virtual ~Message();
};


} // arkanoid
