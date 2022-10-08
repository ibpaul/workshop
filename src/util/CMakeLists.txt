set(LIB_NAME lts_util)

set(INCLUDES
    ../../include
)

set(SOURCES
    statistics.cpp
    string.cpp
)

if (NOT DEFINED ZEPHYR_BASE)
    set(SOURCES
        ${SOURCES}
        PerformanceTest.cpp
    )
endif()

if (DEFINED ZEPHYR_BASE)
    zephyr_library_named(${LIB_NAME})
    zephyr_library_compile_options(-O3 -std=c11 -ffast-math -Wno-array-bounds)
    zephyr_include_directories(${INCLUDES})
    zephyr_library_sources(${SOURCES})
else()
    include_directories(${INCLUDES})
    add_library(${LIB_NAME} ${SOURCES})
endif()


## Unit Test Setup ############################################################

if (NOT DEFINED ZEPHYR_BASE)
    add_executable(
        util_test
        statistics_test.cpp
    )

    target_link_libraries(
        util_test
        GTest::gtest_main
        lts_util
    )

    include(GoogleTest)
    gtest_discover_tests(util_test)
endif()
