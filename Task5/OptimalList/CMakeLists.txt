cmake_minimum_required(VERSION 3.12)
project(OptimalList)

set(CMAKE_CXX_STANDARD 14)

add_executable(OptimalList main.cpp List/Node.cpp List/Node.h OptimalList/OptimalList.cpp OptimalList/OptimalList.h)

include_directories(

        External Libs/googletest-master/googletest/googlemock/gtest
)


add_executable(OptimalListTest tests/OptimalListTest/OptimalListTest.cpp
        OptimalList List/Node.cpp List/Node.h OptimalList/OptimalList.cpp OptimalList/OptimalList.h)
#
target_link_libraries(
        OptimalListTest gtest gtest_main pthread)

enable_testing()