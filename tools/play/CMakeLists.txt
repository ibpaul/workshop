include_directories(${Workshop_SOURCE_DIR}/include)

add_executable(
	play
	main.cpp
)

# Would like to wrap our libraries so we don't have to reference these third-party libraries.
include_directories(${Workshop_SOURCE_DIR}/libs/CImg)
include_directories(${Workshop_SOURCE_DIR}/libs/libpng)
include_directories(${Workshop_SOURCE_DIR}/libs/SFML/include)


set(SFML_LIBS_AND_DEPS
	sfml-audio
	sfml-system
)


if (WIN32)
    target_link_libraries(play PUBLIC lts_filter lts_image lts_util png_static zlibstatic ${SFML_LIBS_AND_DEPS})
else()
    target_link_libraries(play PUBLIC lts_filter lts_image lts_util png_static X11 ${SFML_LIBS_AND_DEPS})
endif()

set_target_properties(
	play
	PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	VS_DEBUGGER_COMMAND_ARGUMENTS "data/peppers.png"
)

