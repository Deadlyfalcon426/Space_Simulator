#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "CelestialBody.h"

CelestialBody::CelestialBody(std::string name, double mass, double x, double y, double z, std::string units_position)
: name(name), mass(mass), position(Vector3(x,y,z,units_position, "Position")), acceleration(0,0,0, "", "Acceleration"), velocity(0,0,0, "", "Velocity")
{
}
CelestialBody::CelestialBody(std::string name, double mass, std::string units)
: name(name), mass(mass), position(Vector3(0,0,0,units, "Position")), acceleration(0,0,0, "m/s^2", "Acceleration"), velocity(0,0,0, "m/s", "Velocity")
{
}

std::string CelestialBody::get_name() const{
    return name;
}
Vector3 CelestialBody::get_velocity() const{
    return velocity;
}
Vector3 CelestialBody::get_acceleration() const{
    return acceleration;
}
Vector3 CelestialBody::get_position() const{
    return position;
}
double CelestialBody::get_mass() const{
    return mass;
}

void CelestialBody::set_mass(double mass){
    this->mass=mass;
}
void CelestialBody::set_units_mass(std::string units_mass){
    this->units_mass=units_mass;
}
void CelestialBody::set_velocity(double x, double y, double z, std::string units_velocity){
    velocity.adjust(x,y,z);
    velocity.setUnits(units_velocity);
}
void CelestialBody::set_velocity(double x, double y, double z){
    velocity.adjust(x,y,z);
}
void CelestialBody::set_velocity(Vector3 new_velocity){
    velocity.adjust(new_velocity.getX(),new_velocity.getY(),new_velocity.getZ());
}
void CelestialBody::set_acceleration(double x, double y, double z, std::string units_acceleration){
    acceleration.adjust(x,y,z);
    acceleration.setUnits(units_acceleration);
}
void CelestialBody::set_acceleration(double x, double y, double z){
    acceleration.adjust(x,y,z);
}
void CelestialBody::set_acceleration(Vector3 new_acceleration){
    acceleration.adjust(new_acceleration.getX(),new_acceleration.getY(),new_acceleration.getZ());
}
void CelestialBody::update_position(double x, double y, double z, std::string units_position){
    position.adjust(x,y,z);
    position.setUnits(units_position);
}
void CelestialBody::update_position(double x, double y, double z){
    position.adjust(x,y,z);
}

Vector3 CelestialBody::get_gravitational_force(const CelestialBody& other, std::string units_force) const{
    double distance = position.distanceTo(other.get_position());
    double g_force_combine = G * this->mass * other.get_mass() / distance / distance;
    Vector3 diff = position.difference(other.get_position());
    double new_x = diff.getX() / distance * g_force_combine;
    double new_y = diff.getY() / distance * g_force_combine;
    double new_z = diff.getZ() / distance * g_force_combine;
    Vector3 new_g_force = Vector3(new_x,new_y,new_z,units_force, "Force");
    return new_g_force;
}



std::ostream& operator<<(std:: ostream& os, const CelestialBody& s){
    return os << 
        "Name: " << s.name << "\n" <<
        "Mass: " << s.mass << "\n" <<
        "Velocity: " << s.velocity << "\n" <<
        "Acceleration: " << s.acceleration << "\n" <<
        "Position: " << s.position << "\n\n"
    ;
}
