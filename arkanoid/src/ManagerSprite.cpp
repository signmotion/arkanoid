#include "../include/stdafx.h"
#include "../include/ManagerSprite.h"


namespace arkanoid {

    
ManagerSprite::ManagerSprite() {
}




ManagerSprite::~ManagerSprite() {
}




prcore::Bitmap*
ManagerSprite::sprite(
    const typelib::size2Int_t&  needVisualSize,
    const pathSprite_t&  path
) {
    const auto sprite = loadSprite( needVisualSize, path );
    ASSERT( sprite
        && "���������� ������ ��� �������� �� ������." );

    return sprite;
}




prcore::Bitmap*
ManagerSprite::loadSprite(
    const typelib::size2Int_t&  needVisualSize,
    const pathSprite_t&  path
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
        imagePtr->ResizeImage( needVisualSize.x, needVisualSize.y, true );

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


} // arkanoid
