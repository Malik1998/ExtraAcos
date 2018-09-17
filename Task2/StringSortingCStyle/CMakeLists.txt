cmake_minimum_required(VERSION 3.10)
project(StringSorting)

set(CMAKE_CXX_STANDARD 11)

add_executable(StringSorting main.cpp StringSorter/StringSorter.cpp StringSorter/StringSorter.h FullFileReader/FullFileReader.cpp FullFileReader/FullFileReader.h)