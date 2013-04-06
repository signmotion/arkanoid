#include "../include/stdafx.h"
#include "../include/Level.h"


namespace arkanoid {


Level::Level( size_t current ) :
    current( current )
{
    ASSERT( (current > 0)
        && "Номер уровня должен быть больше 0." );

    // загружаем
    const std::string name =
        boost::lexical_cast< std::string >( current ) + ".level";
    const auto data = typelib::json::load( name, PATH_MEDIA );
    ASSERT( !data.undefined()
        && "Уровень должен быть декларирован в формате JSON." );

    // фон
    {
        const auto o = data.at< typelib::json::Object >( "background" );
        ASSERT( !o.empty()
            && "Фон должен быть задан." );
        mAboutBackground.sprite = o.at( "sprite" );
        ASSERT( !mAboutBackground.sprite.empty()
            && "Спрайт фона должен быть задан." );
    }

    // платформа
    {
        const auto o = data.at< typelib::json::Object >( "platform" );
        ASSERT( !o.empty()
            && "Платформа должна быть задана." );
        mAboutPlatform.kind   = o.at( "kind" );
        ASSERT( !mAboutPlatform.kind.empty()
            && "Вид платформы должен быть задан." );
        mAboutPlatform.sprite = o.at( "sprite" );
        ASSERT( !mAboutPlatform.sprite.empty()
            && "Спрайт платформы должен быть задан." );
    }

    // ракетка
    {
        const auto o = data.at< typelib::json::Object >( "racket" );
        ASSERT( !o.empty()
            && "Ракетка должна быть задана." );
        mAboutRacket.kind   = o.at( "kind" );
        ASSERT( !mAboutRacket.kind.empty()
            && "Вид ракетка должен быть задан." );
        mAboutRacket.sprite = o.at( "sprite" );
        ASSERT( !mAboutRacket.sprite.empty()
            && "Спрайт ракетки должен быть задан." );
    }

    // размер ячейки
    {
        const auto a = data.at< typelib::json::Array >( "cell" );
        ASSERT( !a.empty()
            && "Размер ячейки должен быть задан." );
        mCell = typelib::size2Int_t( a[ 0 ], a[ 1 ] );
    }

    // все элементы карты
    {
        const auto o = data.at< typelib::json::Object >( "set" );
        ASSERT( !o.empty()
            && "Для построения уровня необходимо декларировать хотя бы один"
               " элемент карты." );
        for (auto itr = o.cbegin(); itr != o.cend(); ++itr) {
            const sign_t  sign  = itr->first[ 0 ];
            const auto&   about = itr->second;
            
            const std::string  kind =
                about.at( "kind", std::string( "Square" ) );

            const std::string  sprite =
                about.at( "sprite", std::string( "" ) );
            ASSERT( !sprite.empty()
                && "Надо указать спрайт для элемента карты." );

            const std::string  nextInString =
                about.at( "next", std::string( "" ) );
            const sign_t  next =
                nextInString.empty() ? 0 : nextInString[ 0 ];

            const AboutSet ac = { kind, sprite, next };
            const bool inserted =
                mAboutSetSign.insert( std::make_pair( sign, ac ) ).second;
            ASSERT( inserted
                && "Название элемента карты должно быть уникальным в пределах уровня." );

        } // for (auto itr = o.cbegin(); ...
    }

    // карта
    {
        const auto a = data.at< typelib::json::Array >( "map" );
        ASSERT( !a.empty()
            && "Для построения уровня необходимо декларировать карту." );
        for (auto itr = a.cbegin(); itr != a.cend(); ++itr) {
            row_t row = *itr;
            // уберём пробелы
            row.erase( std::remove( row.begin(), row.end(), ' ' ), row.end() );
            mMap.push_back( row );
        }
    }
}




Level::~Level() {
}




bool
Level::has( size_t level ) {
    ASSERT( (level > 0)
        && "Номер уровня должен быть больше 0." );

    const std::string name =
        boost::lexical_cast< std::string >( level ) + ".level";
    std::ifstream  in( PATH_MEDIA + "/" + name.c_str() );

    return in.is_open();
}


} // arkanoid




// @todo operator<<() для консоли.
