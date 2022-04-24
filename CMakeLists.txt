cmake_minimum_required(VERSION 3.22)
project(Novomatic)


ADD_LIBRARY(Collision
        src/Collision/collision.cpp
        )

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/)
add_subdirectory(test)
