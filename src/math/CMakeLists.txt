set(LIB_NAME lts_math)

set(INCLUDES
    ${Workshop_SOURCE_DIR}/include
    ${Workshop_SOURCE_DIR}/libs/eigen
)

set(SOURCES
    Matrix.cpp
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
