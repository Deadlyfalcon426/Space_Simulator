#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "Vector3.h"
#include <cmath>
#include "PhysicsFunctions.h"
#include <stdexcept>
Vector3 get_all_gravitational_force_for_a_body(CelestialBody& body_of_interest, std::vector<CelestialBody>& gravitational_influences){
    Vector3 net_force = Vector3(0, 0, 0, "N");

    for(CelestialBody& body : gravitational_influences){
        if(&body==&body_of_interest){ continue;}
        Vector3 temp_force = body_of_interest.get_gravitational_force(body, "N");
        net_force = net_force.sum(temp_force);
    }
    return net_force;
}


void applyForce(CelestialBody& body_of_interest, Vector3 force){
    if(force.getUnits()!="N"){
        std::cout<<"The vector given is not of the appropriate unit, \"N\"";
    } else{
        double mass = body_of_interest.get_mass();
        force.scale(1/mass);
        body_of_interest.set_acceleration(force);
    }
}

void updateKinematics(CelestialBody& target, double dt){
    Vector3 acceleration    = target.get_acceleration();
    Vector3 velocity        = target.get_velocity();

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
    //use old velocity to calculate position?
    //then like from there calculate velocity of next? smth like that isnt it
    for(CelestialBody& body : heavenly_vector){
        applyForce(body, get_all_gravitational_force_for_a_body(body, heavenly_vector));
        updateKinematics(body, dt);
    }
    //so above should set up the velocity from the forces
    //now below is like Δv = Δd/t -> Δd = Δv*t
    for(CelestialBody& body : heavenly_vector){
        body.update_position(body.get_velocity(), dt);
    }


}
void runge_kutta_4_step(std::vector<CelestialBody>& heavenly_vector, double dt){

}

void sim(std::vector<CelestialBody>& heavenly_vector, double time_passed, double base_step, std::string choice){
    int steps = time_passed/base_step;
    if(choice=="RK4"){
        for(int i = 0; i<steps;i++){
            runge_kutta_4_step(heavenly_vector, base_step);
        }
    } else if(choice=="Euler"){
        for(int i = 0; i<steps;i++){
            euler_step(heavenly_vector, base_step);
        }
    } else{
        std::cout<<"Invalid choice of numerical analysis. \nChoose either RK4 or Euler.\n";
    }
}