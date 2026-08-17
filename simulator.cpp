#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "Vector3.h"
#include <cmath>

Vector3 get_all_gravitational_force_for_a_body(CelestialBody& body_of_interest, std::vector<CelestialBody>& gravitational_influences){
    Vector3 net_force = Vector3(0, 0, 0, "N", "Force");

    for(CelestialBody& body : gravitational_influences){
        if(&body==&body_of_interest){ continue;}
        Vector3 temp_force = body_of_interest.get_gravitational_force(body, net_force.getUnits());
        net_force = net_force.sum(temp_force);
    }
    return net_force;
}


void applyForce(CelestialBody& body_of_interest, Vector3 force){
    if(force.getType()!="Force"){
        std::cout<<"The vector given is not of the appropriate type, \"Force\"";
    } else{
        double mass = body_of_interest.get_mass();
        force.scale(1/mass);
        body_of_interest.set_acceleration(force);
    }
}

void updateKinematics(CelestialBody& target, long long dt){
    Vector3 acceleration    = target.get_acceleration();
    Vector3 velocity        = target.get_velocity();
    Vector3 position        = target.get_position();

    //basically just kinematics, but with 3d vectors!
    acceleration.scale(dt);//debug ok this runs
    acceleration.setUnits("m/s");
    target.set_velocity(velocity.sum(acceleration));

}
//here will go the position setup method, and probably the Euler/RK4? 
//i have to research and find out how exactly to draw the line

//so in the below function, this is where the culmination of all the different physics functions will be
//however im kind of waiting on making it as I do think this will require the Euler/RK4 part?
//Also note: im considering making a physics function file to store all of these, making it easy to see the main function
void step(std::vector<CelestialBody> heavenly_vector, long long dt){
    
}

signed main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Vector3 origin = Vector3(0,0,0,"m","Position");
    std::vector<CelestialBody> CelestialBodies;
    CelestialBody sun = CelestialBody("Sun", 1.989*std::pow(10, 30), "m");
    CelestialBodies.push_back(sun);
    CelestialBody earth = CelestialBody("Earth", 5.9722*std::pow(10, 24), "m");
    earth.update_position(10000,541,876373);
    CelestialBodies.push_back(earth);
    CelestialBody mars = CelestialBody("Mars", 9.9722*std::pow(10, 29), "m");
    mars.update_position(10000,50000,200);
    CelestialBodies.push_back(mars);
    std::cout<<CelestialBodies[0]<<"\n";
    std::cout<<CelestialBodies[1]<<"\n";
    std::cout<<CelestialBodies[2]<<"\n"<<"\n";

    applyForce(CelestialBodies[0], get_all_gravitational_force_for_a_body(CelestialBodies[0], CelestialBodies));
    updateKinematics(CelestialBodies[0], 300);

    applyForce(CelestialBodies[1], get_all_gravitational_force_for_a_body(CelestialBodies[1], CelestialBodies));
    updateKinematics(CelestialBodies[1], 300);

    applyForce(CelestialBodies[2], get_all_gravitational_force_for_a_body(CelestialBodies[2], CelestialBodies));
    updateKinematics(CelestialBodies[2], 300);

    std::cout<<CelestialBodies[0]<<"\n";
    std::cout<<CelestialBodies[1]<<"\n";
    std::cout<<CelestialBodies[2]<<"\n";
    return 0;
}



