#pragma once

// Отключим макрос в WinDef.h
#define NOMINMAX

#include "../configure.h"
#include "Sign.h"
#include <assert.h>
#include <string>
#include <limits>
#include <ostream>




/**
* Вспомогательные методы и простейшие типы данных.
*/


namespace typelib {


/**
* Точность сравнения чисел с плавающей точкой.
*/
const float PRECISION = 0.00001f;



/**
* @return true, если значение пустое.
*/
static inline bool empty( int v ) {
    return (v == 0);
}


// float, double
template< typename T >
static inline bool empty( T v ) {
    return (std::abs( v ) < PRECISION);
}


static inline bool empty( bool v ) {
    return v;
}


static inline bool empty( const std::string& v ) {
    return v.empty();
}


static inline bool empty( const char* v ) {
    return v ? (v[0] == '\0') : true;
}




/**
* @return true, если значения равны.
*
* @todo fine? Переписать через шаблоны.
*/
static inline bool equal( int a, int b ) {
    return (a == b);
}



// float, double
template< typename T >
static inline bool equal( T a, T b ) {
    return (std::abs( a - b ) < PRECISION);
}



static inline bool equal( const std::string& a, const std::string& b ) {
    return (a == b);
}


static inline bool equal( const char* a, const char* b ) {
    return (strcmp( a, b ) == 0);
}




/**
* @return Минимальное из трёх.
*/
template< typename T1, typename T2, typename T3 >
static inline T1 min( T1 a, T2 b, T3 c ) {
    return std::min( std::min( a, static_cast< T1 >( b ) ),  static_cast< T1 >( c ) );
}




/**
* @return Максимальное из трёх.
*/
template< typename T1, typename T2, typename T3 >
static inline T1 max( T1 a, T2 b, T3 c ) {
    return std::max( std::max( a, static_cast< T1 >( b ) ),  static_cast< T1 >( c ) );
}




/**
* @return Минимальное из четырёх.
*/
template< typename T1, typename T2, typename T3, typename T4 >
static inline T1 min( T1 a, T2 b, T3 c, T4 d ) {
    return std::min(
        std::min( a,                       static_cast< T1 >( b ) ),
        std::min( static_cast< T1 >( c ),  static_cast< T1 >( d ) )
    );
}




/**
* @return Максимальное из четырёх.
*/
template< typename T1, typename T2, typename T3, typename T4 >
static inline T1 max( T1 a, T2 b, T3 c, T4 d ) {
    return std::max(
        std::max( a,                       static_cast< T1 >( b ) ),
        std::max( static_cast< T1 >( c ),  static_cast< T1 >( d ) )
    );
}




/**
* @return Среднее арифметическое из двух.
*/
template< typename T1, typename T2 >
static inline T1 average( T1 a, T2 b ) {
    return (a + static_cast< T1 >( b )) /
        static_cast< T1 >( 2 );
}




/**
* @return Среднее арифметическое из трёх.
*/
template< typename T1, typename T2, typename T3 >
static inline T1 average( T1 a, T2 b, T3 c ) {
    return (a + static_cast< T1 >( b ) + static_cast< T1 >( c )) /
        static_cast< T1 >( 3 );
}




/**
* @return Среднее арифметическое из четырёх.
*/
template< typename T1, typename T2, typename T3, typename T4 >
static inline T1 average( T1 a, T2 b, T3 c, T4 d ) {
    return (a + static_cast< T1 >( b ) + static_cast< T1 >( c ) + static_cast< T1 >( d )) /
        static_cast< T1 >( 4 );
}





/**
* @return true, если значение лежит в диапазоне [a; b].
*/
template< typename T >
static inline bool between( T v, T a, T b ) {
    return (v >= a) && (v <= b);
}



/**
* @return true, если значение лежит в диапазоне (a; b).
*/
template< typename T >
static inline bool betweenExclude( T v, T a, T b ) {
    return (v > a) && (v < b);
}




/**
* Обрезает значение 'v' до диапазона [a; b].
*
* @see clampr()
*/
template< typename T, typename D >
static inline void clamp( T& v, D a, D b ) {
    assert( (a <= b) && "Invalid clamp range" );

    /* - Заменено. См. ниже.
    v = (v < static_cast< T >( a )) ? static_cast< T >( a )
         : (v > static_cast< T >( b )) ? static_cast< T >( b )
         : v;
    */
    v = std::max(
        std::min( v, static_cast< T >( b ) ),
        static_cast< T >( a )
    );
}




/**
* Обрезает значение 'v' до диапазона [a; b].
*
* @return true, если значение было обрезано.
*
* @see clamp()
*/
template< typename T, typename D >
static inline bool clampr( T& v, D a, D b ) {
    const T saved = v;
    clamp( v, a, b );
    return (saved != v);
}






/**
* @return Символьное представление любого типа данных, для которого
*         определён метод operator<<( std::ostream&, T ).
*/
template< typename T >
static inline std::string string( const T& v ) {
    std::ostringstream ss;
    // лечим точность для float
    ss << std::fixed << v;
    return ss.str();
}


/*
* @alias typelib::string()
*/
template< typename T >
static inline std::string s( const T& v ) {
    return typelib::string( v );
}





/**
* Идентификатор элемента.
*
* Сокр. от Uinique IDentifier.
*/
typedef std::string  uid_t;



/**
* Идентификатор элемента.
*
* Сокр. от Name IDentifier.
*/
typedef std::string  nid_t;





/**
* Язык.
* Указывается в стандарте ISO 639-3. Выбран этот стандарт, т.к. 639-1 и 639-2
* не охватывают всех языков и в них присутствуют неоднозначности.
* http://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%B4%D1%8B_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2
*
* @todo fine optimize Обернуть в класс Lang с фиксир. длиной строки.
*/
typedef std::string  lang_t;





/**
* Печатает список 'v' в поток 'out', обрамляя каждый элемент 'quote',
* разделяя их 'separator'. Список берётся в символьные скобки 'open' / 'close'.
*/
template< class T >
static inline void print(
    std::ostream& out,
    const T& v,
    const std::string& open = "[ ",
    const std::string& close = " ]",
    const std::string& quote = "",
    const std::string& separator = ", "
) {
    assert( (typeid( T ) != typeid( std::string ))
        && "Попытка отобразить строку std::string как список. Это приведёт к печати каждого символа строки со взятием его в 'quote'. Вам этого не надо." );

    out << open;
    const int np = v.size() - 1;
    for (auto itr = std::begin( v ); itr != std::end( v ); ++itr) {
        out << quote << *itr << quote;
        if (std::distance( std::begin( v ), itr ) < np) {
            out << separator;
        }
    }
    if ( v.empty() ) {
        // не делаем лишних пробелов для пустых списков
        if ( !close.empty() && (close[0] == ' ') ) {
            out << close.substr( 1 );
        }
    }
    out << close;
}




/**
* Печатает список 'v' из 'N' элементов в поток 'out', обрамляя каждый элемент 'quote',
* разделяя их 'separator'. Список берётся в символьные скобки 'open' / 'close'.
*/
template< class T, std::size_t N >
static inline void print(
    std::ostream& out,
    const T v[N],
    const std::string& open = "[ ",
    const std::string& close = " ]",
    const std::string& quote = "",
    const std::string& separator = ", "
) {
    assert( (typeid( T ) != typeid( std::string ))
        && "Попытка отобразить строку std::string как список. Это приведёт к печати каждого символа строки со взятием его в 'quote'. Вам этого не надо." );

    out << open;
    for (std::size_t i = 0; i < N; ++i) {
        out << quote << v[i] << quote;
        if (i < (N - 1)) {
            out << separator;
        }
    }
    if (N == 0) {
        // не делаем лишних пробелов для пустых списков
        if ( !close.empty() && (close[0] == ' ') ) {
            out << close.substr( 1 );
        }
    }
    out << close;
}




/**
* То же, что print(), но элементы списка воспринимаются как указатели
* на объекты (разыменовываются).
*/
template< class T >
static inline void printPtr(
    std::ostream& out,
    const T& v,
    const std::string& open = "[ ",
    const std::string& close = " ]",
    const std::string& quote = "",
    const std::string& separator = ", "
) {
    out << open;
    const int np = v.size() - 1;
    for (auto itr = std::begin( v ); itr != std::end( v ); ++itr) {
        out << quote << **itr << quote;
        if (std::distance( std::begin( v ), itr ) < np) {
            out << separator;
        }
    }
    if ( v.empty() ) {
        // не делаем лишних пробелов для пустых списков
        if ( !close.empty() && (close[0] == ' ') ) {
            out << close.substr( 1 );
        }
    }
    out << close;
}




/**
* Печатает карту 'v' в поток 'out', обрамляя каждый элемент 'quote',
* разделяя их 'separator'. Список берётся в символьные скобки 'open' / 'close'.
*/
template< class T >
static inline void printPair(
    std::ostream& out,
    const T& v,
    const std::string& open = "[ ",
    const std::string& close = " ]",
    const std::pair< std::string, std::string >& quote = std::make_pair( "", "" ),
    const std::string& separator = ", "
) {
    out << open;
    const int np = v.size() - 1;
    for (auto itr = std::begin( v ); itr != std::end( v ); ++itr) {
        out << quote.first << itr->first << quote.first <<
            ":" << quote.second << itr->second << quote.second;
        if (std::distance( std::begin( v ), itr ) < np) {
            out << separator;
        }
    }
    if ( v.empty() ) {
        // не делаем лишних пробелов для пустых списков
        if ( !close.empty() && (close[0] == ' ') ) {
            out << close.substr( 1 );
        }
    } else {
        out << close;
    }
}




/**
* То же, что printPair(), но значения карты воспринимаются как указатели
* на объекты (разыменовываются).
*/
template< class T >
static inline void printPairPtr(
    std::ostream& out,
    const T& v,
    const std::string& open = "[ ",
    const std::string& close = " ]",
    const std::pair< std::string, std::string >& quote = std::make_pair( "", "" ),
    const std::string& separator = ", "
) {
    out << open;
    const int np = v.size() - 1;
    for (auto itr = std::begin( v ); itr != std::end( v ); ++itr) {
        out << quote.first << itr->first << quote.first <<
            ":" << quote.second << *itr->second << quote.second;
        if (std::distance( std::begin( v ), itr ) < np) {
            out << separator;
        }
    }
    if ( v.empty() ) {
        // не делаем лишних пробелов для пустых списков
        if ( !close.empty() && (close[0] == ' ') ) {
            out << close.substr( 1 );
        }
    } else {
        out << close;
    }
}




} // typelib
