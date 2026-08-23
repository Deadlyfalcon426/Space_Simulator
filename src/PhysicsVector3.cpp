#include <iostream>
#include <string>
#include "PhysicsVector3.h"
#include <cmath>
#include <stdexcept>

PhysicsVector3::PhysicsVector3(double x, double y, double z, std::string unit)
    : 
    x(x), 
    y(y), 
    z(z), 
    unit(unit)
{
}
PhysicsVector3::PhysicsVector3(const PhysicsVector3& other)
    : 
    x(other.getX()), 
    y(other.getY()), 
    z(other.getZ()), 
    unit(other.getUnits())
{
}
double PhysicsVector3::getX() const{
    return x;
}
double PhysicsVector3::getY() const{
    return y;
}
double PhysicsVector3::getZ() const{
    return z;
}
double PhysicsVector3::getMagnitude() const{
    return std::sqrt( this->x*this->x + this->y*this->y + this->z*this->z);
}
std::string PhysicsVector3::getUnits() const{
    return unit;
}
PhysicsVector3 PhysicsVector3::scale(double scale_factor) const{
    double new_x = x*scale_factor;
    double new_y = y*scale_factor;
    double new_z = z*scale_factor;
    return PhysicsVector3(new_x,new_y,new_z,unit);
}
void PhysicsVector3::adjust(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
void PhysicsVector3::adjust(PhysicsVector3& new_guy){
    adjust(new_guy.getX(), new_guy.getY(), new_guy.getZ());
}
void PhysicsVector3::setUnits(std::string unit){
    this->unit = unit;
}
void PhysicsVector3::adjust(double x, char choice){
    switch(choice){
        case 'x':
            this->x = x;
            break;
        case 'y':
            this->y = x;
            break;
        case 'z':
            this->z = x;
            break;
        default:
            std::cout<<"Error: Invalid dimension. Appropriate inputs are x, y, or z";
    }
}
double PhysicsVector3::distanceTo(const PhysicsVector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch: Defaulting to units passed in argument PhysicsVector3 object.";
    }
    double difference_x = this->x - other.getX();
    double difference_y = this->y - other.getY();
    double difference_z = this->z - other.getZ();
    return std::sqrt( difference_x*difference_x + difference_y*difference_y + difference_z*difference_z);
}
PhysicsVector3 PhysicsVector3::difference(const PhysicsVector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch for difference: Defaulting to units passed in argument PhysicsVector3 object.";
        throw std::runtime_error("");
    }
    return PhysicsVector3(this->x-other.getX(), this->y-other.getY(), this->z-other.getZ(), other.getUnits());
}
PhysicsVector3 PhysicsVector3::sum(const PhysicsVector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch: Defaulting to units passed in argument PhysicsVector3 object.";
        throw std::runtime_error("");
    }
    return PhysicsVector3(this->x+other.getX(), this->y+other.getY(), this->z+other.getZ(), other.getUnits());
}

PhysicsVector3 PhysicsVector3::operator+(const PhysicsVector3& other) const{
    return sum(other);
}
PhysicsVector3 PhysicsVector3::operator-(const PhysicsVector3& other) const{
    return difference(other);
}
PhysicsVector3 PhysicsVector3::operator*(double scalar) const{
    return scale(scalar);
}
PhysicsVector3 operator*(double scalar, const PhysicsVector3& v){
    return v.scale(scalar);
}
PhysicsVector3 PhysicsVector3::operator/(double scalar) const{
    return scale(1/scalar);
}

std::ostream& operator<<(std::ostream& os, const PhysicsVector3& s){
            return os 
                << "(" 
                << s.x << ", " 
                << s.y << ", " 
                << s.z << ") Units: " 
                << s.unit;
    }
