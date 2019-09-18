cmake_minimum_required(VERSION 3.13)
project(TAREA2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/glfw-3.3)
include_directories(libs/glfw-3.3/include)
include_directories(libs/glad/include)
include_directories(libs/glm)

set(SOURCES src/main.cpp src/Shader.h src/stb_image.h src/Camera.h src/Models/Cube.h src/Texture.h src/Models/Lamp.h src/Models/Bunny.h src/Models/Tetrahedron.h)
set(LIBS libs/glad/src/glad.c)

add_executable(Tarea2 ${LIBS} ${SOURCES})
target_link_libraries(Tarea2 glfw ${GLFW_LIBRARIES})

add_executable(PLAYGROUND libs/glad/src/glad.c src/playground.cpp src/Shader.h src/stb_image.h)