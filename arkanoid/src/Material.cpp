#include "../include/stdafx.h"
#include "../include/Material.h"


namespace arkanoid {


Material::Material(
    float elasticity,
    float staticFriction,
    float dynamicFriction,
    float softness
) :
    mElasticity( elasticity ),
    mStaticFriction( staticFriction ),
    mDynamicFriction( dynamicFriction ),
    mSoftness( softness )
{
    ASSERT( (elasticity > 0.0f)
        && "����������� ������������ ������ ���� ������ 0." );
    ASSERT( (staticFriction > 0.0f)
        && "����������� ������ ��� ����������� ��� ������ ���� ������ 0." );
    ASSERT( (dynamicFriction > 0.0f)
        && "����������� ������ ��� ���������� ��� ������ ���� ������ 0." );
    ASSERT( (softness > 0.0f)
        && "����������� �������� ������ ���� ������ 0." );
}


    
    
    
std::unique_ptr< Material >  Material::valueOf(
    float elasticity,
    float staticFriction,
    float dynamicFriction,
    float softness
) {
    return std::unique_ptr< Material >( new Material(
        elasticity,  staticFriction,  dynamicFriction,  softness
    ) );
}


} // arkanoid
