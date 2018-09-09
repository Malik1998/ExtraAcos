//
// Created by user on 09.09.18.
//

#include "LinearEquationSolver.h"
#include "../common_libs/Result/Result.h"


Result LinearEquationSolver::solve(double a, double b) {
    if (a == 0 && b == 0) {
        return Result::getInfinityRoots();
    } else if (b == 0) {
        return Result::getNoneRoots();
    } else {
        std::set<double> roots;
        roots.insert(-b / a);
        return Result::getCountableRoots(std::move(roots));
    }
}