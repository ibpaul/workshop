include_directories(${Workshop_SOURCE_DIR}/filters/include)
include_directories(${Workshop_SOURCE_DIR}/image/include)
add_executable(runner main.cpp)

# Would like to wrap our libraries so we don't have to reference these third-party libraries.
include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
include_directories(${Workshop_SOURCE_DIR}/libs/libpng)


if (WIN32)
    target_link_libraries(runner PUBLIC filters image png_static zlibstatic)
else()
    target_link_libraries(runner PUBLIC filters image png_static X11)
endif (WIN32)

set_target_properties(
	runner
	PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

