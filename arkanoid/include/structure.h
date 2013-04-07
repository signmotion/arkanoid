#pragma once


// ������� ����, ������� �� ������� �� ��������� � ��������� ���� / �����.


namespace arkanoid {


/**
* ����� ��������.
* ������������ ��� ���������� ����� ������.
*/
typedef char  sign_t;




/**
* ��������� ��� �������� ������.
*/
struct AboutBackground {
    std::string  sprite;
};


struct AboutPlatform {
    std::string  kind;
    std::string  sprite;
};


struct AboutRacket {
    std::string  kind;
    std::string  sprite;
};


struct AboutSet {
    std::string  kind;
    std::string  sprite;
    sign_t       next;
};


typedef std::map< sign_t, AboutSet >  aboutSetSign_t;


} // arkanoid
