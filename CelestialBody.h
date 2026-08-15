#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#pragma once
class CelestialBody {
    private:
        std::string name;
        long long mass;
        double tangential_speed;
        Vector3 position;
    public:
        CelestialBody(std::string name, long long mass, double x, double y, double z, std::string units);
        CelestialBody(std::string name, long long mass, std::string units);
        CelestialBody(std::string name, long long mass, std::string units, double tangential_speed);
        CelestialBody(std::string name, long long mass, double x, double y, double z, std::string units, double speed);
        void set_tangential_speed(double speed);
        void update_position(double x, double y, double z);
        friend std::ostream& operator<<(std:: ostream& os, const CelestialBody& s);
};