#include "../include/stdafx.h"
#include "../include/ManagerSound.h"


namespace arkanoid {

    
ManagerSound::ManagerSound(
) :
    mEngine( irrklang::createIrrKlangDevice() )
{
    ASSERT( mEngine
        && "�������� ������ �� ���������������." );
}




ManagerSound::~ManagerSound() {
    /* - ����� ��������� �����������.
    mEngine->drop();
    */
}




void
ManagerSound::play( const pathSound_t&  path,  float volume,  bool loop ) {

    const auto source = sound( path );
    source->setDefaultVolume( volume );
    mEngine->play2D( source, loop );
}




void
ManagerSound::stop( bool clear ) {

    mEngine->stopAllSounds();
    if ( clear ) {
        mEngine->removeAllSoundSources();
        mKnownSound.clear();
    }
}




irrklang::ISoundSource*
ManagerSound::sound( const pathSound_t&  path ) {

    const auto source = loadSound( path );
    ASSERT( source
        && "���������� �������� ����� �� ������." );

    return source;
}




irrklang::ISoundSource*
ManagerSound::loadSound( const pathSound_t&  path ) {

    using namespace irrklang;

    ASSERT( !path.empty()
        && "���� � ��������� ����� �� ������." );

    // ��������� ���
    auto ftr = mKnownSound.find( path );
    if (ftr != mKnownSound.end()) {
        return ftr->second;
    }

    // � ���� ����� ����� ���, ���������
#ifdef _DEBUG
    std::cout << "���� '" << path << "' .. ";
#endif

    // ��������� � ��������
    irrklang::ISoundSource* soundPtr = nullptr;
    try {
        soundPtr = mEngine->addSoundSourceFromFile( path.c_str() );

    } catch ( ... ) {
        CONSOLE << "(!) �������� ����� �� ������ ��� ������ �� ��������������." << std::endl;
        return nullptr;
    }

    if ( !soundPtr ) {
        return nullptr;
    }

    ftr = mKnownSound.insert(
        std::make_pair( path, soundPtr )
    ).first;

#ifdef _DEBUG
    std::cout << " OK" << std::endl;
#endif

    return ftr->second;
}


} // arkanoid
