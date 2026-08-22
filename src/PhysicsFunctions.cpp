#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "Vector3.h"
#include <cmath>
#include "PhysicsFunctions.h"
#include "rk4_variables.h"
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
        gravitational_influences[body_index].set_acceleration(applyForce(gravitational_influences[body_index], net_forces[body_index]));
    }
}


void update_runge_kutta_acceleration(std::vector<CelestialBody>& gravitational_influences, std::vector<RK4::rk4_variables>& variables){
    int n = variables.size();
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
        Vector3 new_g_force = body1.get_gravitational_force(body2, variables[pair_.uno].current_r, variables[pair_.dos].current_r);
        Vector3 opp_new_g_force = new_g_force.scale(-1);
        net_forces[pair_.uno] = net_forces[pair_.uno].sum(new_g_force);
        net_forces[pair_.dos] = net_forces[pair_.dos].sum(opp_new_g_force);
    }
    counter=0;
    for(RK4::rk4_variables& current : variables){
        current.current_a = applyForce(gravitational_influences[counter], net_forces[counter]);
        counter++;
    }
}

Vector3 applyForce(CelestialBody& body_of_interest, Vector3 force){
    if(force.getUnits()!="N"){
        std::cout<<"The vector given is not of the appropriate unit, \"N\"";
        throw std::runtime_error("");
        return Vector3(0,0,0,"I should not exist");
    } else{
        double mass = body_of_interest.get_mass();
        force = force.scale(1/mass);
        force.setUnits("m/s^2");
        Vector3 acceleration = force;
        return acceleration;
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
    /*
    a short(quite long) overview of RK4, since its new and i gotta research and stuff:
    very reminiscent of the trapezoidal rule (due to the coefficients) tbh,
    can't wait to figure out how simpson's rule might translate to numerical analysis lol
    also these arent like the ones on a differential equations reference sheet, i did a bit of translating
    there are two differential equations to solve
    dr/dt = v & dv/dt = a(r)
    the main rk4 equation is: new y = old y + (k1 + 2k2 + 2k3 + k4) / 6
    so which do we solve first, position or velocity?
    they are both kinda based on each other tbh
    well we kind of should do acceleration->velocity->position because before we choose positon we should have our velocity lowk?
    so then:
    k1 = velocity 1 = dt * initial acceleration
    k2 = velocity 2 = dt * acceleration at midpoint, based on (initial velocity + velocity 1)/2
    k3 = velocity 3 = dt * acceleration at midpoint, based on (initial velocity + velocity 2)/2
    k4 = velocity 4 = dt * acceleration at velocity 3

    k1 = position 1 = dt * initial velocity
    k2 = position 2 = dt * velocity at midpoint, based on (initial position + position 1)/2
    k3 = position 3 = dt * velocity at midpoint, based on (initial position + position 2)/2
    k4 = position 4 = dt * velocity at position 3
    so this should be accurate as ive had to rewrite it like 2-4 times now.
    clearly, you cannot have "acceleration at velocity 3" 
    because velocity alone is not enough to calculate the acceleration, we would rather have radius/distance
    so how does our model actually handle things?
    r will be like distance/radius*/
    /*
    STAGE 1:
        first off, it calculates initial acceleration, easiest part. we'll call it a_0
        now, we find k1_r and k1_v, which to do first?
        we want to utilize all initial changer thingies
        but lowk different parameters so nothing bad happens if dif order
        k1_r = dt * v_0
        k1_v = dt * a_0 (nothing is breaking each other yet! no overlap!)
        essentially just an euler step? a foot into the dark?
    */
    //ok stop freaking out we only need to iterate over one vector goddamn it. 
    //all the weird inter-body stuff is handled by the beautiful all_g_acceleration(), 
    //so i can just focus on setting up kinematics and making sure to call the acceleration thingy
    std::vector<RK4::rk4_variables> rk4;
    for(CelestialBody& body : heavenly_vector){
        //add in the initial r_0, v_0, a_0.
        rk4.push_back(RK4::rk4_variables(body.get_position(), body.get_velocity()));
    }
    //in between we gotta do accelerations
    update_runge_kutta_acceleration(heavenly_vector, rk4);
    for(RK4::rk4_variables& current : rk4){
        //next we just multiply in the dt
        current.k1_r = current.v_0.scale(dt);
        current.k1_r.setUnits("m");
        current.k1_v = current.current_a.scale(dt);
        current.k1_v.setUnits("m/s");
    }
    /*
    Stage 2:
        next, we start getting weird
        looking back, it feels kind of safe to call this the euler half-step
        r_2 = r_0 + k1_r/2            <- find the radius midpoint
        v_2 = v_0 + k1_v/2            <- find the velocity midpoint
        a_mid1 = acceleration at r_2    <- find the acceleration at the radius midpoint
        k2_r = dt * v_2                 <- find the radius at the velocity midpoint
        k2_v = dt * a_mid1              <- find the velocity at the radius midpoint
        this is kinda sexy because it like intertwines the two... damn i didnt think it would be half as cool as this
    */
    for(RK4::rk4_variables& current : rk4){
        //that should find the radius midpoint
        current.current_r = (current.k1_r.scale(0.5)).sum(current.r_0);
        //that should find the velocity midpoint
        current.current_v = (current.k1_v.scale(0.5)).sum(current.v_0);
        //yeah lowk dead end here bruh how we gonna set up g acceleration with the current function???
        //ima sleep then handle this BS
        //🤣✌️
        //well due to great project design (not) it didnt take that long to set up a new system, one im kinda happy with
    }
    //find the acceleration at the radius midpoint
    update_runge_kutta_acceleration(heavenly_vector, rk4);
    for(RK4::rk4_variables& current : rk4){
        //find the radius at the velocity midpoint
        current.k2_r = current.current_v.scale(dt);
        current.k2_r.setUnits("m");
        //find the velocity at the radius midpoint
        current.k2_v = current.current_a.scale(dt);
        current.k2_v.setUnits("m/s");
    }
    /*
        Stage 3:
        so same part but reversed technically, we sucessfully intertwine the two differential equations
        looking back i think an appropriate name for this is the linking step, maybe the reverse euler step
        r_3 = r_0 + k2_r/2    <- find midpoint of the velocity-based new position and the initial position
        v_3 = v_0 + k2_v/2    <- find midpoint of the position-based new velocity and the initial velocity
        a_mid2 = acceleration at r_3    <- find the acceleration at the velocity-based positional midpoint
        k3_r = dt * v_3     <- return the position given the velocity at the position-based velocity midpoint! 
        this assumes midpoint speed throughout.
        k3_v = dt * a_mid2      <- return the velocity given the acceleration-that is based on the velocity-based positional midpoint! 
        this assumes midpoint acceleration throughout.
    */
    for(RK4::rk4_variables& current : rk4){
        //find midpoint of the velocity-based new position and the initial position
        current.current_r = current.r_0.sum(current.k2_r.scale(0.5));
        //find midpoint of the position-based new velocity and the initial velocity
        current.current_v = current.v_0.sum(current.k2_v.scale(0.5));
    }
    //find the acceleration at the velocity-based positional midpoint
    update_runge_kutta_acceleration(heavenly_vector, rk4);
    for(RK4::rk4_variables& current : rk4){
        //return the position given the velocity at the position-based velocity midpoint! 
        //this assumes midpoint speed throughout.
        current.k3_r = current.current_v.scale(dt);
        current.k3_r.setUnits("m");
        //return the velocity given the acceleration-that is based on the velocity-based positional midpoint! 
        //this assumes midpoint acceleration throughout.
        current.k3_v = current.current_a.scale(dt);
        current.k3_v.setUnits("m/s");
    }
    /*
        Stage 4: 
        idk abt this step, it feels like its there to balance out the effect of the first stage
        i feel that way because first stage -> initial velocities, stage 4 -> last calculated velocity
        sort of like averaging out the weirdness runge-kutta made with the initial euler assumption step
        r_4 = k3_r + r_0    <- idk yo ✌️
        v_4 = k3_v + v_0    <-
        a_end = acceleration at r_4 <-adds acceleration, but notably at the end and not the midpoint.
        k4_r = dt * v_4
        k4_v = dt * a_end
        this step sort of confuses me but i think i have enough understanding
    */
   for(RK4::rk4_variables& current : rk4){
        //im lowk baffled idk
        current.current_r = current.r_0.sum(current.k3_r);
        //
        current.current_v = current.v_0.sum(current.k3_v);
    }
    //acceleration at r_4 <-adds acceleration, but notably at the end and not the midpoint.
    update_runge_kutta_acceleration(heavenly_vector, rk4);
    for(RK4::rk4_variables& current : rk4){
        //k4_r = dt * v_4
        current.k4_r = current.current_v.scale(dt);
        current.k4_r.setUnits("m");
        //k4_v = dt * a_end
        current.k4_v = current.current_a.scale(dt);
        current.k4_v.setUnits("m/s");
    }
    /*
        Stage 5, Final:
        use initial runge-kutta equation:
        new y = old y + (k1 + 2k2 + 2k3 + k4) / 6
        notice that the midpoint parts have a multiplier and the full parts dont. 
        this is to weight the midpoint ones higher, specifically they are each twice as important as just the k1 or k4
    */
    int counter = 0;
    for(CelestialBody& body : heavenly_vector){
        RK4::rk4_variables& current = rk4[counter];
        body.update_position(current.r_0 + ( ( current.k1_r + (2 * current.k2_r) + (2 * current.k3_r) + current.k4_r) / 6 ) );
        body.set_velocity(current.v_0 + ( ( current.k1_v + (2 * current.k2_v) + (2 * current.k3_v) + current.k4_v) / 6 ) );
        //display number, not actually used but it would be weird not to have one and just have 0,0,0
        //this might have room for improvement, so keep an eye on it
        body.set_acceleration(current.current_a);
        counter++;
    }

}

void sim(std::vector<CelestialBody>& heavenly_vector, double time_passed, double base_step, std::string choice){
    double steps = time_passed/base_step;
    if(choice=="RK4"){
        for(double i = 0; i<steps;i++){
            runge_kutta_4_step(heavenly_vector, base_step);
            //debug
            //std::cout<<heavenly_vector[0]<<"\n"<<heavenly_vector[1];
        }
    } else if(choice=="Euler"){
        for(double i = 0; i<steps;i++){
            euler_step(heavenly_vector, base_step);
            //debug
            //std::cout<<heavenly_vector[0]<<"\n"<<heavenly_vector[1];
        }
    } else{
        std::cout<<"Invalid choice of numerical analysis. \nChoose either RK4 or Euler.\n";
        std::cin>>choice;
        sim(heavenly_vector, time_passed, base_step, choice);
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