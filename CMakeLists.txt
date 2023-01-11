cmake_minimum_required(VERSION 3.0)
project(glteramoopp LANGUAGES C++)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "Cross-platform scene graph framework library intended for
demo and game projects written in C++")
set(CMAKE_C_STANDARD_LIBRARIES_INIT "-lgcc -lc -lm -ldl -lpthread") 
include(CMakeCInformation)
include(FindOpenGL)
include(CheckIncludeFile)
include(GNUInstallDirs)
include(FindPkgConfig)

FILE(GLOB_RECURSE SOURCE_FILES *.cpp)
FILE(GLOB_RECURSE INCLUDE_FILES *.cpp)

find_library(OpenGL::OpenGL OPENGL )


# digit_clock example
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES}
	${ENGINE_EXAMPLE_SOURCE_FILES})
set_property( TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
target_compile_options( ${PROJECT_NAME} PUBLIC -g  ${CGLM_CFLAGS}
	${GLFW_CFLAGS} ${DRAWTEXT_CFLAGS} ${OPENGL_CFLAGS} ${OPENGL_CFLAGS} )
target_include_directories( ${PROJECT_NAME} PUBLIC ${CGLM_INCLUDEDIR}
	${GLFW_INCLUDEDIR} ${DRAWTEXT_INCLUDEDIR} ${FREETYPE_INCLUDEDIR} ${OPENGL_INCLUDEDIR} )
target_link_libraries( ${PROJECT_NAME} PUBLIC ${CGLM_LIBRARIES}
	${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS}
	${CMAKE_C_STANDARD_LIBRARIES} ${FREETYPE_LIBRARIES} ${DRAWTEXT_LIBRARIES})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config)

