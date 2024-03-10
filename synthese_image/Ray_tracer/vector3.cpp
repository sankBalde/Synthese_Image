#include "vector3.hh"
#include <ostream>

std::ostream& Vector3::operator<<(std::ostream &os, const Vector3 &vect) {
    os << vect.x << " " << vect.y << " " << vect.z
    << "\n";
    return os;
}

void  Vector3::write_color(std::ostream &out, Color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x) << ' '
        << static_cast<int>(255.999 * pixel_color.y) << ' '
        << static_cast<int>(255.999 * pixel_color.z) << '\n';
}

Vector3::Vector3 Vector3::operator+(const Vector3 &lhs, const Vector3 &rhs) {
    auto res = Vector3(
            lhs.x + rhs.x,
            lhs.y + rhs.y,
            lhs.z + rhs.z
            );
    return res;
}

Vector3::Vector3 Vector3::operator-(const Vector3&lhs, const Vector3 &rhs) {
    auto res = Vector3(
            lhs.x - rhs.x,
            lhs.y - rhs.y,
            lhs.z - rhs.z
    );
    return res;
}

Vector3::Vector3 Vector3::operator*(const Vector3 &lhs, double scalar) {
    auto res = Vector3(
            lhs.x * scalar,
            lhs.y * scalar,
            lhs.z * scalar
            );
    return res;
}

Vector3::Vector3 Vector3::operator*(double scalar, const Vector3 &rhs) {
    return rhs * scalar;
}

Vector3::Vector3 Vector3::operator*(const Vector3 &lhs, const Vector3 &rhs) {
    auto res = Vector3(
            lhs.x * rhs.x,
            lhs.y * rhs.y,
            lhs.z * rhs.z
    );
    return res;
}

Vector3::Vector3& Vector3::Vector3::operator+=(const Vector3 &rhs) {

    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}

Vector3::Vector3 &Vector3::Vector3::operator-=(const Vector3 &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}

Vector3::Vector3 &Vector3::Vector3::operator*=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

Vector3::Vector3 Vector3::operator/(const Vector3 &lhs, double scalar)
{
    return lhs * (1/ scalar);
}


double Vector3::dot(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3::Vector3 Vector3::cross(const Vector3& u, const Vector3& v)
{
    auto res = Vector3(u.y * v.z - u.z * v.y,
                       u.z * v.x - u.x * v.z,
                       u.x * v.y - u.y * v.x);
    return res;
}

Vector3::Vector3 Vector3::unit_vector(Vector3 v) {
    return v / v.normEuclidienne();
}

