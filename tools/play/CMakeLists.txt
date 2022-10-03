include_directories(${Workshop_SOURCE_DIR}/include)

add_executable(
	play
	main.cpp
)

# Would like to wrap our libraries so we don't have to reference these third-party libraries.
include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
include_directories(${Workshop_SOURCE_DIR}/libs/libpng)


if (WIN32)
    target_link_libraries(play PUBLIC lts_filter image util png_static zlibstatic)
else()
    target_link_libraries(play PUBLIC lts_filter image util png_static X11)
endif()

set_target_properties(
	play
	PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	VS_DEBUGGER_COMMAND_ARGUMENTS "data/peppers.png"
)

