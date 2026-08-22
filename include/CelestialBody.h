#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include <cmath>
#pragma once
class CelestialBody {
    private:
        std::string name;
        double mass;
        Vector3 acceleration;
        Vector3 velocity;
        Vector3 position;
        std::string units_mass;
    public:
        const double G = 6.67430*std::pow(10, -11);
        CelestialBody(std::string name, double mass, double x, double y, double z);
        CelestialBody(std::string name, double mass);
        
        std::string get_name() const;
        Vector3 get_velocity() const;
        Vector3 get_acceleration() const;
        Vector3 get_position() const;
        double get_mass() const;
        void set_mass(double mass);
        void set_units_mass(std::string new_units);
        void set_velocity(double x, double y, double z, std::string units_velocity);
        void set_velocity(double x, double y, double z);
        void set_velocity(Vector3 new_velocity);
        void set_acceleration(double x, double y, double z, std::string units_acceleration);
        void set_acceleration(double x, double y, double z);
        void set_acceleration(Vector3 new_acceleration);
        void update_position(double x, double y, double z, std::string units_position);
        void update_position(double x, double y, double z);
        void update_position(Vector3 speed, double time);
        void update_position(Vector3 new_position);

        Vector3 get_gravitational_force(const CelestialBody& other) const;
        Vector3 get_gravitational_force(const CelestialBody& other, const Vector3& new_position, const Vector3& new_position_other) const;

        friend std::ostream& operator<<(std:: ostream& os, const CelestialBody& s);
};