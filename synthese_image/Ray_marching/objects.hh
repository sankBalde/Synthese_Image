#pragma once

#include "vector3.hh"

class Objet {
public:
    virtual double sdf(const Vector3::Point3& pos) const = 0;
    virtual Vector3::Color getColor() const = 0;
    virtual double getRefelexion() const = 0;
    virtual ~Objet() = default;
};

class Sphere : public Objet {
public:
    Vector3::Point3 center;
    Vector3::Color color;
    double radius;
    double reflection;

    Sphere(const Vector3::Point3& c, const Vector3::Color& color, double r, double refl = 0.0) : center(c), color(color), radius(r), reflection(refl) {}

    double sdf(const Vector3::Point3& pos) const override {
        return (pos - center).normEuclidienne() - radius;
    }

    Vector3::Color getColor() const override {
        return color;
    }
    double getRefelexion() const override {
        return reflection;
    }
};

class Plan : public Objet {
public:
    Vector3::Vector3 normal;
    Vector3::Color color;
    double distance;
    double reflection;

    Plan(const Vector3::Vector3& n, const Vector3::Color& color, double d, double refl = 0.0) : normal(n), color(color), distance(d), reflection(refl) {}

    double sdf(const Vector3::Point3& pos) const override {
        return Vector3::dot(pos, normal) + distance;
    }

    Vector3::Color getColor() const override {
        return color;
    }
    double getRefelexion() const override {
        return reflection;
    }
};

class Cube : public Objet {
public:
    Vector3::Point3 center;
    Vector3::Color color;
    Vector3::Vector3 size;
    double reflection;

    Cube(const Vector3::Point3& c, const Vector3::Vector3& s, const Vector3::Color& color, double refl = 0.0) : center(c), size(s), color(color), reflection(refl) {}

    double sdf(const Vector3::Point3& pos) const override {
        Vector3::Vector3 d = Vector3::Vector3(std::abs(pos.x - center.x), std::abs(pos.y - center.y), std::abs(pos.z - center.z)) - size;
        return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0) + Vector3::Vector3(std::max(d.x, 0.0), std::max(d.y, 0.0), std::max(d.z, 0.0)).normEuclidienne();
    }

    Vector3::Color getColor() const override {
        return color;
    }
    double getRefelexion() const override {
        return reflection;
    }
};

float intersectSDF(double distA, double distB) {
    return std::max(distA, distB);
}

float unionSDF(double distA, double distB) {
    return std::min(distA, distB);
}

float differenceSDF(double distA, double distB) {
    return std::max(distA, -distB);

}

class Nice_cube : public Objet {
public:
    Vector3::Point3 center;
    Vector3::Color color;
    Vector3::Vector3 size;
    double reflection;
    double radius;

    Nice_cube(const Vector3::Point3& c, const Vector3::Vector3& s, const Vector3::Color& color, double radius, double refl = 0.0) : center(c), size(s), color(color), reflection(refl), radius(radius) {}

    double sdf_cube(const Vector3::Point3& pos) const  {
        Vector3::Vector3 d = Vector3::Vector3(std::abs(pos.x - center.x), std::abs(pos.y - center.y), std::abs(pos.z - center.z)) - size;
        return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0) + Vector3::Vector3(std::max(d.x, 0.0), std::max(d.y, 0.0), std::max(d.z, 0.0)).normEuclidienne();
    }
    double sdf_sphere(const Vector3::Point3& pos) const  {
        return (pos - center).normEuclidienne() - radius;
    }
    double sdf(const Vector3::Point3& pos) const override {
        double sdf_cube_var = sdf_cube(pos);
        double sdf_sphere_var = sdf_sphere(pos);
        return differenceSDF(sdf_cube_var, sdf_sphere_var);
    }

    Vector3::Color getColor() const override {
        return color;
    }
    double getRefelexion() const override {
        return reflection;
    }

};

class Triangle : public Objet {
public:
    Vector3::Point3 v0, v1, v2;
    double reflection;

    Triangle(const Vector3::Point3& p0, const Vector3::Point3& p1, const Vector3::Point3& p2) : v0(p0), v1(p1), v2(p2) {}

    double sdf(const Vector3::Point3& pos) const override {
        return 0.0;
    }

    Vector3::Color getColor() const override {
        return Vector3::Color(1.0, 1.0, 1.0);
    }
    double getRefelexion() const override {
        return reflection;
    }
};

