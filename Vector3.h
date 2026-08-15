#pragma once
#include <iostream>
#include <string>

class Vector3{
    private:
        double x;
        double y;
        double z;
        std::string unit;

    public:
        Vector3(double x, double y, double z, std::string unit);

        void adjust(double x, double y, double z);

        void adjust(double x, char choice);
        
        friend std::ostream& operator<<(std::ostream& os, const Vector3& s);
};