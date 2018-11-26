cmake_minimum_required(VERSION 3.12)
project(TreeDifferntial)

set(CMAKE_CXX_STANDARD 14)

add_executable(TreeDifferntial main.cpp Tree/Tree.cpp Tree/Tree.h Node/Node.cpp Node/Node.h Data/Data.cpp Data/Data.h)