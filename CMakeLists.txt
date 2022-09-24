cmake_minimum_required(VERSION 3.23)
project(Workshop)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory(C:/ws/workshop/filters)
#add_executable(filter-runner filter_runner/main.cpp)
#target_link_libraries(filter-runner PUBLIC filters)

add_executable(runner runner/main.cpp)
target_link_libraries(runner PUBLIC filters)
target_include_directories(runner PRIVATE filters)


add_library(filters filters/gaussian.cpp)