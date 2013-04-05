#include "../include/stdafx.h"
#include "../include/Level.h"


namespace arkanoid {


Level::Level( size_t current ) :
    current( current )
{
    ASSERT( (current > 0)
        && "����� ������ ������ ���� ������ 0." );

    // ���������
    const std::string name =
        boost::lexical_cast< std::string >( current ) + ".level";
    const auto data = typelib::json::load( name, PATH_MEDIA );
    ASSERT( !data.undefined()
        && "������� ������ ���� ������������ � ������� JSON." );

    {
        const auto o = data.at< typelib::json::Object >( "platform" );
        ASSERT( !o.empty()
            && "��������� ������ ���� ������." );
        mAboutPlatform.kind   = o.at( "kind" );
        ASSERT( !mAboutPlatform.kind.empty()
            && "��� ��������� ������ ���� �����." );
        mAboutPlatform.sprite = o.at( "sprite" );
        ASSERT( !mAboutPlatform.kind.empty()
            && "������ ��������� ������ ���� �����." );
    }

    {
        const auto o = data.at< typelib::json::Object >( "racket" );
        ASSERT( !o.empty()
            && "������� ������ ���� ������." );
        mAboutRacket.kind   = o.at( "kind" );
        ASSERT( !mAboutRacket.kind.empty()
            && "��� ������� ������ ���� �����." );
        mAboutRacket.sprite = o.at( "sprite" );
        ASSERT( !mAboutRacket.kind.empty()
            && "������ ������� ������ ���� �����." );
    }

    {
        const auto a = data.at< typelib::json::Array >( "cell" );
        ASSERT( !a.empty()
            && "������ ������ ������ ���� �����." );
        mCell = typelib::size2Int_t( a[ 0 ], a[ 1 ] );
    }

    {
        const auto o = data.at< typelib::json::Object >( "container" );
        ASSERT( !o.empty()
            && "��� ���������� ������ ���������� ������������� ���� �� ���� ���������." );
        for (auto itr = o.cbegin(); itr != o.cend(); ++itr) {
            const sign_t  sign  = itr->first[ 0 ];
            const auto&   about = itr->second;
            const std::string  kind =
                about.at( "kind", std::string( "Square" ) );
            const std::string  sprite =
                about.at( "sprite", std::string( "" ) );
            ASSERT( !sprite.empty()
                && "���� ������� ������ ��� ����������." );
            const std::string  nextInString =
                about.at( "next", std::string( "" ) );
            const sign_t  next =
                nextInString.empty() ? 0 : nextInString[ 0 ];
            const AboutContainer ac = { kind, sprite, next };
            const bool inserted =
                mAboutContainerSign.insert( std::make_pair( sign, ac ) ).second;
            ASSERT( inserted
                && "�������� ���������� ������ ���� ���������� � �������� ������." );
        }
    }

    {
        const auto a = data.at< typelib::json::Array >( "map" );
        ASSERT( !a.empty()
            && "��� ���������� ������ ���������� ������������� �����." );
        for (auto itr = a.cbegin(); itr != a.cend(); ++itr) {
            row_t row = *itr;
            // ����� �������
            row.erase( std::remove( row.begin(), row.end(), ' ' ), row.end() );
            mContainerMap.push_back( row );
        }
    }
}




Level::~Level() {
}


} // arkanoid




// @todo operator<<() ��� �������.
