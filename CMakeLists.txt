cmake_minimum_required(VERSION 3.22.1)
project(Workshop)

set(CMAKE_CXX_STANDARD 14)

if (NOT UNIX)
    # On Windows, we have CMake find our included zlib library via our
    # provided FindZLIB.cmake file.
    # On Linux, we expect the user to have installed it via 'apt install zlib1g-dev`.
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
endif()

# Need to copy this file for some reason. libpng header documentation said to copy
# this file from here if it doesn't already exist.
file(COPY_FILE libs/libpng/scripts/pnglibconf.h.prebuilt libs/libpng/pnglibconf.h)

add_definitions(-Dcimg_use_png)

if (WIN32)
    # On Windows, this is needed for CLion to readily be able to run
    # our runner program with CLion and set the current working directory
    # to reference loading images from folder data.
    # On Linux, for some reason, this causes runner to not be built because
    # the build system tries to use a folder name to write the program to.
    #
    # I think the make system is trying to write to the folder /runner but
    # this directory already exists. Need a better fix at some point.
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_subdirectory(src/filter)
add_subdirectory(src/image)
add_subdirectory(src/util)
add_subdirectory(tools/filter)
add_subdirectory(libs/libpng)
if (WIN32)
    add_subdirectory(libs/zlib)
endif()

## Google Testing #############################################################
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
