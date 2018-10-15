cmake_minimum_required(VERSION 3.10)
project(SafeStackLib)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        External Libs/googletest-master/googletest/googlemock/gtest
)
#add_compile_definitions(DEBUG)
add_executable(SafeStackTest Tests/SafeStackTester/SafeStackTest.cpp Tests/SafeStackTester/SafeStackTest.h SafeStack/SafeStack.h)

target_link_libraries(
        SafeStackTest gtest gtest_main pthread)

enable_testing()