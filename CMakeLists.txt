cmake_minimum_required(VERSION 3.20...4.5)
project(CarEvolved LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(CarEvolved
    main.cpp
    Entities/Camera.cpp Entities/Camera.h
    Entities/Mesh.cpp Entities/Mesh.h
    Collision/AABB.cpp Collision/AABB.h
    Util/cg.h Util/Const.h Util/OBJ_Loader.h
)

target_compile_definitions(CarEvolved PRIVATE
    ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Blender Files/"
)

target_link_libraries(CarEvolved PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT glm::glm)
