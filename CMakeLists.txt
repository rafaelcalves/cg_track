# CMake entry point
cmake_minimum_required (VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
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

include_directories(
	external/glfw/include/
	external/glm/
	external/glew/include/
	external/assimp/include/
	common
	common/stb
	common/glad
	common/KHR
	common/structure
	common/structure_curve
	.
)
set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_210
)
file(GLOB COMMON
	"common/*.hpp"
	"common/*.cpp"
	"common/*.h"
	"common/*.c"
	"common/*/*.hpp"
	"common/*/*.cpp"
	"common/*/*.h"
	"common/*/*.c"
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set(EXERCISE	
	obj_load
	curve_generator
)

foreach(EXERCISE ${EXERCISE})
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/${EXERCISE}")
	file(GLOB SOURCE
		"src/${EXERCISE}/${EXERCISE}.cpp"
	)
	add_executable(${EXERCISE} 
		${SOURCE}
		${COMMON}
	)
	target_link_libraries(${EXERCISE}
		${ALL_LIBS}
	)
	# Xcode and Visual working directories
	set_target_properties(${EXERCISE} PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")
	file(COPY "src/${EXERCISE}/resources" DESTINATION "${PROJECT_BINARY_DIR}/bin/${EXERCISE}")
endforeach(EXERCISE)