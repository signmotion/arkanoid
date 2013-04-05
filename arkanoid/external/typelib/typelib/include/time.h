#pragma once

#include "../configure.h"
#include <string>



/**
* Работа со временем.
*/

namespace typelib {
    namespace time {


/**
* Тип данных для хранения "сырого времени" (времени в секундах).
*/
typedef long long  raw_t;




/**
* Структура, используемая методами для работы со временем.
*/
template< typename Number >
struct time_t {
    Number eon;
    Number era;
    Number epoch;
    Number year;
    Number month;
    Number day;
    Number hour;
    Number minute;
    Number second;
};




/**
* @return Период времени, переведённый в человеческую строку.
*
* Градация времени задаётся шаблоном класса: можно использовать время,
* отличное от земного.
*/
template<
    raw_t ERA    = 1000, // эр в эоне
    raw_t EPOCH  = 1000, // эпох в эре
    raw_t YEAR   = 1000, // лет в эпохе
    raw_t MONTH  = 12,   // месяцев в году
    raw_t DAY    = 30,   // дней в месяце
    raw_t HOUR   = 24,   // часов в дне
    raw_t MINUTE = 60,   // минут в часе
    raw_t SECOND = 60    // секунд в минуте
>
class Time {
public:
    const raw_t raw;




public:
    /*
    * @param time Время, заданное в секундах.
    */
    template< typename T >
    explicit inline Time( T time ): raw( static_cast< raw_t >( time ) ) {
    }




    template< typename Number >
    inline operator time_t< Number > () const {
        register raw_t dt = raw;
        typelib::time::time_t< Number >  tt;

        static const raw_t K_EON = ERA * EPOCH * YEAR * MONTH * DAY * HOUR * MINUTE * SECOND;
        tt.eon = static_cast< Number >( dt / K_EON );
        dt %= K_EON;

        static const raw_t K_ERA = EPOCH * YEAR * MONTH * DAY * HOUR * MINUTE * SECOND;
        tt.era = static_cast< Number >( dt / K_ERA );
        dt %= K_ERA;

        static const raw_t K_EPOCH = YEAR * MONTH * DAY * HOUR * MINUTE * SECOND;
        tt.epoch = static_cast< Number >( dt / K_EPOCH );
        dt %= K_EPOCH;

        static const raw_t K_YEAR = MONTH * DAY * HOUR * MINUTE * SECOND;
        tt.year = static_cast< Number >( dt / K_YEAR );
        dt %= K_YEAR;

        static const raw_t K_MONTH = DAY * HOUR * MINUTE * SECOND;
        tt.month = static_cast< Number >( dt / K_MONTH );
        dt %= K_MONTH;

        static const raw_t K_DAY = HOUR * MINUTE * SECOND;
        tt.day = static_cast< Number >( dt / K_DAY );
        dt %= K_DAY;

        static const raw_t K_HOUR = MINUTE * SECOND;
        tt.hour = static_cast< Number >( dt / K_HOUR );
        dt %= K_HOUR;

        static const raw_t K_MINUTE = SECOND;
        tt.minute = static_cast< Number >( dt / K_MINUTE );
        dt %= K_MINUTE;

        tt.second = static_cast< Number >( dt );

        return tt;
    }

};


    } // time
} // typelib








namespace std {


template< typename Number >
inline std::ostream& operator<<(
    std::ostream& out,
    const typelib::time::time_t< Number >&  time
) {
    out <<
        time.eon << "|"  << time.era << "|" << time.epoch << " " <<
        time.year <<
          "/" << setfill( '0' ) << setw( 2 ) << time.month <<
          "/" << setfill( '0' ) << setw( 2 ) << time.day <<
        " " <<
        setfill( '0' ) << setw( 2 ) << time.hour <<
          ":" << setfill( '0' ) << setw( 2 ) << time.minute <<
          ":" << setfill( '0' ) << setw( 2 ) << time.second;
    return out;
}




template<
    typelib::time::raw_t  ERA,
    typelib::time::raw_t  EPOCH,
    typelib::time::raw_t  YEAR,
    typelib::time::raw_t  MONTH,
    typelib::time::raw_t  DAY,
    typelib::time::raw_t  HOUR,
    typelib::time::raw_t  MINUTE,
    typelib::time::raw_t  SECOND
>
inline std::ostream& operator<<(
    std::ostream& out,
    const typelib::time::Time< ERA, EPOCH, YEAR, MONTH, DAY, HOUR, MINUTE, SECOND >&  time
) {
    typedef typelib::time::time_t< typelib::time::raw_t >  streamTime_t;
    const auto ts = static_cast< streamTime_t >( time );
    out << ts;
    return out;
}


} // std
