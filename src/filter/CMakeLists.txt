include_directories(${Workshop_SOURCE_DIR}/include)

add_library(
    lts_filter
    versions/gaussian_v0.cpp
    versions/gaussian_v1.cpp
    versions/gaussian_v2.cpp
    Kernel.cpp
)

## Unit Test Setup ############################################################

#include_directories(${Workshop_SOURCE_DIR}/image/include)

add_executable(
    filter_test
    Gaussian_test.cpp
)

target_link_libraries(
    filter_test
    GTest::gtest_main
    lts_filter
    image
)

include(GoogleTest)
gtest_discover_tests(filter_test)
