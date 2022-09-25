include_directories(${Workshop_SOURCE_DIR}/image/include)
include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
include_directories(${Workshop_SOURCE_DIR}/libs/libpng)
include_directories(${Workshop_SOURCE_DIR}/cmake-build-debug/libs/libpng)
add_library(image basic.cpp TestImages.cpp)

add_executable(
    image_test
    TestImages_test.cpp
)

target_link_libraries(
    image_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(image_test)
