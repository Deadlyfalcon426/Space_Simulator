#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "Vector3.h"
#include <cmath>
#include "PhysicsFunctions.h"
#include <stdexcept>
Vector3 get_all_gravitational_force_for_a_body(CelestialBody& body_of_interest, std::vector<CelestialBody>& gravitational_influences){
    Vector3 net_force = Vector3(0, 0, 0, "N", "Force");

    for(CelestialBody& body : gravitational_influences){
        if(&body==&body_of_interest){ continue;}
        Vector3 temp_force = body_of_interest.get_gravitational_force(body, "N");
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

void updateKinematics(CelestialBody& target, double dt){
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
void euler_step(std::vector<CelestialBody>& heavenly_vector, double dt){
    
}
void runge_kutta_4_step(std::vector<CelestialBody>& heavenly_vector, double dt){

}