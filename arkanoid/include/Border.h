#pragma once

#include "configure.h"
#include "structure.h"
#include "PIncarnate.h"
#include "VIncarnate.h"


namespace arkanoid {


class Border :
    public PIncarnate
{
public:
    Border(
        std::shared_ptr< World >,
        const typelib::coord2_t&  a,
        const typelib::coord2_t&  b
    );


    virtual ~Border();




    /**
    * @virtual PIncarnate
    */
    virtual void sync();
    virtual void selfReaction( const std::string& event );
    virtual void collisionReaction( const GE* );

};








/**
* Граница в форме линии.
*/
class EdgeBorder :
    public Border
{
public:
    EdgeBorder(
        std::shared_ptr< World >,
        const typelib::coord2_t&  a,
        const typelib::coord2_t&  b
    );


    virtual ~EdgeBorder();
};


} // arkanoid
