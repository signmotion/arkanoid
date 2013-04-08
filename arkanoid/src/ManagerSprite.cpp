#include "../include/stdafx.h"
#include "../include/ManagerSprite.h"


namespace arkanoid {

    
ManagerSprite::ManagerSprite() {
}




ManagerSprite::~ManagerSprite() {
}




prcore::Bitmap*
ManagerSprite::sprite(
    const pathSprite_t&         path,
    const typelib::size2Int_t&  needVisualSize
) {
    const auto sprite = loadSprite( path, needVisualSize );
    ASSERT( sprite
        && "���������� ������ ��� �������� �� ������." );

    return sprite;
}




void
ManagerSprite::clear() {
    mKnownSprite.clear();
}




prcore::Bitmap*
ManagerSprite::loadSprite(
    const pathSprite_t&         path,
    const typelib::size2Int_t&  needVisualSize
) {
    using namespace prcore;

    ASSERT( !path.empty()
        && "���� � ������� �� ������." );

    // ��������� ���
    auto ftr = mKnownSprite.find( path );
    if (ftr != mKnownSprite.end()) {
        return ftr->second.get();
    }

    // � ���� ����� ����������� ���, ���������
#ifdef _DEBUG
    std::cout << "������ '" << path << "' .. ";
#endif
    const int posExtension = path.find_last_of( '.' );
    const std::string extension =
        (posExtension == std::string::npos)
            ? "" : path.substr( posExtension );
    const bool support =
        (extension == ".png")
     || (extension == ".jpg")
     || (extension == ".tga")
    ;
    if ( !support ) {
        ASSERT( false
            && "���� ��� ����������� �� ��������������." );
        return nullptr;
    }


    // ��������� � ��������
    std::unique_ptr< Bitmap >  imagePtr;
    try {
        imagePtr =
            std::unique_ptr< Bitmap >( new Bitmap( path.c_str() ) );
        imagePtr->ReformatImage( PIXELFORMAT_ARGB8888 );
        if (needVisualSize != typelib::size2Int_t::ZERO()) {
            imagePtr->ResizeImage( needVisualSize.x, needVisualSize.y, true );
        }

    } catch ( ... ) {
        // # ������������ SDK �� �������� ��������� � ������� ���������. �������,
        //   ������� ���������, ��� ������ ������� � ������� PNG, ���������. @todo
        CONSOLE << "(!) ������ �� ������ ��� ������ �� ��������������." << std::endl;
        return nullptr;
    }

    ftr = mKnownSprite.insert(
        std::make_pair( path,  std::move( imagePtr ) )
    ).first;

#ifdef _DEBUG
    std::cout << " OK" << std::endl;
#endif

    return ftr->second.get();
}




typelib::size2Int_t
ManagerSprite::sizeSprite( const pathSprite_t& path ) const {

    try {
        prcore::Bitmap  s( path.c_str() );
        return typelib::size2Int_t( s.GetWidth(), s.GetHeight() );

    } catch ( ... ) {
        // # ������������ SDK �� �������� ��������� � ������� ���������. �������,
        //   ������� ���������, ��� ������ ������� � ������� PNG, ���������. @todo
        CONSOLE << "(!) ������ �� ������ ��� ������ �� ��������������." << std::endl;
        return typelib::size2Int_t::ZERO();
    }
}


} // arkanoid
