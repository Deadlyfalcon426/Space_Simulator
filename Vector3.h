#pragma once
#include <iostream>
#include <string>

class Vector3{
    private:
        double x;
        double y;
        double z;
        std::string unit;
        std::string type;
    public:
        Vector3(double x, double y, double z, std::string unit, std::string type);

        double getX() const;
        double getY() const;
        double getZ() const;
        double getMagnitude() const;
        std::string getUnits() const;
        std::string getType() const;
        void adjust(double x, double y, double z);
        void setUnits(std::string unit);
        void adjust(double x, char choice);
        //pythagorean with 3 
        double distanceTo(const Vector3& other) const;
        Vector3 difference(const Vector3& other) const;
        Vector3 sum(const Vector3& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Vector3& s);
};