include_directories(${Workshop_SOURCE_DIR}/filters/include)
include_directories(${Workshop_SOURCE_DIR}/image/include)
add_executable(runner main.cpp)
#target_link_libraries(runner PUBLIC filters image png zlib)
target_link_libraries(runner PUBLIC filters image png_static zlibstatic)

set_target_properties(
	runner
	PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
