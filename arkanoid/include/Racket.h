#pragma once

#include "configure.h"
#include "PIncarnate.h"
#include "VIncarnate.h"
#include "SIncarnate.h"


namespace arkanoid {


class Racket :
    public VIncarnate,
    public PIncarnate,
    public SIncarnate
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
    * @virtual PIncarnate
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
