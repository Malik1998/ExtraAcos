//
// Created by user on 09.09.18.
//

#include <assert.h>
#include <limits>
#include <cmath>
#include "LinearEquationSolver.h"

namespace LinearEquationSolver {
    std::array<double, 2> solve(double a, double b) {
        if (fabs(a) <= PRECISION && fabs(b) <= PRECISION) {
            return INFINITY_ROOTS;
        } else if (fabs(a) <= PRECISION) {
            return NO_ROOTS;
        } else {
            return std::array<double, 2>    {
                -b / a,
                std::numeric_limits<double>::max()
            };
        }
    }

    void setPresicion(double eps) {
        assert(eps >= 0);
        PRECISION = eps;
    }

    double getPresison() {
        return PRECISION;
    }

    double PRECISION = 1e-9;
    std::array<double, 2> NO_ROOTS = std::array<double, 2>    {
            std::numeric_limits<double>::min(),
            std::numeric_limits<double>::min(),
    };

    std::array<double, 2> INFINITY_ROOTS = std::array<double, 2>    {
            std::numeric_limits<double>::max(),
            std::numeric_limits<double>::max(),
    };
}