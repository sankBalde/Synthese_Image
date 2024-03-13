#include "vector3.hh"
#include "ray.hh"
#include "image.hh"
#include <iostream>
#include <ostream>
#include "scene.hh"


int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    std::vector<std::vector<Vector3::Color>> pixels_(image_width, std::vector<Vector3::Color>(image_height));

    //spheres
    /*Vector3::Point3 sphere1_center{-1, 0, -2};
    Vector3::Point3 sphere2_center{1, -0.5, -3};
    Vector3::Color sphere1_color{1, 0, 0};
    Vector3::Color sphere2_color{0, 0, 1};
    Sphere sphere1{sphere1_center, 0.5, sphere1_color};
    Sphere sphere2{sphere2_center, 0.7, sphere2_color};
    std::vector<Sphere> spheres{sphere1, sphere2};

    //camera
    Vector3::Point3 camera_center{0, 0, 0};
    Camera camera{camera_center};

    //lights
    Vector3::Vector3 lightdirection{-1, -1, -5};
    Light light1{lightdirection};
    std::vector<Light> lights{light1};

    auto scene = Scene(spheres, lights, camera);
    //auto scene = Scene();*/
    // Sphères
    Vector3::Point3 sun_center{0, 0, 0};
    Vector3::Color sun_color{1, 1, 0};
    Sphere sun{sun_center, 1, sun_color};

    Vector3::Point3 mercury_center{-2, 0, 0};
    Vector3::Color mercury_color{0.5, 0.5, 0.5};
    Sphere mercury{mercury_center, 0.1, mercury_color};

    Vector3::Point3 venus_center{-4, 0, 0};
    Vector3::Color venus_color{1, 1, 0.5};
    Sphere venus{venus_center, 0.2, venus_color};

    Vector3::Point3 earth_center{-6, 0, 0};
    Vector3::Color earth_color{0, 0, 1};
    Sphere earth{earth_center, 0.25, earth_color};

    Vector3::Point3 mars_center{-8, 0, 0};
    Vector3::Color mars_color{1, 0, 0};
    Sphere mars{mars_center, 0.2, mars_color};

    sun.setTextureMaterial(UniformTexture());
    mercury.setTextureMaterial(UniformTexture());
    venus.setTextureMaterial(UniformTexture());
    earth.setTextureMaterial(UniformTexture());
    mars.setTextureMaterial(UniformTexture());
    std::vector<Sphere> spheres{sun, mercury, venus, earth, mars};

// Caméra
    Vector3::Point3 camera_center{0, 0, 5};
    Camera camera{camera_center};

// Lumière
    Vector3::Vector3 light_direction{0, 0, -1};
    Light light1{light_direction};
    std::vector<Light> lights{light1};

    auto scene = Scene(spheres, lights, camera);


    // Render

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            Vector3::Point3 pixel_point(i, j, 0);
            auto rayDirection = scene.camera_.ray_direction(image_width, image_height, pixel_point);
            Ray r(scene.camera_.camera_center_, rayDirection);

            Sphere* closestSphere = nullptr;
            double hitDistance = std::numeric_limits<double>::max();

            for (auto& sphere : scene.spheres_) {
                auto t = sphere.hit_object(r);
                if (t > 0.0 && t < hitDistance) {
                    closestSphere = &sphere;
                    hitDistance = t;
                }
            }

            if (closestSphere == nullptr)
                pixels_[i][j] = Vector3::Color{0, 0, 0};
            else {
                Vector3::Color pixel_color = closestSphere->ray_color(r, scene.lights_[0].lightdirection_);
                pixels_[i][j] = pixel_color;
            }
        }
    }




    auto img = Image(image_width, image_height, pixels_);
    img.save_image("../../../../Desktop/solarSystem3.ppm");
    //img.save_image("images/imgRendered.ppm");
}