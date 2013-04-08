#pragma once

#include "configure.h"
#include "structure.h"


namespace arkanoid {


/**
* ����� ��� ���������� ������� ���������.
* ���� ������ (������, �������, ������, ...) ������ ����� � ������
* ������� ���������, �� ������ ������������� �� ����� ������.
*/
class GE {
public:
    /**
    * ����� ����� �������� � ��, �� ��� �� ������������ (��������, �����
    * ����������).
    *
    * # ���� ������� �� ������ ���� �������� �� �����, �������� ����� = 0.
    */
    const sign_t  sign;
    const sign_t  next;



public:
    GE( sign_t sign, sign_t next );


    virtual ~GE();
};


} // arkanoid
