cmake_minimum_required(VERSION 3.28)
project(my_normal_project)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_GLIBCXX_USE_CXX17_ABI=0)

add_executable(normal main.cpp
        path_printer.cpp
        path_printer.h
        bellman_ford.cpp
        bellman_ford.h
        adjacency_matrix.cpp
        adjacency_matrix.h
        dijkstra.cpp
        dijkstra.h
)
