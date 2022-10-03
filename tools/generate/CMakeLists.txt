include_directories(${Workshop_SOURCE_DIR}/include)
include_directories(${Workshop_SOURCE_DIR}/libs/cxxopts)

add_executable(
	generate
	main.cpp
	options.cpp
)

# Would like to wrap our libraries so we don't have to reference these third-party libraries.
include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
include_directories(${Workshop_SOURCE_DIR}/libs/libpng)


if (WIN32)
    target_link_libraries(generate PUBLIC lts_filter image util png_static zlibstatic)
else()
    target_link_libraries(generate PUBLIC lts_filter image util png_static X11)
endif()

set_target_properties(
	generate
	PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	VS_DEBUGGER_COMMAND_ARGUMENTS "--image-to-cpp data/peppers.png output.txt"
)

