cmake_minimum_required(VERSION 4.1.2)
project(genesis VERSION 1.0.0)
set(CMP0072 NEW)

Find_package(OpenGL REQUIRED)

add_executable(genesis
src/main.cpp
src/config.h
src/config.cpp
src/glad.c
src/triangle_mesh.cpp
src/material.cpp
src/linear_algebruh.cpp
)

target_include_directories(genesis PRIVATE dependencies)

target_link_libraries(genesis glfw3 OpenGL::GL)

