cmake_minimum_required(VERSION 3.20)
project(source)

set(CMAKE_CXX_STANDARD 14)


add_executable(main main.cpp)
add_subdirectory(particles)
include_directories(particles)
target_link_libraries(main particles_lib particles_interface_lib)