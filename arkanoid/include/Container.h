#pragma once

#include "configure.h"
#include "structure.h"
#include "B2DIncarnate.h"
#include "PPIncarnate.h"


namespace arkanoid {


/**
* # Контейнер - то, что разбивается.
*/
class Container :
    public PPIncarnate,
    public B2DIncarnate
{
public:
    /**
    * Метка этого контейнера и то, чем он станет после разрушения.
    */
    const sign_t  sign;
    const sign_t  next;




public:
    /**
    * Круглый контейнер.
    */
    Container(
        std::shared_ptr< World >,
        sign_t,
        sign_t                      next,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        size_t                      radius,
        float                       density,
        const typelib::coord2_t&    coord
    );


    /**
    * Полигональный контейнер.
    */
    Container(
        std::shared_ptr< World >,
        sign_t,
        sign_t                      next,
        const std::string&          sprite,
        const typelib::size2Int_t&  needVisualSize,
        const polygon_t&,
        float                       density,
        const typelib::coord2_t&    coord
    );


    virtual ~Container();




    static std::unique_ptr< Container >  valueOf(
        std::shared_ptr< World >,
        sign_t,
        const AboutSet&,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::size2Int_t&  cell,
        const typelib::coord2_t&
    );




    /**
    * @virtual B2DIncarnate
    */
    virtual void sync();

};








/**
* Контейнер в форме сферы.
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
        const typelib::coord2_t&    coord
    );


    virtual ~SphereContainer();
};








/**
* Контейнер в форме куба.
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
        const typelib::coord2_t&    coord
    );


    virtual ~CubeContainer();
};


} // arkanoid
