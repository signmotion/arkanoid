#include "../include/stdafx.h"
#include "../include/PPIncarnate.h"
#include "../include/World.h"
#include "../include/ManagerSprite.h"


namespace arkanoid {


std::unique_ptr< ManagerSprite >  PPIncarnate::mManagerSprite(
    new ManagerSprite()
);




PPIncarnate::PPIncarnate(
    const typelib::coord2Int_t&  vc,
    const std::string&           sprite,
    const typelib::size2Int_t&   needVisualSize
) :
    mCoord( vc ),
    sprite( sprite ),
    needVisualSize( needVisualSize ),
    mRotation( 0.0f ),
    mAlpha( 1.0f )
{
}




PPIncarnate::~PPIncarnate() {
}




void
PPIncarnate::draw( prcore::Bitmap& context ) const {

    using namespace prcore;

    auto s = mManagerSprite->sprite(
        needVisualSize,
        PATH_MEDIA + "/" + sprite
    );
    DASSERT( s
        && "Спрайт для элемента не найден." );

    //context.BlitImage( mCoord.x, mCoord.y, *s );

    SetAlphaFunc( SRCALPHA, SRCINVALPHA );
    SetConstantAlpha( 0xFF, 0xFF );
    AlphaBlend( mCoord.x, mCoord.y, context, *s );
}


} // arkanoid
