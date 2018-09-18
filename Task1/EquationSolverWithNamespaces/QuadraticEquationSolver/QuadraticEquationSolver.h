//
// Created by user on 09.09.18.
//

#ifndef QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H
#define QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H

#include <cmath>
#include <array>

/// Class for Solving Quadratic equation a * x * x + b * x + c = 0
/// Where a != 0, otherwise LinearEquationSolver will be used
/// Default precision 1e-9
namespace QuadraticEquationSolver {
    /// Solve equation a * x * x + b * x + c = 0
    /// Equality with zero, used as: fabs(a) <= PRECISION
    /// If a = 0, LinearEquationSolver used
    /// \param a  - parametr of x^2
    /// \param b - parametr of x
    /// \param c - free member
    /// \return - array with  size 3,
    ///             if roots are Infinity, first,second,third index - std::numeric_limits<double>::max()
    ///             if roots are two, they are sorted and put in first indexes
    ///             if root is one, where first index - is root, second, thirs std::numeric_limits<double>::max()
    ///             if root - none, first,second,third index std::numeric_limits<double>::min()
    std::array<double, 3> solve(double a, double b, double c);

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
    /// Default precision 1e-9
    extern double PRECISION;

    /// Variable indication no roots, as shown in docs of solve
    extern std::array<double, 3> NO_ROOTS;
    /// Variable indication infinity roots, as shown in docs of solve
    extern std::array<double, 3> INFINITY_ROOTS;
};

#endif //QUADRICQUATIONS_QUADRATICEQUATIONSOLVER_H
