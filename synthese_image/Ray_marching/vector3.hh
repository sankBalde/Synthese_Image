//
// Created by Abdoulaye Baldé on 08/03/2024.
//

#ifndef SYNTHESE_IMAGE_VECTOR3_HH
#define SYNTHESE_IMAGE_VECTOR3_HH

#include <ostream>
namespace Vector3 {
    class Vector3 {
    public:
        double x = 0;
        double y = 0;
        double z = 0;

        Vector3() = default;

        Vector3(double e0, double e1, double e2): x{e0}, y{e1}, z{e2} {}

        Vector3 operator-() const { return Vector3(-x, -y, -z); }

        Vector3& operator+=(const Vector3& rhs);
        Vector3& operator-=(const Vector3& rhs);
        Vector3& operator*=(double scalar);
        Vector3& operator/=(double scalar) { *this *= 1/scalar; return *this;}

        double normEuclidienne()
        {
            return sqrt(x * x + y * y + z * z);
        }

    };
    using Point3 = Vector3;
    using Color = Vector3;
    std::ostream& operator<<(std::ostream& os, const Vector3& vect);
    Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator*(const Vector3& lhs, double scalar);
    Vector3 operator*(double scalar, const Vector3& rhs);
    Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator/(const Vector3& lhs, double scalar);
    double dot(const Vector3& lhs, const Vector3& rhs);
    Vector3 cross(const Vector3& u, const Vector3& v);
    Vector3 unit_vector(Vector3 v);
    void write_color(std::ostream &out, Color pixel_color);
}

#endif //SYNTHESE_IMAGE_VECTOR3_HH
