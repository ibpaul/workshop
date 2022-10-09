set(INCLUDES
    ${Workshop_SOURCE_DIR}/include
    ${Workshop_SOURCE_DIR}/libs/cxxopts
    ${Workshop_SOURCE_DIR}/libs/eigen
)

include_directories(${INCLUDES})

add_executable(
	filter
	main.cpp
	options.cpp
)

# Would like to wrap our libraries so we don't have to reference these third-party libraries.
include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
include_directories(${Workshop_SOURCE_DIR}/libs/libpng)


if (WIN32)
    target_link_libraries(filter PUBLIC lts_framework lts_filter lts_image lts_util png_static zlibstatic)
else()
    target_link_libraries(filter PUBLIC lts_framework lts_filter lts_image lts_util png_static X11)
endif()

set_target_properties(
	filter
	PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	VS_DEBUGGER_COMMAND_ARGUMENTS "--type=gaussian{3,3} data/peppers.png output.png"
)

