include_directories(${Workshop_SOURCE_DIR}/filters/include)
add_executable(runner main.cpp)
target_link_libraries(runner PUBLIC filters)
