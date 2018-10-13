cmake_minimum_required(VERSION 3.12)
project(Processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Processor main.cpp Processor/Processor.cpp Processor/Processor.h Processor/WordToCodeConverter/WordToCodeConverter.cpp Processor/WordToCodeConverter/WordToCodeConverter.h)

#
#include_directories(
#        External Libs/googletest-master/googletest/googlemock/gtest
#)
##add_compile_definitions(DEBUG)
#add_executable(SafeStackTest Tests/SafeStackTester/SafeStackTest.cpp Tests/SafeStackTester/SafeStackTest.h SafeStack/SafeStack.cpp SafeStack/SafeStack.h)
#
#target_link_libraries(
#        SafeStackTest gtest gtest_main pthread)
#
#enable_testing()