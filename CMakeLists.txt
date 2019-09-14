cmake_minimum_required(VERSION 3.13)
project(TAREA2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/glfw-3.3)
include_directories(libs/glfw-3.3/include)
include_directories(libs/glad/include)
include_directories(libs/glm)

add_executable(Tarea2 libs/glad/src/glad.c src/main.cpp src/Shader.h src/stb_image.h src/Camera.h src/Cube.h src/Texture.h src/Lamp.h)
target_link_libraries(Tarea2 glfw ${GLFW_LIBRARIES})

add_executable(PLAYGROUND libs/glad/src/glad.c src/playground.cpp src/Shader.h src/stb_image.h)