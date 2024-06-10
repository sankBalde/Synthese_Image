#pragma once
#include <iostream>
#include <vector>
#include <limits>

#include "vector3.hh"
#include "objects.hh"

struct HitPayload {
    double HitDistance;
    Vector3::Vector3 WorldPosition;
    Vector3::Vector3 WorldNormal;
    Vector3::Color Color;
    int ObjectIndex;
};

struct Dist_object {
    int ObjectIndex;
    double distance;
};

Dist_object sdf_scene(const Vector3::Point3& pos, const std::vector<Objet*>& objets) {
    double min_distance = std::numeric_limits<double>::max();
    Dist_object info_sdf;
    for (int i = 0; i < objets.size(); ++i) {
        double dist = objets[i]->sdf(pos);
        if (dist < min_distance) {
            min_distance = dist;
            info_sdf.ObjectIndex = i;
        }
    }
    info_sdf.distance = min_distance;
    return info_sdf;
}

Vector3::Vector3 calculate_normal(const Vector3::Point3& pos, const std::vector<Objet*>& objets) {
    const double epsilon = 1e-3;
    double dx = sdf_scene(Vector3::Point3(pos.x + epsilon, pos.y, pos.z), objets).distance - sdf_scene(Vector3::Point3(pos.x - epsilon, pos.y, pos.z), objets).distance;
    double dy = sdf_scene(Vector3::Point3(pos.x, pos.y + epsilon, pos.z), objets).distance - sdf_scene(Vector3::Point3(pos.x, pos.y - epsilon, pos.z), objets).distance;
    double dz = sdf_scene(Vector3::Point3(pos.x, pos.y, pos.z + epsilon), objets).distance - sdf_scene(Vector3::Point3(pos.x, pos.y, pos.z - epsilon), objets).distance;
    return Vector3::unit_vector(Vector3::Vector3(dx, dy, dz));
}

HitPayload raymarch(const Vector3::Point3& orig, const Vector3::Vector3& dir, const std::vector<Objet*>& objets, int max_steps = 100, double epsilon = 1e-3) {
    double dist = 0.0;
    HitPayload payload;
    payload.HitDistance = -1.0;
    payload.ObjectIndex = -1;

    for (int i = 0; i < max_steps; ++i) {
        Vector3::Point3 pos = orig + dist * dir;
        Dist_object info_sdf = sdf_scene(pos, objets);
        if (info_sdf.distance < epsilon) {
            payload.HitDistance = dist;
            payload.WorldPosition = pos;
            payload.WorldNormal = calculate_normal(pos, objets);
            payload.ObjectIndex = info_sdf.ObjectIndex;
            payload.Color = objets[info_sdf.ObjectIndex]->getColor();
            return payload;
        }
        dist += info_sdf.distance;
        if (dist > 100.0) {
            break;
        }
    }
    return payload;
}

bool is_in_shadow(const Vector3::Point3& point, const Vector3::Vector3& light_dir, const std::vector<Objet*>& objets, double light_distance, double epsilon = 1e-3) {
    Vector3::Point3 orig = point + light_dir;
    double dist = 0.0;
    for (int i = 0; i < 100; ++i) {
        Vector3::Point3 pos = orig + dist * light_dir;
        Dist_object info_sdf = sdf_scene(pos, objets);
        if (info_sdf.distance < epsilon) {
            return true;
        }
        dist += info_sdf.distance;
        if (dist > light_distance) {
            break;
        }
    }
    return false;
}

Vector3::Vector3 reflect(const Vector3::Vector3& dir, const Vector3::Vector3& normal) {
    return dir - 2.0 * dot(dir, normal) * normal;
}

Vector3::Color calculate_color(const Vector3::Point3& orig, const Vector3::Vector3& dir, const std::vector<Objet*>& objets, const Vector3::Vector3& light_dir, int max_depth = 5) {
    Vector3::Color color(0.0, 0.0, 0.0);
    Vector3::Vector3 current_dir = dir;
    Vector3::Point3 current_orig = orig;
    double current_reflection = 1.0;

    HitPayload hit = raymarch(current_orig, current_dir, objets);
    bool shadow = is_in_shadow(hit.WorldPosition, light_dir, objets, 100.0);
    if (shadow)
        return color;

    for (int depth = 0; depth < max_depth; ++depth) {
        HitPayload hit = raymarch(current_orig, current_dir, objets);
        if (hit.HitDistance < 0) {
            break;
        }

        const Objet* hit_obj = objets[hit.ObjectIndex];
        Vector3::Color obj_color = hit_obj->getColor();
        double light_intensity = std::max(0.0, dot(hit.WorldNormal, light_dir));



        if (hit.HitDistance < 100) {
            color += current_reflection * obj_color * light_intensity;
        } else {
            break;
        }
        if (hit_obj->getRefelexion() <= 0.0) {
            break;
        }


        current_reflection *= 0.7f;
        current_dir = reflect(current_dir, hit.WorldNormal);
        current_orig = hit.WorldPosition + hit.WorldNormal;
    }

    return color;
}
