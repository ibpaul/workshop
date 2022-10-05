include_directories(${Workshop_SOURCE_DIR}/include)

add_library(
    lts_filter
    gaussian.cpp
    Kernel.cpp
    operations.cpp
)

## Unit Test Setup ############################################################

#include_directories(${Workshop_SOURCE_DIR}/image/include)

add_executable(
    filter_test
    gaussian_test.cpp
)

target_link_libraries(
    filter_test
    GTest::gtest_main
    lts_filter
    image
    util
)

include(GoogleTest)
gtest_discover_tests(filter_test)
