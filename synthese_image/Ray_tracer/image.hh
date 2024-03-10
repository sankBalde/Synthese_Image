#pragma once
#include <vector>
#include <fstream>
#include "vector3.hh"

class Image
{
public:
    int image_width_;
    int image_height_;
    std::vector<std::vector<Vector3::Color>> pixels_;
    Image(int image_width_, int image_height, std::vector<std::vector<Vector3::Color>> pixels) :
    pixels_{std::move(pixels)}, image_height_{image_height}, image_width_(image_width_){};

    void save_image(const std::string& image_name)
    {
        std::ofstream file(image_name);
        file << "P3\n" << this->image_width_ << ' ' << this->image_height_ << "\n255\n";
        for (int j = 0; j < image_height_; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height_ - j) << ' ' << std::flush;
            for (int i = 0; i < image_width_; ++i) {
                Vector3::write_color(file, pixels_[i][j]);
            }
        }
        std::clog << "\rDone.                 \n";
        file.close();
    }

};
