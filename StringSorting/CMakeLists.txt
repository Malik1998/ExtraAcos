cmake_minimum_required(VERSION 3.10)
project(StringSorting)

set(CMAKE_CXX_STANDARD 11)

add_executable(StringSorting main.cpp SortString/StringSorter.cpp SortString/StringSorter.h ReadFullFile/FullFileReader.cpp ReadFullFile/FullFileReader.h)