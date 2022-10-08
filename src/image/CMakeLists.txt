set(LIB_NAME lts_image)

set(INCLUDES
    ../../include
)

if (NOT DEFINED ZEPHYR_BASE)
    set(INCLUDES ${INCLUDES}
        ${Workshop_SOURCE_DIR}/libs/CImg
        ${Workshop_SOURCE_DIR}/libs/libpng
    )
endif()

set(SOURCES
    TestImages.cpp
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


## Google Test Setup ##########################################################

if (NOT DEFINED ZEPHYR_BASE)
    add_executable(
        image_test
        TestImages_test.cpp
    )

    target_link_libraries(
        image_test
        GTest::gtest_main
        lts_image
    )

    include(GoogleTest)
    gtest_discover_tests(image_test)
endif()
