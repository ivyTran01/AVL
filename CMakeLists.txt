cmake_minimum_required(VERSION 3.17)
project(Assignment_6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_6
        A6Main.cpp AVLTree.h KeyNotFoundException.cpp KeyNotFoundException.h AVLTree.cpp EmptyTreeException.cpp EmptyTreeException.h)
