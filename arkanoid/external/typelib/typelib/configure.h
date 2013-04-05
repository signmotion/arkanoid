#pragma once

#include <string>


namespace typelib {


/**
* Язык по умолчанию.
*
* @see typelib::lang_t
*/
static const std::string LANG_DEFAULT_TYPELIB = "rus";




/**
* Включить, если для констант достаточна точность 'float'.
* По умолчанию исп. 'double'.
*/
#define LOW_PRECISION_CONSTANT_TYPELIB




/**
* Включить, если для вычислений достаточна точность 'float'.
* По умолчанию исп. 'double'.
*/
#define LOW_PRECISION_COMPUTE_TYPELIB


} // typelib
