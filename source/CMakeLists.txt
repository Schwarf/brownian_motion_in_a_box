cmake_minimum_required(VERSION 3.20)
project(particle_scattering)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)



add_executable(main main.cpp)
add_subdirectory(particles)
include_directories(particles)
