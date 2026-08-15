#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "CelestialBody.h"

CelestialBody::CelestialBody(std::string name, long long mass, double x, double y, double z, std::string units)
: name(name), mass(mass), position(Vector3(x,y,z,units))
{
}
CelestialBody::CelestialBody(std::string name, long long mass, std::string units)
: name(name), mass(mass), position(Vector3(0,0,0,units))
{
}
CelestialBody::CelestialBody(std::string name, long long mass, std::string units, double speed)
: name(name), mass(mass), position(Vector3(0,0,0,units))
{
    set_tangential_speed(speed);
}
CelestialBody::CelestialBody(std::string name, long long mass, double x, double y, double z, std::string units, double speed)
: name(name), mass(mass), position(Vector3(x,y,z,units))
{
    set_tangential_speed(speed);
}
void CelestialBody::set_tangential_speed(double speed){
    tangential_speed=speed;
}
void CelestialBody::update_position(double x, double y, double z){
        position.adjust(x,y,z);
    }

std::ostream& operator<<(std:: ostream& os, const CelestialBody& s){
    return os << 
        "Name: " << s.name << "\n" <<
        "Mass: " << s.mass << "\n" <<
        "Tangential Speed: " << s.tangential_speed << "\n" <<
        "Position: " << s.position << "\n"
    ;
}
