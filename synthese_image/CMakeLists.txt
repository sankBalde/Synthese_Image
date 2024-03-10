cmake_minimum_required(VERSION 3.27)
project(synthese_image)

set(CMAKE_CXX_STANDARD 20)

add_executable(synthese_image
        Ray_tracer/vector3.hh
        Ray_tracer/main.cpp
        Ray_tracer/vector3.cpp
        Ray_tracer/image.hh
        Ray_tracer/ray.hh
        Ray_tracer/scene.hh)
