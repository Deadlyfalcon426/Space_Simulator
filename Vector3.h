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
        Vector3(const Vector3& other);
        double getX() const;
        double getY() const;
        double getZ() const;
        double getMagnitude() const;
        std::string getUnits() const;
        void adjust(double x, double y, double z);
        void setUnits(std::string unit);
        void adjust(double x, char choice);
        //we've gone TOO long without this one below
        void adjust(Vector3& new_guy);
        Vector3 scale(double scale_factor) const;
        //pythagorean with 3 
        double distanceTo(const Vector3& other) const;
        Vector3 difference(const Vector3& other) const;
        Vector3 sum(const Vector3& other) const;
        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(double scalar) const;
        friend Vector3 operator*(double scalar, const Vector3& v);
        Vector3 operator/(double scalar) const;
        friend std::ostream& operator<<(std::ostream& os, const Vector3& s);
};