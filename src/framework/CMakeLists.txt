set(INCLUDES
    ${Workshop_SOURCE_DIR}/include
    ${Workshop_SOURCE_DIR}/libs/eigen
)

include_directories(${INCLUDES})

add_library(
    lts_framework
    FilterFactory.cpp
)
