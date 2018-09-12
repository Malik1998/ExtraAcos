//
// Created by user on 09.09.18.
//

#ifndef QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H
#define QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H

#include "../common_libs/Result/Result.h"
#include <cmath>

/// Class for Solving Quadratic equation a * x * x + b * x + c = 0
/// Where a != 0, otherwise LinearEquationSolver will be used
namespace QuadraticEquationSolver {
    /// Solve equation a * x * x + b * x + c = 0
    /// If a = 0, LinearEquationSolver used
    /// \param a  - parametr of x^2
    /// \param b - parametr of x
    /// \param c - free member
    /// \return - Result object with appropriate roots and count
    /// Roots are unique
    Result solve(double a, double b, double c);

    /// Check if Equation given is quadratic (a != 0)
    /// \param a  - parametr of x^2
    /// \param b - parametr of x
    /// \param c - free member
    /// \return true - if quadratic, false - else
    bool static isNotQuadratic(double a, double b, double c);

    /// Set presion of calculating roots to eps
    /// \param eps - new precision - default = 1e-9
    void setPresicion(double eps);

    /// Get current precision
    /// \return current precision - default = 1e-9
    double getPresison();

    /// Precisoion used to compare with 0;
    extern double PRECISION;
};

#endif //QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H
