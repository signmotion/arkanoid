#include "../include/stdafx.h"
#include "../include/IRRKIncarnate.h"
#include "../include/ManagerSound.h"


namespace arkanoid {


std::unique_ptr< ManagerSound >  IRRKIncarnate::mManagerSound(
    new ManagerSound()
);




IRRKIncarnate::IRRKIncarnate() {
}




IRRKIncarnate::~IRRKIncarnate() {
}




void
IRRKIncarnate::play( const std::string& file,  float volume,  bool loop ) const {
    mManagerSound->play( PATH_MEDIA + "/" + file,  volume,  loop );
}




void
IRRKIncarnate::stop( bool clear ) {
    mManagerSound->stop( clear );
}


} // arkanoid
