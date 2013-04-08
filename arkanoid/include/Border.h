#pragma once

#include "configure.h"
#include "structure.h"
#include "B2DIncarnate.h"
#include "PPIncarnate.h"


namespace arkanoid {


class Border :
    public B2DIncarnate
{
public:
    Border(
        std::shared_ptr< World >,
        const typelib::coord2_t&  a,
        const typelib::coord2_t&  b
    );


    virtual ~Border();




    /**
    * @virtual B2DIncarnate
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
