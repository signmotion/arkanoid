#pragma once

#include "configure.h"
#include "structure.h"
#include "PPIncarnate.h"
#include "IRRKIncarnate.h"


namespace arkanoid {


/**
* # ќстанки - то, что может остатьс€ после уничтожени€ контейнера.
*/
class Remains :
    public PPIncarnate,
    public IRRKIncarnate
    // # ќстанки не €вл€ютс€ частью физ. мира.
{
public:
    /**
    * »нформаци€ об останках, полученна€ из файла декларации уровн€.
    *
    * @todo fine —ократить конструктор: сейчас часть инфо дублируетс€.
    */
    const AboutRemains  about;




public:
    Remains(
        const std::string&           sprite,
        const typelib::size2Int_t&   needVisualSize,
        const typelib::coord2_t&     coord,
        const AboutRemains&
    );


    virtual ~Remains();




    static std::unique_ptr< Remains >  valueOf(
        const AboutRemains&,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::coord2_t&
    );

};


} // arkanoid
