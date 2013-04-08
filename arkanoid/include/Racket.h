#pragma once

#include "configure.h"
#include "B2DIncarnate.h"
#include "PPIncarnate.h"
#include "IRRKIncarnate.h"


namespace arkanoid {


class Racket :
    public PPIncarnate,
    public B2DIncarnate,
    public IRRKIncarnate
{
public:
    /**
    * ���������� � �������, ���������� �� ����� ���������� ������.
    *
    * @todo fine ��������� �����������: ������ ����� ���� �����������.
    */
    const AboutRacket  about;




public:
    /**
    * ������� �������.
    */
    Racket(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      radius,
        float                       density,
        const typelib::coord2_t&    coord,
        const AboutRacket&
    );


    /**
    * ������������� �������.
    */
    Racket(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        const polygon_t&,
        float                       density,
        const typelib::coord2_t&    coord,
        const AboutRacket&
    );


    virtual ~Racket();




    /**
    * @virtual B2DIncarnate
    */
    virtual void sync();
    virtual void selfReaction( const std::string& event );
    virtual void collisionReaction( const GE* );




    inline void pushRacket( const typelib::vector2_t&  force ) {
        applyForce( force );
    }

};








/**
* ������� � ����� �����.
*/
class SphereRacket :
    public Racket
{
public:
    SphereRacket(
        std::shared_ptr< World >,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      radius,
        const typelib::coord2_t&    coord,
        const AboutRacket&
    );


    virtual ~SphereRacket();
};


} // arkanoid
