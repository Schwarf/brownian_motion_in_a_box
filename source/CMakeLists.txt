cmake_minimum_required(VERSION 3.20)
project(particle_scattering)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)
include(CheckCXXCompilerFlag)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CUDA_FLAGS}" "${flag}" flag_already_set)
    if (flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if (flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif ()
        unset(flag_supported CACHE)
    endif ()
endfunction()

enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-pedantic")
enable_cxx_compiler_flag_if_supported("-std=c++17")
enable_cxx_compiler_flag_if_supported("-O0")


add_executable(main main.cpp)
add_executable(sdl sdl_main.cpp sdl/SDL_wrapper.cpp sdl/SDL_wrapper.h)
add_subdirectory(particles)
include_directories(particles)
# target_include_directories(particle_scattering )
target_link_libraries(sdl SDL2main SDL2 GL)

