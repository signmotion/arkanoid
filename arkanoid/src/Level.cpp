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


    // ���
    {
        static const AboutBackground  EMPTY = {};
        mAboutBackground = EMPTY;

        // .
        const auto o = data.at< typelib::json::Object >( "background" );
        ASSERT( !o.empty()
            && "��� ������ ���� �����." );
        mAboutBackground.sprite = o.at( "sprite" );
        ASSERT( !mAboutBackground.sprite.empty()
            && "������ ���� ������ ���� �����." );

        // load
        if ( o.has( "load" ) ) {
            const auto variant = o.at( "load" );
            const AboutBackground::Load  load = {
                variant.at( "sound", std::string( "" ) )
            };
            mAboutBackground.load = load;
        }
    }


    // ���������
    {
        static const AboutPlatform  EMPTY = {};
        mAboutPlatform = EMPTY;

        // .
        const auto o = data.at< typelib::json::Object >( "platform" );
        ASSERT( !o.empty()
            && "��������� ������ ���� ������." );
        mAboutPlatform.kind = o.at( "kind" );
        ASSERT( !mAboutPlatform.kind.empty()
            && "��� ��������� ������ ���� �����." );
        mAboutPlatform.sprite = o.at( "sprite" );
        ASSERT( !mAboutPlatform.sprite.empty()
            && "������ ��������� ������ ���� �����." );

        // collision
        if ( o.has( "collision" ) ) {
            const auto variant = o.at( "collision" );
            const auto o2 = static_cast< typelib::json::Object >( variant );
            for (auto itr = o2.cbegin(); itr != o2.cend(); ++itr) {
                const sign_t  sign  = itr->first[ 0 ];
                const auto&   about = itr->second;
            
                const AboutPlatform::Collision  collision = {
                    about.at( "sound", std::string( "" ) )
                };
                const bool inserted = mAboutPlatform.collision.insert(
                    std::make_pair( sign, collision )
                ).second;
                ASSERT( inserted
                    && "�������� �������� ����� ������ ���� ���������� � ��������"
                       " ��������� 'collision'." );

            } // for (auto itr = o2.cbegin(); ...
        }
    }


    // �������
    {
        static const AboutRacket  EMPTY = {};
        mAboutRacket = EMPTY;

        // .
        const auto o = data.at< typelib::json::Object >( "racket" );
        ASSERT( !o.empty()
            && "������� ������ ���� ������." );
        mAboutRacket.kind = o.at( "kind" );
        ASSERT( !mAboutRacket.kind.empty()
            && "��� ������� ������ ���� �����." );
        mAboutRacket.sprite = o.at( "sprite" );
        ASSERT( !mAboutRacket.sprite.empty()
            && "������ ������� ������ ���� �����." );

        // out
        if ( o.has( "out" ) ) {
            const auto variant = o.at( "out" );
            const AboutRacket::Out  out = {
                variant.at( "sound", std::string( "" ) )
            };
            mAboutRacket.out = out;
        }
    }


    // ������ ������
    {
        mCell = typelib::size2Int_t::ZERO();

        // .
        const auto a = data.at< typelib::json::Array >( "cell" );
        ASSERT( !a.empty()
            && "������ ������ ������ ���� �����." );
        mCell = typelib::size2Int_t( a[ 0 ], a[ 1 ] );
    }


    // ��� �������� ����� (�����)
    {
        mAboutSetSign.clear();

        // .
        const auto o = data.at< typelib::json::Object >( "set" );
        ASSERT( !o.empty()
            && "��� ���������� ������ ���������� ������������� ���� �� ����"
               " ������� �����." );
        for (auto itr = o.cbegin(); itr != o.cend(); ++itr) {
            const sign_t  sign  = itr->first[ 0 ];
            const auto&   about = itr->second;
            
            AboutSet aboutSet = {};

            aboutSet.kind = about.at( "kind", std::string( "Square" ) );

            aboutSet.sprite = about.at( "sprite", std::string( "" ) );
            ASSERT( !aboutSet.sprite.empty()
                && "���� ������� ������ ��� �������� �����." );

            const std::string  nextInString =
                about.at( "next", std::string( "" ) );
            aboutSet.next = nextInString.empty() ? 0 : nextInString[ 0 ];

            // collision
            if ( about.has( "collision" ) ) {
                const auto variant = about[ "collision" ];
                const auto o2 = static_cast< typelib::json::Object >( variant );
                for (auto itr = o2.cbegin(); itr != o2.cend(); ++itr) {
                    const sign_t  sign  = itr->first[ 0 ];
                    const auto&   about = itr->second;
            
                    const AboutContainer::Collision  collision = {
                        about.at( "sound", std::string( "" ) )
                    };
                    const bool inserted = aboutSet.collision.insert(
                        std::make_pair( sign, collision )
                    ).second;
                    ASSERT( inserted
                        && "�������� �������� ����� ������ ���� ���������� � ��������"
                           " ��������� 'collision'." );

                } // for (auto itr = o2.cbegin(); ...
            }

            // destroy
            if ( about.has( "destroy" ) ) {
                const auto variant = about[ "destroy" ];
                const AboutSet::Destroy  destroy = {
                    variant.at( "sound", std::string( "" ) )
                };
                aboutSet.destroy = destroy;
            }

            const bool inserted =
                mAboutSetSign.insert( std::make_pair( sign, aboutSet ) ).second;
            ASSERT( inserted
                && "�������� �������� ����� ������ ���� ���������� � �������� ������." );

        } // for (auto itr = o.cbegin(); ...
    }


    // �����
    {
        mMap.clear();

        // .
        const auto a = data.at< typelib::json::Array >( "map" );
        ASSERT( !a.empty()
            && "��� ���������� ������ ���������� ������������� �����." );
        for (auto itr = a.cbegin(); itr != a.cend(); ++itr) {
            row_t row = *itr;
            // ����� �������
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
        && "����� ������ ������ ���� ������ 0." );

    const std::string name =
        boost::lexical_cast< std::string >( level ) + ".level";
    std::ifstream  in( PATH_MEDIA + "/" + name.c_str() );

    return in.is_open();
}


} // arkanoid




// @todo operator<<() ��� �������.
