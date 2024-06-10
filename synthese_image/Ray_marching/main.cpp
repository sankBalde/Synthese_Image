#include <iostream>
#include <vector>
#include <cmath>
#include <cmath>

#include "vector3.hh"
#include "image.hh"
#include "raymarching.hh"
#include "objects.hh"

using namespace Vector3;

// Paramètres de l'image
const int image_width = 800;
const int image_height = 600;
const double aspect_ratio = double(image_width) / image_height;
const double fov = M_PI / 3;


const Point3 camera_pos(0.0, 0.0, -5.0);


const Point3 light_dir = unit_vector(Point3(-3.0, 1.0, -1.0));

int main() {

    Sphere sphere(Point3(-1.7, 0.0, 0.0), Color(1.0, 0.0, 0.0), 1.0, 0.5);
    Plan plane(Point3(-0.1, 1.0, 0.0), Color(0.0, 1.0, 0.0), 1.0, 0.5);
    Nice_cube cube(Point3(2.5, 1.0, 0.0), Point3(1.0, 1.0, 1.0), Color(0.0, 0.0, 1.0), 1.3, 0.5);
    // Triangle triangle(Point3(0.0, 0.0, 0.0), Point3(1.0, 0.0, 0.0), Point3(0.0, 1.0, 0.0));

    std::vector<Objet*> objets = { &sphere, &cube, &plane/*, &triangle */ };


    std::vector<std::vector<Color>> pixels(image_width, std::vector<Color>(image_height));

    for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {

            double nx = (double(x) / image_width) * 2 - 1;
            double ny = 1 - (double(y) / image_height) * 2;


            Point3 dir(nx * aspect_ratio * std::tan(fov / 2), ny * std::tan(fov / 2), 1.0);
            dir = unit_vector(dir);


            Color color = calculate_color(camera_pos, dir, objets, light_dir, 10);

            pixels[x][y] = color;
        }
    }


    Image image(image_width, image_height, pixels);
    image.save_image("../images/final_image.ppm");

    return 0;
}
