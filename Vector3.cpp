#include <iostream>
#include <string>
#include "Vector3.h"
#include <cmath>

Vector3::Vector3(double x, double y, double z, std::string unit, std::string type)
        : x(x), y(y), z(z), unit(unit), type(type)
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
std::string Vector3::getType() const{
    return type;
}
void Vector3::scale(double scale_factor){
    this->x = x*scale_factor;
    this->y = y*scale_factor;
    this->z = z*scale_factor;
}
void Vector3::adjust(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
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
    if(other.getType()!=type){
        std::cout<<"Type mismatch: Defaulting to type passed in argument Vector3 object.";
    }
    double difference_x = this->x - other.getX();
    double difference_y = this->y - other.getY();
    double difference_z = this->z - other.getZ();
    return std::sqrt( difference_x*difference_x + difference_y*difference_y + difference_z*difference_z);
}
Vector3 Vector3::difference(const Vector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch: Defaulting to units passed in argument Vector3 object.";
    }
    if(other.getType()!=type){
        std::cout<<"Type mismatch: Defaulting to type passed in argument Vector3 object.";
    }
    return Vector3(this->x-other.getX(), this->y-other.getY(), this->z-other.getZ(), other.getUnits(), other.getType());
}
Vector3 Vector3::sum(const Vector3& other) const{
    if(other.getUnits()!=unit){
        std::cout<<"Unit mismatch: Defaulting to units passed in argument Vector3 object.";
    }
    if(other.getType()!=type){
        std::cout<<"Type mismatch: Defaulting to type passed in argument Vector3 object.";
    }
    return Vector3(this->x+other.getX(), this->y+other.getY(), this->z+other.getZ(), other.getUnits(), other.getType());
}
std::ostream& operator<<(std::ostream& os, const Vector3& s){
            return os 
                << "(" 
                << s.x << ", " 
                << s.y << ", " 
                << s.z << ") Units: " 
                << s.unit;
    }
