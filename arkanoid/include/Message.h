#pragma once

#include "configure.h"
#include "PPIncarnate.h"


namespace arkanoid {


/**
* # ��������� - ��� ����� ���������� / �������� ������.
*/
class Message :
    public PPIncarnate
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
