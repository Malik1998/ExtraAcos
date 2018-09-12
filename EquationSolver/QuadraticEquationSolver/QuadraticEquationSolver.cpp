//
// Created by user on 09.09.18.
//

#include "QuadraticEquationSolver.h"
#include "../LinearEquationSolver/LinearEquationSolver.h"

namespace QuadraticEquationSolver {

    Result solve(double a, double b, double c) {
        if (isNotQuadratic(a, b, c)) {
            return LinearEquationSolver::solve(b, c);
        } else {
            double discriminant = b * b - 4 * a * c;
            if (discriminant < 0) {
                return Result::getNoneRoots();
            } else {
                std::set<double> roots; // Use Array !!!
                roots.insert((-b + std::sqrt(discriminant)) / (2 * a));
                roots.insert((-b - std::sqrt(discriminant)) / (2 * a));
                return Result::getCountableRoots(std::move(roots));
            }
        }
    }

    bool isNotQuadratic(double a, double b, double c) {
        return a == 0;
    }

    void setPresicion(double eps) {
        PRECISION = eps;
    }

    double getPresison() {
        return PRECISION;
    }

    double PRECISION = 1e-9;
}