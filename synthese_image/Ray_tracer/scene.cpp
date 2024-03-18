//
// Created by Abdoulaye Baldé on 15/03/2024.
//
#include <cstdlib>
#include "scene.hh"
#include "vector3.hh"

HitPayload Scene::ClosestHit(const Ray &ray, float hitDistance, int objectIndex) {
    HitPayload payload;
    payload.HitDistance = hitDistance;
    payload.ObjectIndex = objectIndex;

    const Sphere& closestSphere = spheres_[objectIndex];

    Vector3::Vector3 origin = ray.origine() - closestSphere.sphere_center;
    //Vector3::Vector3 origin = closestSphere.sphere_center;
    payload.WorldPosition = origin + ray.direction() * hitDistance;
    payload.WorldNormal = Vector3::unit_vector(payload.WorldPosition);

    payload.WorldPosition += closestSphere.sphere_center;

    return payload;
}

HitPayload Scene::Miss(const Ray &ray) {
    HitPayload payload;
    payload.HitDistance = -1.0f;
    return payload;
}

double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

Vector3::Color Scene::PerPixel(Vector3::Point3 pixel_point) {

    auto rayDirection = camera_.ray_direction(pixel_point);
    Ray ray{camera_.camera_center_, rayDirection};

    Vector3::Vector3 light{0,0,0};
    Vector3::Vector3 lightDire{-1,-1,-1};
    //Vector3::Vector3 contribution{1.0, 1.0, 1.0};
    double multiplier = 1.0f;
    lightDire = Vector3::unit_vector(lightDire);
    int bounces = 3;
    for (int i = 0; i < bounces; i++)
    {
        HitPayload payload = TraceRay(ray);
        if (payload.HitDistance < 0.0f)
        {
            //Vector3::Vector3 skyColor(0.6f, 0.7f, 0.9f);
            Vector3::Vector3 skyColor(0, 0, 0);
            light += skyColor * multiplier;

            //light = Vector3::Color{0, 0, 0};
            break;
        }

        const Sphere& sphere = spheres_[payload.ObjectIndex];

        //contribution = contribution * sphere.sphere_color;

        Vector3::Vector3 normal = payload.WorldNormal;
        double cos_angle_normal_light = to_positive(Vector3::dot(normal, -lightDire));
        Vector3::Color diffuse_color = sphere.sphere_color * cos_angle_normal_light;

        light += diffuse_color * multiplier * sphere.textureMaterial->getParametersAtPosition(pixel_point);

        multiplier *= 0.7f;

        ray.setorigine(payload.WorldPosition + payload.WorldNormal * 0.0001f);
        ray.setdirection(Sphere::reflect(ray.direction(), payload.WorldNormal));
    }

    return light;
}




HitPayload Scene::TraceRay(const Ray &ray) {
    int closestSphere = -1;
    float hitDistance = std::numeric_limits<float>::max();
    for (size_t i = 0; i < spheres_.size(); i++)
    {
        const Sphere& sphere = spheres_[i];
        Vector3::Vector3 origin = ray.origine() - sphere.sphere_center;

        float a = Vector3::dot(ray.direction(), ray.direction());
        float b = 2.0f * Vector3::dot(origin, ray.direction());
        float c = Vector3::dot(origin, origin) - sphere.radius * sphere.radius;

        // Quadratic forumula discriminant:
        // b^2 - 4ac

        float discriminant = b * b - 4.0f * a * c;
        if (discriminant < 0.0f)
            continue;

        // Quadratic formula:
        // (-b +- sqrt(discriminant)) / 2a

        // float t0 = (-b + sqrt(discriminant)) / (2.0f * a); // Second hit distance (currently unused)
        float closestT = (-b - sqrt(discriminant)) / (2.0f * a);
        if (closestT > 0.0f && closestT < hitDistance)
        {
            hitDistance = closestT;
            closestSphere = (int)i;
        }
    }

    if (closestSphere < 0)
        return Miss(ray);

    return ClosestHit(ray, hitDistance, closestSphere);

}