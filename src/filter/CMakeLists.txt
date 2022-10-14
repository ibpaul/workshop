set(LIB_NAME lts_filter)

set(INCLUDES
    ${Workshop_SOURCE_DIR}/include
    ${Workshop_SOURCE_DIR}/libs/eigen
)

set(SOURCES
    gaussian.cpp
    operations.cpp
)

if (DEFINED ZEPHYR_BASE)
    zephyr_library_named(${LIB_NAME})
    zephyr_library_compile_options(-O3 -std=c11 -ffast-math -Wno-array-bounds)
    zephyr_include_directories(${INCLUDES})
    zephyr_library_sources(${SOURCES})
else()
    include_directories(${INCLUDES})
    add_library(${LIB_NAME} STATIC ${SOURCES})
endif()


## Unit Test Setup ############################################################

if (NOT DEFINED ZEPHYR_BASE)
    add_executable(
        filter_test
        gaussian_test.cpp
        operations_test.cpp
    )
    
    set(TEST_LINKS
    	lts_filter
        lts_image
        lts_util
        png_static
    )
    
    if (WIN32)
	    set(TEST_LINKS ${TEST_LINKS} zlibstatic)
    elseif (UNIX)
    	set(TEST_LINKS ${TEST_LINKS} X11)
    endif()

    target_link_libraries(
        filter_test
        GTest::gtest_main
        ${TEST_LINKS}
    )

    include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
    include_directories(${Workshop_SOURCE_DIR}/libs/libpng)

    include(GoogleTest)
    gtest_discover_tests(filter_test)
endif()
