cmake_minimum_required(VERSION 3.20)
project(cameraman)


file(GLOB SOURCES src/*.c src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/src)


find_package(GLEW REQUIRED GLEW_USE_STATIC_LIBS)
include_directories(${GLEW_INCLUDE_DIRS})
if(UNIX)
	target_link_libraries(${PROJECT_NAME} "/usr/lib/x86_64-linux-gnu/libGLEW.so")
else()
	target_link_libraries(${PROJECT_NAME} "C:/Program Files (x86)/glew/lib/libglew32.dll.a")
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

if(UNIX)
	target_link_libraries(${PROJECT_NAME} cglm)
else()
	include_directories("C:/Program Files (x86)/cglm/include")
	target_link_libraries(${PROJECT_NAME} "C:/Program Files (x86)/cglm/lib/libcglm.dll.a")
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -lm)
target_link_libraries(${PROJECT_NAME} m)