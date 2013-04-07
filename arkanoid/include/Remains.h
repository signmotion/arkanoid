#pragma once

#include "configure.h"
#include "structure.h"
#include "PPIncarnate.h"


namespace arkanoid {


/**
* # ќстанки - то, что может остатьс€ после уничтожени€ контейнера.
*/
class Remains :
    public PPIncarnate
    // # ќстанки не €вл€ютс€ частью физ. мира.
{
public:
    Remains(
        const std::string&           sprite,
        const typelib::size2Int_t&   needVisualSize,
        const typelib::coord2_t&     coord
    );


    virtual ~Remains();




    static std::unique_ptr< Remains >  valueOf(
        const AboutSet&,
        const typelib::size2Int_t&  needVisualSize,
        const typelib::coord2_t&
    );

};


} // arkanoid
