#pragma once
#include <vector>
#include "vector3.hh"


class Sphere
{
public:
    double radius = 0.5;
    Vector3::Point3 sphere_center{0, 0, -1};
    Vector3::Color sphere_color{1, 0, 0};

    Sphere() = default;
    Sphere(Vector3::Point3 sphere_center, double radius, Vector3::Color sphere_color) : radius{radius},
                                                                                        sphere_center{sphere_center},
                                                                                        sphere_color{sphere_color}{}

    double hit_sphere(const Ray& r) {
        Vector3::Vector3 oc = r.origine() - sphere_center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b*b - 4*a*c;
        if (discriminant < 0) {
            return -1.0;
        } else {
            return (-b - sqrt(discriminant) ) / (2.0*a);
        }
    }

    double to_positive(double dot) {
        if (dot < 0.0)
            return 0.0;
        else
            return dot;
    }

    Vector3::Vector3 normal_vector(const Ray& r, double t)
    {
        Vector3::Vector3 normal = unit_vector(r.at(t) - sphere_center);
        return normal;
    }

    Vector3::Color ray_color(const Ray& r, const Vector3::Vector3& lightDirection) {
        auto t = hit_sphere(r);
        if (t > 0.0) {
            Vector3::Vector3 normal = normal_vector(r, t);
            double cos_angle_normal_light = to_positive(Vector3::dot(normal, -lightDirection));
            return sphere_color * cos_angle_normal_light; // Multiplier par la couleur de la lumière
        }
        return Vector3::Color(0,0,0);
    }

};

class Light
{
public:
    Vector3::Vector3 lightdirection_{-1, -1, -1};

    Light(){ lightdirection_ /= lightdirection_.normEuclidienne(); }
    Light(Vector3::Vector3 lightdirection) : lightdirection_{lightdirection}
    {
        this->lightdirection_ /= lightdirection.normEuclidienne();
    }
};

class Camera
{
public:
    Vector3::Point3 camera_center_{0, 0, 0};

    Camera() = default;

    Camera(Vector3::Point3 camera_center): camera_center_{camera_center}{}


    Vector3::Vector3 ray_direction(double image_width, double image_height, Vector3::Point3 spotted_Point)
    {
        // Camera

        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);


        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = Vector3::Vector3(viewport_width, 0, 0);
        auto viewport_v = Vector3::Vector3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        auto pixel_delta_u = viewport_u / image_width;
        auto pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = camera_center_
                                   - Vector3::Vector3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        double pixel_i = spotted_Point.x; // From image width
        double pixel_j = spotted_Point.y; // From image height

        auto pixel_center = pixel00_loc + (pixel_i * pixel_delta_u) + (pixel_j * pixel_delta_v);
        auto ray_direction = pixel_center - camera_center_;
        return ray_direction;
    }

};

class Scene
{
public:
    std::vector<Sphere> spheres_{Sphere()};
    std::vector<Light> lights_{Light()};

    Camera camera_{Camera()};

    Scene() = default;
    Scene(std::vector<Sphere> spheres, std::vector<Light> lights, Camera camera): spheres_{std::move(spheres)},
                                                                                  lights_{std::move(lights)}, camera_{camera} {}

};