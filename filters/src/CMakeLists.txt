include_directories(${Workshop_SOURCE_DIR}/filters/include)
include_directories(${Workshop_SOURCE_DIR}/include)
add_library(filters gaussian.cpp)

## Unit Test Setup ############################################################
include_directories(${Workshop_SOURCE_DIR}/image/include)

add_executable(
    filters_test
    Gaussian_test.cpp
)

target_link_libraries(
    filters_test
    GTest::gtest_main
    filters
    image
)

include(GoogleTest)
gtest_discover_tests(filters_test)
