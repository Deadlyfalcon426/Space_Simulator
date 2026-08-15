#include <iostream>
#include <string>
#include "Vector3.h"


Vector3::Vector3(double x, double y, double z, std::string unit)
        : x(x), y(y), z(z), unit(unit)
    {
    }

void Vector3::adjust(double x, double y, double z){
            this->x = x;
            this->y = y;
            this->z = z;
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
    
std::ostream& operator<<(std::ostream& os, const Vector3& s){
            return os 
                << "(" 
                << s.x << ", " 
                << s.y << ", " 
                << s.z << ") Units: " 
                << s.unit;
    }
