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
std::string Vector3::getUnits() const{
    return unit;
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
                    this->y = y;
                    break;
                case 'z':
                    this->z=z;
                    break;
                default:
                    std::cout<<"Error: Invalid dimension. Appropriate inputs are x, y, or z";
            }
        }
double Vector3::distanceTo(const Vector3& other) const{
    double difference_x = this->x - other.getX();
    double difference_y = this->y - other.getY();
    double difference_z = this->z - other.getZ();
    return std::sqrt( difference_x*difference_x + difference_y*difference_y + difference_z*difference_z);
}

std::ostream& operator<<(std::ostream& os, const Vector3& s){
            return os 
                << "(" 
                << s.x << ", " 
                << s.y << ", " 
                << s.z << ") Units: " 
                << s.unit;
    }
