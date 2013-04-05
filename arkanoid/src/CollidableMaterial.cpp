#include "../include/stdafx.h"
#include "../include/CollidableMaterial.h"


namespace arkanoid {


CollidableMaterial::CollidableMaterial(
    uidMaterial_t  it,
    to_t&  to,
    uidMaterial_t  uidDefMaterial,
    std::unique_ptr< Material >  defMaterial
) :
    mIt( it ),
    mTo(),
    mDef( std::make_pair( uidDefMaterial, std::move( defMaterial ) ) )
{
    assert( !to.empty()
        && "Список взаимодействующих материалов не должен быть пустым." );

    // инициализация с разрушением исходного списка
    for (auto itr = to.begin(); itr != to.end(); ++itr) {
        mTo.insert( std::make_pair( itr->first,  std::move( itr->second ) ) );
    }
}


    
    
    
CollidableMaterial::CollidableMaterial(
    uidMaterial_t  it,
    uidMaterial_t  uidDefMaterial,
    std::unique_ptr< Material >  defMaterial
) :
    mIt( it ),
    mTo(),
    mDef( std::make_pair( uidDefMaterial, std::move( defMaterial ) ) )
{
    assert( mDef.second
        && "Декларация взаимодействия материалов по умолчанию не должна быть пустой." );
}


    
    
    
std::unique_ptr< CollidableMaterial >  CollidableMaterial::valueOf(
    uidMaterial_t  it,
    to_t&  to,
    uidMaterial_t  uidDefMaterial,
    std::unique_ptr< Material >  defMaterial
) {
    return std::unique_ptr< CollidableMaterial >( new CollidableMaterial(
        it,  to,  uidDefMaterial,  std::move( defMaterial )
    ) );
}


    
    
    
std::unique_ptr< CollidableMaterial >  CollidableMaterial::valueOf(
    uidMaterial_t  it,
    uidMaterial_t  uidDefMaterial,
    std::unique_ptr< Material >  defMaterial
) {
    return std::unique_ptr< CollidableMaterial >( new CollidableMaterial(
        it,  uidDefMaterial,  std::move( defMaterial )
    ) );
}


} // arkanoid
