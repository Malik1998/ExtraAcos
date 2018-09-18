//
// Created by user on 09.09.18.
//

#ifndef QUADRICQUATIONS_LINEAREQUATIONSOLVER_H
#define QUADRICQUATIONS_LINEAREQUATIONSOLVER_H

#include "../common_libs/Result/Result.h"

/// Solves Linear Equations and returns roots as Result object
class LinearEquationSolver {
public:
    /// Equation a * x + b = 0
    /// \param a - parametr multiplied on x
    /// \param b - free member
    /// \return - Roots as object of Result class, see specification of Result class
    static Result solve(double a, double b);
};


#endif //QUADRICQUATIONS_LINEAREQUATIONSOLVER_H
