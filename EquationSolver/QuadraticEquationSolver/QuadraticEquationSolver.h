//
// Created by user on 09.09.18.
//

#ifndef QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H
#define QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H

#include "../common_libs/Result/Result.h"
#include <cmath>

/// Class for Solving Quadratic equation a * x * x + b * x + c = 0
/// Where a != 0, otherwise LinearEquationSolver will be used
class QuadraticEquationSolver {
public:
    /// Solve equation a * x * x + b * x + c = 0
    /// If a = 0, LinearEquationSolver used
    /// \param a  - parametr of x^2
    /// \param b - parametr of x
    /// \param c - free member
    /// \return - Result object with appropriate roots and count
    /// Roots are unique
    static Result solve(double a, double b, double c);

private:
    /// Check if Equation given is quadratic (a != 0)
    /// \param a  - parametr of x^2
    /// \param b - parametr of x
    /// \param c - free member
    /// \return true - if quadratic, false - else
    bool static isNotQuadratic(double a, double b, double c);
};

#endif //QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H
