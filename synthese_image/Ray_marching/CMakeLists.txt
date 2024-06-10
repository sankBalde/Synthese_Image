cmake_minimum_required(VERSION 3.27)
project(synthese_image)

set(CMAKE_CXX_STANDARD 20)

add_executable(ray_marching
        vector3.hh
        main.cpp
        vector3.cpp
        image.hh
        raymarching.hh
        objects.hh)
