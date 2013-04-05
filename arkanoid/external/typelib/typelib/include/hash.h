#pragma once

#include "../configure.h"
#include "codepage.h"
#include "../external/smallsha1/sha1.h"
#include <string>



/**
* ћетоды дл€ хешировани€.
*/


namespace typelib {
    namespace hash {


/**
* @return —троку, закодированную в SHA1.
* 
* @use http://code.google.com/p/smallsha1
*/
static inline std::string sha1( const std::string& s ) {

    // 20 bytes of sha1 hash
    unsigned char resultByte[20];
    // 40 chars + a zero as result string
    char resultHex[ 40 + 1 ];

    sha1::calc( s.c_str(), s.length(), resultByte );
    sha1::toHexString( resultByte, resultHex );

    return static_cast< std::string >( resultHex );
}






/**
* @return —трока, кириллические символы которой заменены
*         escape-последовательностью и результат закодирован
*         в SHA1.
*
* @info ќчень просто создать идентичные методы на любом €зыке (например,
*       JavaScript) и получить код дл€ быстрого поиска, пон€тный и серверу,
*       и клиентам. ћысль ввести этот метод по€вилась после (безуспешной)
*       попытки подружить кодировки собранной дл€ Windows CouchDB.
*
* @see Name
*/
static inline std::string searchHash( const std::string& s ) {
    const std::string t = convert::codepage::cyrillicEncode( s );
    return sha1( t );
}



    } // hash
} // typelib
