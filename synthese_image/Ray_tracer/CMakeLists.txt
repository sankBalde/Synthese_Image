cmake_minimum_required(VERSION 3.27)
project(synthese_image)

set(CMAKE_CXX_STANDARD 20)

add_executable(synthese_image
        vector3.hh
        main.cpp
        vector3.cpp
        image.hh
        ray.hh
        scene.hh
        scene.cpp)
