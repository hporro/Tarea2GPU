cmake_minimum_required(VERSION 3.13)
project(TAREA2)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs/glm)

set(MODELS src/Models/Cube.h src/Models/Lamp.h src/Models/Tetrahedron.h src/Models/Piramid.h src/Models/Sphere.h src/Models/ModelImporter.h)
set(SOURCES src/Core/Shader.h src/Camera/FPSCamera.h src/Core/Texture.h ${MODELS} src/Camera/CenteredCamera.h src/Light.h src/objloader.h)
set(LIBS libs/stb_image.h)

add_executable(Tarea2 src/main.cpp ${LIBS} ${SOURCES})
target_link_libraries(Tarea2 glfw GLEW GL ${GLFW_LIBRARIES})

add_executable(PLAYGROUND src/playground.cpp ${LIBS} ${SOURCES})
target_include_directories(PLAYGROUND PRIVATE libs)