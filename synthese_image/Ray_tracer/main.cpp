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
    Vector3::Point3 sphere1_center{ 0.0, -100.5, -10.0};
    Vector3::Point3 sphere2_center{0.0,    0.0, -1.0};
    Vector3::Color sphere1_color{1, 0, 0};
    Vector3::Color sphere2_color{0, 0, 1};
    Sphere sphere1{sphere1_center, 100, sphere1_color};
    Sphere sphere2{sphere2_center, 0.5, sphere2_color};
    sphere1.setTextureMaterial(UniformTexture());
    sphere2.setTextureMaterial(UniformTexture());
    std::vector<Object *> spheres{&sphere1, &sphere2};

    //camera
    Vector3::Point3 camera_center{0,0,0};
    Camera camera{camera_center, image_width, image_height};

    //lights
    Vector3::Vector3 lightdirection{4, 1, 4};
    Light light1{lightdirection};
    std::vector<Light> lights{light1};

    Scene scene{spheres, lights, camera};
    //auto scene = Scene();
    // Sphères
    /*Vector3::Point3 sun_center{0, 0, 0};
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
    Camera camera{camera_center, image_width, image_height};

// Lumière
    Vector3::Vector3 light_direction{0, 0, -1};
    Light light1{light_direction};
    std::vector<Light> lights{light1};

    auto scene = Scene(spheres, lights, camera);
    */

    // Render

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            Vector3::Point3 pixel_point(i, j, 0);
            Vector3::Color color = scene.PerPixel(pixel_point);
            pixels_[i][j] = color;
        }
    }




    auto img = Image(image_width, image_height, pixels_);
    img.save_image("../../../../Desktop/sha_re_sphe.ppm");
    //img.save_image("images/imgRendered.ppm");
}