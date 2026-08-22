#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "CelestialBody.h"

CelestialBody::CelestialBody(std::string name, double mass, double x, double y, double z)
: 
name(name), 
mass(mass), 
position(Vector3(x,y,z,"m")), 
acceleration(0,0,0, "m/s^2"), 
velocity(0,0,0, "m/s"), 
units_mass("kg")
{
}
CelestialBody::CelestialBody(std::string name, double mass)
: 
name(name), 
mass(mass), 
position(Vector3(0,0,0,"m")), 
acceleration(0,0,0, "m/s^2"), 
velocity(0,0,0, "m/s"),
units_mass("kg")
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
    velocity.adjust(new_velocity);
}
void CelestialBody::set_acceleration(double x, double y, double z, std::string units_acceleration){
    acceleration.adjust(x,y,z);
    acceleration.setUnits(units_acceleration);
}
void CelestialBody::set_acceleration(double x, double y, double z){
    acceleration.adjust(x,y,z);
}
void CelestialBody::set_acceleration(Vector3 new_acceleration){
    acceleration.adjust(new_acceleration);
}
void CelestialBody::update_position(double x, double y, double z, std::string units_position){
    position.adjust(x,y,z);
    position.setUnits(units_position);
}
void CelestialBody::update_position(double x, double y, double z){
    position.adjust(x,y,z);
}
void CelestialBody::update_position(Vector3 speed, double time){
    Vector3 new_distance = Vector3(speed.getX()*time, speed.getY()*time, speed.getZ()*time, "m");
    position = position.sum(new_distance);
}

void CelestialBody::update_position(Vector3 new_position){
    position.adjust(new_position);
}

Vector3 CelestialBody::get_gravitational_force(const CelestialBody& other) const{
    return get_gravitational_force(other, position, other.get_position());
}


Vector3 CelestialBody::get_gravitational_force(const CelestialBody& other, const Vector3& new_position, const Vector3& new_position_other) const{
    double distance = new_position.distanceTo(new_position_other);
    double g_force_combine = G * this->mass * other.get_mass() / distance / distance;
    Vector3 diff = new_position_other.difference(new_position);
    double new_x = diff.getX() / distance * g_force_combine;
    double new_y = diff.getY() / distance * g_force_combine;
    double new_z = diff.getZ() / distance * g_force_combine;
    Vector3 new_g_force = Vector3(new_x,new_y,new_z,"N");
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
