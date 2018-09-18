//
// Created by user on 09.09.18.
//

#include <assert.h>
#include <array>
#include <limits>
#include "QuadraticEquationSolver.h"
#include "../LinearEquationSolver/LinearEquationSolver.h"

namespace QuadraticEquationSolver {

    std::array<double, 3> solve(double a, double b, double c) {
        if (isNotQuadratic(a, b, c)) {
            double lastLinearPresicion = LinearEquationSolver::getPresison();
            LinearEquationSolver::setPresicion(PRECISION);
            auto resultFromLinear = LinearEquationSolver::solve(b, c);
            LinearEquationSolver::setPresicion(lastLinearPresicion);
            return std::array<double, 3> {
                resultFromLinear[0],
                resultFromLinear[1],
                resultFromLinear[1]
            };
        } else {
            double discriminant = b * b - 4 * a * c;
            if (discriminant < -PRECISION) {
                return NO_ROOTS;
            } else {
                if (fabs(discriminant) <= PRECISION) {
                    return std::array<double, 3>    {
                        (-b + std::sqrt(discriminant)) / (2 * a),
                        std::numeric_limits<double>::max(),
                        std::numeric_limits<double>::max()
                    };
                } else {
                    return std::array<double, 3>{
                            (-b - std::sqrt(discriminant)) / (2 * a),
                            (-b + std::sqrt(discriminant)) / (2 * a),
                            std::numeric_limits<double>::max()
                    };
                }
            }
        }
    }

    bool isNotQuadratic(double a, double b, double c) {
        return fabs(a) <= PRECISION;
    }

    void setPresicion(double eps) {
        assert(eps >= 0);
        PRECISION = eps;
    }

    double getPresison() {
        return PRECISION;
    }

    double PRECISION = 1e-9;
    std::array<double, 3> NO_ROOTS = std::array<double, 3>    {
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min()
    };

    std::array<double, 3> INFINITY_ROOTS = std::array<double, 3>    {
            std::numeric_limits<double>::max(),
            std::numeric_limits<double>::max(),
            std::numeric_limits<double>::max()
    };

}