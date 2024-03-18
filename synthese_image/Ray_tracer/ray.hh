#pragma once
#include "vector3.hh"

class Ray
{
public:
    Ray() = default;
    Ray(const Vector3::Point3& origine, const Vector3::Vector3& direction):
    dir{direction}, orig{origine} {}


    Vector3::Point3 origine() const { return orig; }
    Vector3::Vector3 direction() const { return dir; }

    void setorigine(Vector3::Vector3 origA){ orig = origA; }
    void setdirection(Vector3::Vector3 dirA) { dir = dirA; }

    Vector3::Point3 at(double t) const{
        return t * dir + orig;
    }
private:
    Vector3::Point3 orig;
    Vector3::Vector3 dir;
};