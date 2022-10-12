cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr)
project(zephyr_filter)
add_compile_definitions(LTS_EIGEN_MATRIX)
include_directories(${APPLICATION_SOURCE_DIR}/../../include)
target_sources(app PRIVATE src/main.cpp)

include_directories(${APPLICATION_SOURCE_DIR}/../../libs/eigen)
add_subdirectory("../../src/filter" "${CMAKE_CURRENT_BINARY_DIR}/lts/filter")
add_subdirectory("../../src/image" "${CMAKE_CURRENT_BINARY_DIR}/lts/image")
add_subdirectory("../../src/util" "${CMAKE_CURRENT_BINARY_DIR}/lts/util")

target_link_libraries(app PUBLIC lts_filter lts_util lts_image)
