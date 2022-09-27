include_directories(../../include)

add_library(utils
    PerformanceTest.cpp
)

## Unit Test Setup ############################################################

add_executable(
    utils_test
    statistics_test.cpp
)

target_link_libraries(
    utils_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utils_test)
