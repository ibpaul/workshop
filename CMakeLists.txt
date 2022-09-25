cmake_minimum_required(VERSION 3.23)
project(Workshop)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

add_definitions(-Dcimg_use_png)

add_subdirectory(filters)
add_subdirectory(runner)
add_subdirectory(image)
add_subdirectory(libs/libpng)
add_subdirectory(libs/zlib)
