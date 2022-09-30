include_directories(../../include)

add_library(utils
    PerformanceTest.cpp
    string.cpp
)

## Unit Test Setup ############################################################

add_executable(
    util_test
    statistics_test.cpp
)

target_link_libraries(
    util_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(util_test)
