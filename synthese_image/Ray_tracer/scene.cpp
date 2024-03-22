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

    auto closestObject = objects_[objectIndex];

    payload.WorldPosition = ray.at(hitDistance);
    payload.WorldNormal = closestObject->normal_vector(ray, hitDistance);

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

double euclidean_distance(Vector3::Vector3 v1,Vector3::Vector3 v2) {
    double dx = v1.x - v2.x;
    double dy = v1.y - v2.y;
    double dz = v1.z - v2.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}


Vector3::Color Scene::PerPixel(Vector3::Point3 pixel_point) {

    auto rayDirection = camera_.ray_direction(pixel_point);
    Ray ray{camera_.camera_center_, rayDirection};

    Vector3::Vector3 light{0,0,0};
    Vector3::Vector3 lightDire{-1, -1, -1};
    //Vector3::Vector3 contribution{1.0, 1.0, 1.0};
    double multiplier = 1.0f;
    lightDire = Vector3::unit_vector(lightDire);

    // ombre
    // Pour chaque source lumineuse
    for (const auto& lightA : lights_) {
        Vector3::Vector3 lightDirection = lightA.lightdirection_;

        bool inShadow = false;
        double epsilon = 0.0001f;
        HitPayload firstHit = TraceRay(ray, -1);

        // Vérifier s'il y a une intersection avec un objet entre le point d'intersection et la source lumineuse
        HitPayload shadowHit = TraceRay(Ray{firstHit.WorldPosition, lightDirection}, firstHit.ObjectIndex);
        double distance_one = euclidean_distance(firstHit.WorldPosition, lightDirection);
        double distance_two = euclidean_distance(firstHit.WorldPosition, shadowHit.WorldPosition);
        if (shadowHit.HitDistance > 0  && distance_one > distance_two) {
            inShadow = true;
        }

        if (firstHit.HitDistance > 0) {
            if (inShadow)
                return light;
        }
    }

    int bounces = 5;
    for (int i = 0; i < bounces; i++)
    {
        HitPayload payload = TraceRay(ray, -1);
        if (payload.HitDistance < 0.0f)
        {
            //Vector3::Vector3 skyColor(0.6f, 0.7f, 0.9f);
            Vector3::Vector3 skyColor(0, 0, 0);
            light += skyColor * multiplier;

            //light = Vector3::Color{0, 0, 0};
            break;
        }

        auto object = objects_[payload.ObjectIndex];

        //contribution = contribution * sphere.sphere_color;

        Vector3::Vector3 normal = payload.WorldNormal;
        double cos_angle_normal_light = to_positive(Vector3::dot(normal, -lightDire));
        Vector3::Color diffuse_color = object->getobjetColor() * cos_angle_normal_light;

        light += diffuse_color * multiplier * object->textureMaterial->getParametersAtPosition(pixel_point);

        multiplier *= 0.7f;

        ray.setorigine(payload.WorldPosition + payload.WorldNormal * 0.0001f);
        ray.setdirection(Sphere::reflect(ray.direction(), payload.WorldNormal));
    }

    return light;
}




HitPayload Scene::TraceRay(const Ray &ray, int ignore_object_index) {
    int closestSphere = -1;
    float hitDistance = std::numeric_limits<float>::max();
    for (size_t i = 0; i < objects_.size(); i++)
    {
        if (ignore_object_index != i) {
            auto object = objects_[i];
            float closestT = object->hit_object(ray);
            if (closestT > 0.0f && closestT < hitDistance) {
                hitDistance = closestT;
                closestSphere = (int) i;
            }
        }
    }

    if (closestSphere < 0)
        return Miss(ray);

    return ClosestHit(ray, hitDistance, closestSphere);

}