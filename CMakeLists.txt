cmake_minimum_required(VERSION 3.0.0)
project(CarEvolved)

add_executable(CarEvolved main.cpp Entities/Camera.cpp Entities/Camera.h Util/cg.h Collision/AABB.cpp Collision/AABB.h Entities/Mesh.cpp Entities/Mesh.h Util/Const.h)

target_link_libraries(CarEvolved -lOpenGL32 -lfreeGLUT)