//
// Created by user on 08.09.18.
//

#include "QuadraticEquationSolverTest.h"
#include "gtest/gtest.h"
#include "../../QuadraticEquationSolver/QuadraticEquationSolver.h"



TEST(QuadricQuationSolverTest, ONE_ROOT) {
    auto answers = QuadraticEquationSolver::solve(1, -2, 1); // x^2 - 2 * x + 1 = 0;
    ASSERT_DOUBLE_EQ(answers[0], 1);
}

TEST(QuadricQuationSolverTest, TWO_ROOT) {
    auto answers = QuadraticEquationSolver::solve(1, 0, -1); // X^2 - 1= 0;
    ASSERT_EQ(answers.size(), 3);
    ASSERT_DOUBLE_EQ(answers[0], -1);
    ASSERT_DOUBLE_EQ(answers[1], 1);
}

TEST(QuadricQuationSolverTest, NONE_ROOT) {
    auto answers = QuadraticEquationSolver::solve(-1, 0, -4); // - x^2  - 4= 0;
    ASSERT_DOUBLE_EQ(answers[0], std::numeric_limits<double>::min());
}

TEST(QuadricQuationSolverTest, INFINITY_ROOT) {
    auto answers = QuadraticEquationSolver::solve(0, 0, 0); //  0 * x = 0;
    ASSERT_DOUBLE_EQ(answers[0], std::numeric_limits<double>::max());
}

TEST(QuadricQuationSolverTest, NOT_QUADRIC) {
    using QuadraticEquationSolver::solve;

    auto answers = QuadraticEquationSolver::solve(0, 3, -1); // 3 * X - 1= 0;
    ASSERT_DOUBLE_EQ(answers[0], 1. / 3);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}