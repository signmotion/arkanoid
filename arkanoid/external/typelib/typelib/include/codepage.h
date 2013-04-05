#pragma once

#include "../configure.h"
#include <assert.h>
#include <string>
#include <windows.h>
#include <locale>
#include <boost/algorithm/string/replace.hpp>



/**
* Методы для конвертирования строк между разными кодировками.
*
* Я сторонник использовать специализированные библиотеки. Для конвертации -
* это iconv. Но если проект требует быстрого запуска, возня с
* неинлайн-библиотеками может затянуться. Поэтому, здесь собрано несколько
* методов, которые *проверены* и позволяют не удлинять хвост библиотек для
* проекта.
*/


namespace typelib {
    namespace convert {
        namespace codepage {


/**
* @return std::wstring из std::string.
*/
static inline std::wstring widen( const std::string& s, const std::locale& loc = std::locale() ) {
    std::wstring out( s.length(), 0 );

    auto itr = s.cbegin();
    auto jtr = out.begin();
    for ( ;  itr != s.cend();  ++itr, ++jtr ) {
        *jtr = std::use_facet< std::ctype< wchar_t > >( loc ).widen( *itr );
    }

    return out;
}





/**
* @return Строка UTF8, которая может быть корректно сохранена в файле под Windows.
*
* Пример кода:
    std::wstring ws( ss.str().length(), L' ' );
    std::copy( ss.str().cbegin(), ss.str().cend(), ws.begin() );
    const std::string utf8ss = typelib::codepage::correctUTF8Windows( ws );
    out << utf8ss.str();

*
* @see Описание проблемы > http://mariusbancila.ro/blog/2008/10/20/writing-utf-8-files-in-c
*/
static inline std::string correctUTF8Windows( const std::wstring& wstr ) {

    const wchar_t* buffer = wstr.c_str();
    const std::size_t length = wstr.size();

    const int nChars = ::WideCharToMultiByte(
        CP_UTF8,
        0,
        buffer,
        length,
        nullptr,
        0,
        nullptr,
        nullptr
    );
    if (nChars == 0) {
        return "";
    };

    std::string newBuffer;
    newBuffer.resize( nChars );
    ::WideCharToMultiByte(
        CP_UTF8,
        0,
        buffer,
        length,
        const_cast< char* >( newBuffer.c_str() ),
        nChars,
        nullptr,
        nullptr
    );

    return newBuffer;
}



static inline std::string correctUTF8Windows( const std::string& str ) {
    const std::wstring wstr = widen( str );
    return correctUTF8Windows( wstr );
}





/**
* @return Строку в формате UTF-8, перекодированную из Windows-1251.
* 
* @source http://linux.org.ru/forum/development/3968525#comment-3970860
*//* - @todo Проверить и включить когда действительно понадобится.
static inline std::string cp1251utf8( const std::string& s ) {
    static const int table[ 128 ] = {
        0x82D0,0x83D0,0x9A80E2,0x93D1,0x9E80E2,0xA680E2,0xA080E2,0xA180E2,
        0xAC82E2,0xB080E2,0x89D0,0xB980E2,0x8AD0,0x8CD0,0x8BD0,0x8FD0,    
        0x92D1,0x9880E2,0x9980E2,0x9C80E2,0x9D80E2,0xA280E2,0x9380E2,0x9480E2,
        0,0xA284E2,0x99D1,0xBA80E2,0x9AD1,0x9CD1,0x9BD1,0x9FD1,               
        0xA0C2,0x8ED0,0x9ED1,0x88D0,0xA4C2,0x90D2,0xA6C2,0xA7C2,              
        0x81D0,0xA9C2,0x84D0,0xABC2,0xACC2,0xADC2,0xAEC2,0x87D0,              
        0xB0C2,0xB1C2,0x86D0,0x96D1,0x91D2,0xB5C2,0xB6C2,0xB7C2,              
        0x91D1,0x9684E2,0x94D1,0xBBC2,0x98D1,0x85D0,0x95D1,0x97D1,            
        0x90D0,0x91D0,0x92D0,0x93D0,0x94D0,0x95D0,0x96D0,0x97D0,
        0x98D0,0x99D0,0x9AD0,0x9BD0,0x9CD0,0x9DD0,0x9ED0,0x9FD0,
        0xA0D0,0xA1D0,0xA2D0,0xA3D0,0xA4D0,0xA5D0,0xA6D0,0xA7D0,
        0xA8D0,0xA9D0,0xAAD0,0xABD0,0xACD0,0xADD0,0xAED0,0xAFD0,
        0xB0D0,0xB1D0,0xB2D0,0xB3D0,0xB4D0,0xB5D0,0xB6D0,0xB7D0,
        0xB8D0,0xB9D0,0xBAD0,0xBBD0,0xBCD0,0xBDD0,0xBED0,0xBFD0,
        0x80D1,0x81D1,0x82D1,0x83D1,0x84D1,0x85D1,0x86D1,0x87D1,
        0x88D1,0x89D1,0x8AD1,0x8BD1,0x8CD1,0x8DD1,0x8ED1,0x8FD1
    };

    std::string r( s.length(), '\0' );
    char* out = &r[0];

    const char* in = &s[0];
    while ( *in ) {
        if ( *in & 0x80 ) {
            int v = table[ (int)(0x7f & *in++) ];
            if (!v) {
                continue;
            }
            *out++ = (char)v;
            *out++ = (char)(v >> 8);
            if (v >>= 16) {
                *out++ = (char)v;
            }
        }
        else {
            *out++ = *in++;
        }
    }
    *out = '\0';

    return r;
}
*/





/**
* Кириллица.
*//* - Заменено на одну константу. См. ниже.
static const std::string cyrillic = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
static const std::string CYRILLIC = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
*/
static const std::string CYRILLIC =
    "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";



/**
* Escape-кодировки для кириллицы.
*//* - Заменено на 1-ну константу. См. ниже.
static const std::string ESCAPE_cyrillic =
    "%E0%E1%E2%E3%E4%E5%B8%E6%E7%E8%E9%EA%EB%EC%ED%EE%EF%F0%F1%F2%F3%F4%F5%F6%F7%F8%F9%FA%FB%FC%FD%FE%FF";
static const std::string ESCAPE_CYRILLIC =
    "%C0%C1%C2%C3%C4%C5%A8%C6%C7%C8%C9%CA%CB%CC%CD%CE%CF%D0%D1%D2%D3%D4%D5%D6%D7%D8%D9%DA%DB%DC%DD%DE%DF";
*/
static const std::string ESCAPE_CYRILLIC =
    "%E0%E1%E2%E3%E4%E5%B8%E6%E7%E8%E9%EA%EB%EC%ED%EE%EF%F0%F1%F2%F3%F4%F5%F6%F7%F8%F9%FA%FB%FC%FD%FE%FF%C0%C1%C2%C3%C4%C5%A8%C6%C7%C8%C9%CA%CB%CC%CD%CE%CF%D0%D1%D2%D3%D4%D5%D6%D7%D8%D9%DA%DB%DC%DD%DE%DF";



/**
* @return Русские буквы, преобразованные в escape-последовательности.
*
* @see cyrillicDecode()
*/
static inline std::string cyrillicEncode( const std::string& s ) {

    /* - @todo optimize Отладить этот - более быстрый - алгоритм.
    //std::string r( s.length() * 3, '\0' );
    std::string r = "";
    r.reserve( s.length() * 3 );
    for (auto itr = s.cbegin(); itr != s.cend(); ++itr) {
        const char ch = *itr;
        if ((ch >= 'а' ) && (ch <= 'я')) {
            const unsigned char pos =
                static_cast< unsigned char >( ch ) - static_cast< unsigned char >( 'а' );
            r += ESCAPE_cyrillic.substr( pos * 3, 3 );
            continue;
        }
        if ((ch >= 'А' ) && (ch <= 'Я')) {
            const unsigned char pos =
                static_cast< unsigned char >( ch ) - static_cast< unsigned char >( 'А' );
            r += ESCAPE_CYRILLIC.substr( pos * 3, 3 );
            continue;
        }
        // @todo optimize А можно быстрее?
        r += std::string( 1, ch );
    }
    */

    std::string r = s;
    std::size_t i = 0;
    for (auto itr = CYRILLIC.cbegin(); itr != CYRILLIC.cend(); ++itr) {
        const std::string ech = ESCAPE_CYRILLIC.substr( i, 3 );
        const char ch = *itr;
        const std::string a( 1, ch );
        boost::replace_all( r, a, ech );
        i += 3;
    }

    return r;
}





/**
* @return Escape-последовательности, преобразованные в русские буквы.
*
* @see cyrillicEncode()
*/
static inline std::string cyrillicDecode( const std::string& s ) {
    
    assert( false && "Не реализовано." );

    return s;
}



        } // codepage
    } // convert
} // typelib
