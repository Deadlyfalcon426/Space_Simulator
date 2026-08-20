#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "Vector3.h"
#include <cmath>
#include "PhysicsFunctions.h"

signed main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Vector3 origin = Vector3(0,0,0,"m");
    std::vector<CelestialBody> CelestialBodies;
    CelestialBody sun = CelestialBody("Sun", 1.989*std::pow(10, 30));
    CelestialBodies.push_back(sun);
    CelestialBody earth = CelestialBody("Earth", 5.9722*std::pow(10, 24));
    earth.update_position(1.52087774*std::pow(10, 11),0,0);
    earth.set_velocity(0,0,2.9300*std::pow(10,4));
    CelestialBodies.push_back(earth);
    CelestialBody mars = CelestialBody("Mars", 6.417*std::pow(10, 23));
    mars.update_position(2.49*std::pow(10, 11),0,0);
    mars.set_velocity(0,0,2.19424229375*std::pow(10, 4));//used vis-viva!
    CelestialBodies.push_back(mars);
    std::cout<<CelestialBodies[0]<<"\n";
    std::cout<<CelestialBodies[1]<<"\n";
    std::cout<<CelestialBodies[2]<<"\n"<<"\n";

    sim(CelestialBodies, 3600*24*30, 60, "Euler");

    std::cout<<CelestialBodies[0]<<"\n";
    std::cout<<CelestialBodies[1]<<"\n";
    std::cout<<CelestialBodies[2]<<"\n";
    return 0;
}



