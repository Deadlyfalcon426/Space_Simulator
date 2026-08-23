#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "PhysicsVector3.h"
#include <cmath>
#include "PhysicsFunctions.h"
#include <string>
#include <raylib.h>
signed main() {
    


    //initial set up
    PhysicsVector3 origin = PhysicsVector3(0,0,0,"m");
    std::vector<CelestialBody> CelestialBodies;
    std::vector<PhysicsVector3> initial_positions;
    //sun
    CelestialBody sun = CelestialBody("Sun", 1.989*std::pow(10, 30));
    CelestialBodies.push_back(sun);
    initial_positions.push_back(sun.get_position());

    //earth
    CelestialBody earth = CelestialBody("Earth", 5.9722*std::pow(10, 24));
    earth.update_position(1.52087774*std::pow(10, 11),0,0);
    earth.set_velocity(0,0,2.9300*std::pow(10,4));
    CelestialBodies.push_back(earth);
    initial_positions.push_back(earth.get_position());
    //mars
    CelestialBody mars = CelestialBody("Mars", 6.417*std::pow(10, 23));
    mars.update_position(2.49*std::pow(10, 11),0,0);
    mars.set_velocity(0,0,2.19424229375*std::pow(10, 4));//used vis-viva!
    CelestialBodies.push_back(mars);
    initial_positions.push_back(mars.get_position());

    print_heavenly_vector(CelestialBodies);
    //31556952 <- seconds in a year
    //2629746 <- seconds in a month
    //86400 <- seconds in a day
    double time ; std::cout<<"Time to sim? -> "; std::cin>>time;
    double step ; std::cout<<"Time per step? -> "; std::cin>>step;
    std::string choice ; std::cout<<"Euler or RK4 numerical analysis? -> "; std::cin>>choice;
    sim(CelestialBodies, time, step, choice);

    print_heavenly_vector(CelestialBodies);
    int counter = 0;
    for(CelestialBody& body : CelestialBodies){
        initial_positions[counter] = body.get_position().difference(initial_positions[counter]);
        std::cout<<"\n"<<initial_positions[counter];
        counter++;
    }
    return 0;
}



