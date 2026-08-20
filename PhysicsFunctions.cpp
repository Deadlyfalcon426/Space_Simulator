#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "Vector3.h"
#include <cmath>
#include "PhysicsFunctions.h"
#include <stdexcept>

struct pair {
    int uno;
    int dos;
    pair(int uno, int dos) : uno(uno), dos(dos) {}
};

void all_g_acceleration(std::vector<CelestialBody>& gravitational_influences){
    int n = gravitational_influences.size();
    std::vector<Vector3> net_forces = std::vector(n, Vector3(0, 0, 0, "N"));
    std::vector<pair> pairs = std::vector(((n*n)-n)/2, pair(0,0));
    int counter = 0;
    for(int i = 0; i<n-1;i++){
        for(int j = i+1; j<n;j++){
            pairs[counter].uno = i;
            pairs[counter].dos = j;
            counter++;
        }
    }
    for(pair& pair_ : pairs){
        CelestialBody& body1 = gravitational_influences[pair_.uno];
        CelestialBody& body2 = gravitational_influences[pair_.dos];
        Vector3 new_g_force = body1.get_gravitational_force(body2);
        Vector3 opp_new_g_force = new_g_force.scale(-1);
        net_forces[pair_.uno] = net_forces[pair_.uno].sum(new_g_force);
        net_forces[pair_.dos] = net_forces[pair_.dos].sum(opp_new_g_force);
    }
    //now that we have found all net forces we can apply the forces to find acceleration
    for(int body_index = 0; body_index<n;body_index++){
        applyForce(gravitational_influences[body_index], net_forces[body_index]);
    }
}


void applyForce(CelestialBody& body_of_interest, Vector3 force){
    if(force.getUnits()!="N"){
        std::cout<<"The vector given is not of the appropriate unit, \"N\"";
    } else{
        double mass = body_of_interest.get_mass();
        force = force.scale(1/mass);
        body_of_interest.set_acceleration(force);
    }
}

void updateVelocity(CelestialBody& target, double dt){
    Vector3 acceleration    = target.get_acceleration();
    Vector3 velocity        = target.get_velocity();

    //basically just kinematics, but with 3d vectors!
    acceleration = acceleration.scale(dt);
    acceleration.setUnits("m/s");
    target.set_velocity(velocity.sum(acceleration));

}

//so in the below function, this is where the culmination of all the different physics functions will be
//however im kind of waiting on making it as I do think this will require the Euler/RK4 part?
void euler_step(std::vector<CelestialBody>& heavenly_vector, double dt){
    //the idea is to first calculate new acceleration
    //then calculate position using initial velocity
    //then we find velocity using the new acceleration
    //kind of like a step up thing ig
    //so first forces-> acceleration, now we have a function that does both
    all_g_acceleration(heavenly_vector);
    //next position update, we dont have a cool method for this besides the function that should probably not be overloaded in this manner
    for(CelestialBody& body : heavenly_vector){
        body.update_position(body.get_velocity(), dt);
    }
    //lastly we have the velocity update using the latest acceleration calculation
    for(CelestialBody& body : heavenly_vector){
        updateVelocity(body, dt);
    }


}
void runge_kutta_4_step(std::vector<CelestialBody>& heavenly_vector, double dt){

}

void sim(std::vector<CelestialBody>& heavenly_vector, double time_passed, double base_step, std::string choice){
    int steps = time_passed/base_step;
    if(choice=="RK4"){
        for(double i = 0; i<steps;i++){
            runge_kutta_4_step(heavenly_vector, base_step);
        }
    } else if(choice=="Euler"){
        for(double i = 0; i<steps;i++){
            euler_step(heavenly_vector, base_step);
        }
    } else{
        std::cout<<"Invalid choice of numerical analysis. \nChoose either RK4 or Euler.\n";
    }
}
void print_heavenly_vector(std::vector<CelestialBody>& heavenly_vector){
    std::cout<<"All bodies in current system: \n"<<
    "----------------------------------------\n";
    for(CelestialBody& body : heavenly_vector){
        std::cout<<body<<"\n";
    }
    std::cout<<"\n"<<
    "----------------------------------------\n";
}