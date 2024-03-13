#pragma once
#include "vector3.hh"
#include <iostream>
#include <vector>

class TextureMaterial {
public:
    virtual Vector3::Vector3 getParametersAtPosition(Vector3::Point3 point) const = 0;
    virtual ~TextureMaterial() {}
};

class UniformTexture : public TextureMaterial {
public:
    UniformTexture() = default;
    UniformTexture(double kd, double ks, double ka) : kd{kd}, ks{ks}, ka{ka}{}
    Vector3::Vector3 getParametersAtPosition(Vector3::Point3 point) const override {
        // Pour une texture uniforme, les paramètres sont les mêmes en tout point
        return Vector3::Vector3{kd, ks, ka};
    }

private:
    double kd = 1; // Coefficient de diffusion
    double ks = 1; // Coefficient de spécularité
    double ka = 1; // Coefficient d'absorption
};



