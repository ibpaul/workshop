include_directories(${Workshop_SOURCE_DIR}/utils/include)


## Unit Test Setup ############################################################
include_directories(${Workshop_SOURCE_DIR}/utils/include)

add_executable(
        utils_test
        src/statistics_test.cpp
)

target_link_libraries(
        utils_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utils_test)
