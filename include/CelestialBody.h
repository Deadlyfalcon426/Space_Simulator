#include <iostream>
#include <vector>
#include <string>
#include "PhysicsVector3.h"
#include <cmath>
#pragma once
class CelestialBody {
    private:
        std::string name;
        double mass;
        PhysicsVector3 acceleration;
        PhysicsVector3 velocity;
        PhysicsVector3 position;
        std::string units_mass;
    public:
        const double G = 6.67430*std::pow(10, -11);
        CelestialBody(std::string name, double mass, double x, double y, double z);
        CelestialBody(std::string name, double mass);
        
        std::string get_name() const;
        PhysicsVector3 get_velocity() const;
        PhysicsVector3 get_acceleration() const;
        PhysicsVector3 get_position() const;
        double get_mass() const;
        void set_mass(double mass);
        void set_units_mass(std::string new_units);
        void set_velocity(double x, double y, double z, std::string units_velocity);
        void set_velocity(double x, double y, double z);
        void set_velocity(PhysicsVector3 new_velocity);
        void set_acceleration(double x, double y, double z, std::string units_acceleration);
        void set_acceleration(double x, double y, double z);
        void set_acceleration(PhysicsVector3 new_acceleration);
        void update_position(double x, double y, double z, std::string units_position);
        void update_position(double x, double y, double z);
        void update_position(PhysicsVector3 speed, double time);
        void update_position(PhysicsVector3 new_position);

        PhysicsVector3 get_gravitational_force(const CelestialBody& other) const;
        PhysicsVector3 get_gravitational_force(const CelestialBody& other, const PhysicsVector3& new_position, const PhysicsVector3& new_position_other) const;

        friend std::ostream& operator<<(std:: ostream& os, const CelestialBody& s);
};