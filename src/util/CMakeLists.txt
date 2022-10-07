include_directories(../../include)

set(SOURCE_FILES
    string.cpp
    statistics.cpp
)

if (NOT DEFINED ZEPHYR_BASE)
    set(SOURCE_FILES
        ${SOURCE_FILES}
        PerformanceTest.cpp
    )
endif()

add_library(util ${SOURCE_FILES})

## Unit Test Setup ############################################################

if (NOT DEFINED ZEPHYR_BASE)
    add_executable(
        util_test
        statistics_test.cpp
    )

    target_link_libraries(
        util_test
        GTest::gtest_main
        util
    )

    include(GoogleTest)
    gtest_discover_tests(util_test)
endif()
