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

    struct Load {
        std::string  sound;
    };

    std::string  sprite;
    Load         load;
};




struct AboutPlatform {

    struct Collision {
        std::string  sound;
    };

    std::string  kind;
    std::string  sprite;
    std::unordered_map< sign_t, Collision >  collision;
};




struct AboutRacket {

    struct Out {
        std::string  sound;
    };

    std::string  kind;
    std::string  sprite;
    Out          out;
};




struct AboutSet {

    struct Collision {
        std::string  sound;
    };

    struct Destroy {
        std::string  sound;
    };

    std::string  kind;
    std::string  sprite;
    sign_t       next;
    std::unordered_map< sign_t, Collision >  collision;
    Destroy      destroy;
};

typedef AboutSet  AboutContainer;
typedef AboutSet  AboutRemains;


typedef std::map< sign_t, AboutSet >  aboutSetSign_t;


} // arkanoid
