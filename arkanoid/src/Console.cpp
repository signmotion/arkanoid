#include "../include/stdafx.h"
#include "../include/Console.h"


namespace arkanoid {


Console*  Console::mInstance = nullptr;

boost::mutex  Console::mtxInstance;
boost::recursive_mutex  Console::mtx;


} // arkanoid
