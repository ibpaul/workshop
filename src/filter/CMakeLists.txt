set(LIB_NAME lts_filter)

set(INCLUDES
    ../../include
)

set(SOURCES
    gaussian.cpp
    Kernel.cpp
    operations.cpp
)

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
        filter_test
        gaussian_test.cpp
    )

    target_link_libraries(
        filter_test
        GTest::gtest_main
        lts_filter
        lts_image
        lts_util
        png_static
        zlibstatic
    )

    include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
    include_directories(${Workshop_SOURCE_DIR}/libs/libpng)

    include(GoogleTest)
    gtest_discover_tests(filter_test)
endif()
