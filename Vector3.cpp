#include <iostream>
#include <string>
#include "Vector3.h"
#include <cmath>
#include <stdexcept>

Vector3::Vector3(double x, double y, double z, std::string unit)
    : 
    x(x), 
    y(y), 
    z(z), 
    unit(unit)
{
}
Vector3::Vector3(const Vector3& other)
    : 
    x(other.getX()), 
    y(other.getY()), 
    z(other.getZ()), 
    unit(other.getUnits())
{
}
double Vector3::getX() const{
    return x;
}
double Vector3::getY() const{
    return y;
}
double Vector3::getZ() const{
    return z;
}
double Vector3::getMagnitude() const{
    return std::sqrt( this->x*this->x + this->y*this->y + this->z*this->z);
}
std::string Vector3::getUnits() const{
    return unit;
}
Vector3 Vector3::scale(double scale_factor) const{
    double new_x = x*scale_factor;
    double new_y = y*scale_factor;
    double new_z = z*scale_factor;
    return Vector3(new_x,new_y,new_z,unit);
}
void Vector3::adjust(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
void Vector3::adjust(Vector3& new_guy){
    adjust(new_guy.getX(), new_guy.getY(), new_guy.getZ());
}
void Vector3::setUnits(std::string unit){
    this->unit = unit;
}
void Vector3::adjust(double x, char choice){
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
double Vector3::distanceTo(const Vector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch: Defaulting to units passed in argument Vector3 object.";
    }
    double difference_x = this->x - other.getX();
    double difference_y = this->y - other.getY();
    double difference_z = this->z - other.getZ();
    return std::sqrt( difference_x*difference_x + difference_y*difference_y + difference_z*difference_z);
}
Vector3 Vector3::difference(const Vector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch for difference: Defaulting to units passed in argument Vector3 object.";
        throw std::runtime_error("");
    }
    return Vector3(this->x-other.getX(), this->y-other.getY(), this->z-other.getZ(), other.getUnits());
}
Vector3 Vector3::sum(const Vector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch: Defaulting to units passed in argument Vector3 object.";
        throw std::runtime_error("");
    }
    return Vector3(this->x+other.getX(), this->y+other.getY(), this->z+other.getZ(), other.getUnits());
}

Vector3 Vector3::operator+(const Vector3& other) const{
    return sum(other);
}
Vector3 Vector3::operator-(const Vector3& other) const{
    return difference(other);
}
Vector3 Vector3::operator*(double scalar) const{
    return scale(scalar);
}
Vector3 operator*(double scalar, const Vector3& v){
    return v.scale(scalar);
}
Vector3 Vector3::operator/(double scalar) const{
    return scale(1/scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector3& s){
            return os 
                << "(" 
                << s.x << ", " 
                << s.y << ", " 
                << s.z << ") Units: " 
                << s.unit;
    }
