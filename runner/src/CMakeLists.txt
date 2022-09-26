include_directories(${Workshop_SOURCE_DIR}/filters/include)
include_directories(${Workshop_SOURCE_DIR}/image/include)
add_executable(runner main.cpp)

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

