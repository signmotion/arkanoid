namespace typelib {
    namespace compute {
        namespace physics {


inline real_t orbitalSpeed(
    real_t massOrbitBody,
    real_t massCenterBody,
    real_t distance
) {
    return std::sqrt(
        constant::physics::G * massCenterBody * massCenterBody /
        ( (massOrbitBody + massCenterBody) * distance )
    );
}




inline std::pair< real_t, real_t >  speedElasticCollision(
    real_t massA,  real_t speedA,
    real_t massB,  real_t speedB
) {
    const real_t allMass = massA + massB;
    const real_t va =
        (speedA * (massA - massB) + 2.0f * massB * speedB) / allMass;
    const real_t vb =
        (speedB * (massB - massA) + 2.0f * massA * speedA) / allMass;

    return std::make_pair( va, vb );
}




inline std::pair< VectorT< real_t >,  VectorT< real_t > >
speedElasticCollision(
    real_t massA,  const VectorT< real_t >&  speedA,
    real_t massB,  const VectorT< real_t >&  speedB
) {
    const auto vx = speedElasticCollision( massA, speedA.x, massB, speedB.x );
    const auto vy = speedElasticCollision( massA, speedA.y, massB, speedB.y );
    const auto vz = speedElasticCollision( massA, speedA.z, massB, speedB.z );

    return std::make_pair(
        VectorT< real_t >( vx.first,  vy.first,  vz.first  ),
        VectorT< real_t >( vx.second, vy.second, vz.second )
    );
}




inline real_t speedInelasticCollision(
    real_t massA,  real_t speedA,
    real_t massB,  real_t speedB
) {
    const real_t allMass = massA + massB;
    const real_t mvab = massA * speedA + massB * speedB;
    const real_t v = mvab / allMass;

    return v;
}




inline VectorT< real_t >  speedInelasticCollision(
    real_t massA,  const VectorT< real_t >&  speedA,
    real_t massB,  const VectorT< real_t >&  speedB
) {
    const auto vx = speedInelasticCollision( massA, speedA.x, massB, speedB.x );
    const auto vy = speedInelasticCollision( massA, speedA.y, massB, speedB.y );
    const auto vz = speedInelasticCollision( massA, speedA.z, massB, speedB.z );

    return VectorT< real_t >( vx, vy, vz );
}




inline std::pair< real_t, real_t >  speedCollision(
    real_t massA,  real_t speedA,
    real_t massB,  real_t speedB,
    real_t COR
) {
    const real_t allMass = massA + massB;
    const real_t mvab = massA * speedA + massB * speedB;
    const real_t va = (mvab + massB * COR * (speedB - speedA)) / allMass;
    const real_t vb = (mvab + massA * COR * (speedA - speedB)) / allMass;

    return std::make_pair( va, vb );
}




inline std::pair< VectorT< real_t >,  VectorT< real_t > >
speedCollision(
    real_t massA,  const VectorT< real_t >&  speedA,
    real_t massB,  const VectorT< real_t >&  speedB,
    real_t COR
) {
    const auto vx = speedCollision( massA, speedA.x, massB, speedB.x, COR );
    const auto vy = speedCollision( massA, speedA.y, massB, speedB.y, COR );
    const auto vz = speedCollision( massA, speedA.z, massB, speedB.z, COR );

    return std::make_pair(
        VectorT< real_t >( vx.first,  vy.first,  vz.first  ),
        VectorT< real_t >( vx.second, vy.second, vz.second )
    );
}




inline real_t deltaTemperature(
    real_t q,  real_t mass,  real_t heatCapacity
) {
    return q / (heatCapacity * mass);
}




inline real_t luminosity(
    real_t radius,  real_t temperature
) {
    return
        4.0f * constant::pi * radius * radius *
        constant::physics::stefanBoltzmann *
        temperature * temperature * temperature * temperature;
}




inline real_t effectiveTemperature(
    real_t luminosity,  real_t distance,  real_t albedo
) {
    const real_t r = luminosity * (1.0f - albedo) / (
        16.0f * constant::pi *
        constant::physics::stefanBoltzmann *
        distance * distance
    );

    return std::pow( r,  1.0f / 4.0f );
}


        } // physics
    } // compute
} // typelib
