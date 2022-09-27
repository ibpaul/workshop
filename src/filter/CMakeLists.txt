include_directories(${Workshop_SOURCE_DIR}/include)

add_library(
    filter
    gaussian.cpp
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
    filter
    image
)

include(GoogleTest)
gtest_discover_tests(filter_test)
