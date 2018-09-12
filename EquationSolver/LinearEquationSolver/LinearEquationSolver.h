//
// Created by user on 09.09.18.
//

#ifndef QUADRICQUATIONS_LINEAREQUATIONSOLVER_H
#define QUADRICQUATIONS_LINEAREQUATIONSOLVER_H

#include <array>

/// Solves Linear Equations and returns roots as array
/// Default precision 1e-9
namespace LinearEquationSolver {
    /// Solve equation a * x + b  = 0
    /// \param a  - parametr of x
    /// \param b - parametr - free
    /// \return - array with  size 2,
    ///             if roots are Infinity, first,second index - std::numeric_limits<double>::max()
    ///             if root is one, where first index - is root, second std::numeric_limits<double>::max()
    ///             if root - none, first,second index std::numeric_limits<double>::min()
    std::array<double, 2> solve(double a, double b);

    /// Set presion of calculating roots to eps
    /// \param eps - new precision - default = 1e-9
    void setPresicion(double eps);

    /// Get current precision
    /// \return current precision - default = 1e-9
    double getPresison();

    /// Precisoion used to compare with 0;
    /// Default precision 1e-9
    extern double PRECISION;

    extern std::array<double, 2> NO_ROOTS;
    extern std::array<double, 2> INFINITY_ROOTS;
};


#endif //QUADRICQUATIONS_LINEAREQUATIONSOLVER_H
