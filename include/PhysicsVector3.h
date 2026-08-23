#pragma once
#include <iostream>
#include <string>

class PhysicsVector3{
    private:
        double x;
        double y;
        double z;
        std::string unit;
    public:
        PhysicsVector3(double x, double y, double z, std::string unit);
        PhysicsVector3(const PhysicsVector3& other);
        double getX() const;
        double getY() const;
        double getZ() const;
        double getMagnitude() const;
        std::string getUnits() const;
        void adjust(double x, double y, double z);
        void setUnits(std::string unit);
        void adjust(double x, char choice);
        //we've gone TOO long without this one below
        void adjust(PhysicsVector3& new_guy);
        PhysicsVector3 scale(double scale_factor) const;
        //pythagorean with 3 
        double distanceTo(const PhysicsVector3& other) const;
        PhysicsVector3 difference(const PhysicsVector3& other) const;
        PhysicsVector3 sum(const PhysicsVector3& other) const;
        PhysicsVector3 operator+(const PhysicsVector3& other) const;
        PhysicsVector3 operator-(const PhysicsVector3& other) const;
        PhysicsVector3 operator*(double scalar) const;
        friend PhysicsVector3 operator*(double scalar, const PhysicsVector3& v);
        PhysicsVector3 operator/(double scalar) const;
        friend std::ostream& operator<<(std::ostream& os, const PhysicsVector3& s);
};