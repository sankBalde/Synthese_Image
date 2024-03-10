#include <iostream>
#include "vector3.hh"
#include "image.hh"

int main(){
    // Image

    int image_width = 256;
    int image_height = 256;

    std::vector<std::vector<Vector3::Color>> pixels_(image_height, std::vector<Vector3::Color>(image_width));

    // Render

    //std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; ++j) {
        //std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto color = Vector3::Color(double(i) / (image_width-1), double(j) / (image_height-1), 0);
            //Vector3::write_color(std::cout, color);
            pixels_[i][j] = color;
        }
    }
    auto img = Image(image_width, image_height, pixels_);
    img.save_image("img.ppm");
    //std::clog << "\rDone.                 \n";
}