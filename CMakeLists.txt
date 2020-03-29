# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (CG_Track)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
	external/glfw/include/
	external/glm/
	external/glew/include/
	external/assimp/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_210
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

# Add executables here
# START REPEAT
	add_executable(hello_window 
		src/hello_window/hello_window.cpp
	)
	target_link_libraries(hello_window
		${ALL_LIBS}
	)
	# Xcode and Visual working directories
	set_target_properties(hello_window PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")
# END REPEAT