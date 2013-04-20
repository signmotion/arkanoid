#pragma once

#include "configure.h"
#include "structure.h"
#include "PIncarnate.h"
#include "VIncarnate.h"
#include "SIncarnate.h"


namespace arkanoid {


/**
* # ��������� - ��, ��� �����������.
*/
class Container :
    public VIncarnate,
    public PIncarnate,
    public SIncarnate
{
public:
    /**
    * ���������� � ����������, ���������� �� ����� ���������� ������.
    *
    * @todo fine ��������� �����������: ������ ����� ���� �����������.
    */
    const AboutContainer  about;




public:
    /**
    * ������� ���������.
    */
    Container(
        std::shared_ptr< World >,
        sign_t,
        sign_t                      next,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      radius,
        float                       density,
        const typelib::coord2_t&    coord,
        const AboutContainer&
    );


    /**
    * ������������� ���������.
    */
    Container(
        std::shared_ptr< World >,
        sign_t,
        sign_t                      next,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        const polygon_t&,
        float                       density,
        const typelib::coord2_t&    coord,
        const AboutContainer&
    );


    virtual ~Container();




    static std::unique_ptr< Container >  valueOf(
        std::shared_ptr< World >,
        sign_t,
        const AboutContainer&,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::size2Int_t&  cell,
        const typelib::coord2_t&
    );




    /**
    * @virtual PIncarnate
    */
    virtual void sync();
    virtual void selfReaction( const std::string& event );
    virtual void collisionReaction( const GE* );

};








/**
* ��������� � ����� ����.
*/
class CubeContainer :
    public Container
{
public:
    CubeContainer(
        std::shared_ptr< World >,
        sign_t,
        sign_t                      next,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        int                         side,
        const typelib::coord2_t&    coord,
        const AboutContainer&
    );


    virtual ~CubeContainer();
};








/**
* ��������� � ����� �����.
*/
class SphereContainer :
    public Container
{
public:
    SphereContainer(
        std::shared_ptr< World >,
        sign_t,
        sign_t                      next,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      radius,
        const typelib::coord2_t&    coord,
        const AboutContainer&
    );


    virtual ~SphereContainer();
};


} // arkanoid
