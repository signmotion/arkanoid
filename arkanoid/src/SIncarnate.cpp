#include "../include/stdafx.h"
#include "../include/SIncarnate.h"
#include "../include/ManagerSound.h"


namespace arkanoid {


std::unique_ptr< ManagerSound >  SIncarnate::mManagerSound(
    new ManagerSound()
);




SIncarnate::SIncarnate() {
}




SIncarnate::~SIncarnate() {
}




void
SIncarnate::play( const std::string& file,  float volume,  bool loop ) const {
    mManagerSound->play( PATH_MEDIA + "/" + file,  volume,  loop );
}




void
SIncarnate::stop( bool clear ) {
    mManagerSound->stop( clear );
}


} // arkanoid
