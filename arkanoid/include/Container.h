#pragma once

#include "configure.h"
#include "structure.h"
#include "PIncarnate.h"
#include "VIncarnate.h"
#include "SIncarnate.h"


namespace arkanoid {


/**
* # Контейнер - то, что разбивается.
*/
class Container :
    public VIncarnate,
    public PIncarnate,
    public SIncarnate
{
public:
    /**
    * Информация о контейнере, полученная из файла декларации уровня.
    *
    * @todo fine Сократить конструктор: сейчас часть инфо дублируется.
    */
    const AboutContainer  about;




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
        const typelib::coord2_t&    coord,
        const AboutContainer&
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
        const typelib::coord2_t&    coord,
        const AboutContainer&
    );


    virtual ~CubeContainer();
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
        const typelib::coord2_t&    coord,
        const AboutContainer&
    );


    virtual ~SphereContainer();
};


} // arkanoid
