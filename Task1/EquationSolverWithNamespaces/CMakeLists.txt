cmake_minimum_required(VERSION 3.10)
project(QuadricQuations)

set(CMAKE_CXX_STANDARD 11)


include_directories(
        External Libs/googletest-master/googletest/googlemock/gtest
)

add_executable(QuadraticEquationSolverTest Tests/QuadraticEquatationSolver/QuadraticEquationSolverTest.cpp Tests/QuadraticEquatationSolver/QuadraticEquationSolverTest.h QuadraticEquationSolver/QuadraticEquationSolver.cpp QuadraticEquationSolver/QuadraticEquationSolver.h LinearEquationSolver/LinearEquationSolver.cpp LinearEquationSolver/LinearEquationSolver.h)

target_link_libraries(
        QuadraticEquationSolverTest gtest gtest_main pthread)

enable_testing()