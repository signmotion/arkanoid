#include "../include/stdafx.h"
#include "../include/PPIncarnate.h"
#include "../include/World.h"
#include "../include/ManagerSprite.h"


namespace arkanoid {


std::unique_ptr< ManagerSprite >  PPIncarnate::mManagerSprite(
    new ManagerSprite()
);




PPIncarnate::PPIncarnate(
    const std::string&           sprite,
    const typelib::coord2Int_t&  vc,
    const typelib::size2Int_t&   needVisualSize
) :
    sprite( sprite ),
    mCoord( vc ),
    originalVisualSize( sizeSprite( sprite ) ),
    needVisualSize(
        (needVisualSize == typelib::size2Int_t::ZERO())
          ? originalVisualSize
          : needVisualSize
    ),
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
        PATH_MEDIA + "/" + sprite,
        needVisualSize
    );
    DASSERT( s
        && "Спрайт для элемента не найден." );

    // @todo Показывать вращение.

    SetAlphaFunc( SRCALPHA, SRCINVALPHA );
    SetConstantAlpha( 0xFF, 0xFF );
    AlphaBlend( mCoord.x,  mCoord.y,  context,  *s );
}




typelib::size2Int_t
PPIncarnate::sizeSprite( const std::string&  sprite ) {
    return mManagerSprite->sizeSprite( PATH_MEDIA + "/" + sprite );
}




typelib::coord2Int_t
PPIncarnate::centerSprite( const std::string&  sprite ) {
    const auto size = sizeSprite( sprite );
    return typelib::coord2Int_t(
        WINDOW_WIDTH  / 2 - size.x / 2,
        WINDOW_HEIGHT / 2 - size.y / 2
    );
}


} // arkanoid
