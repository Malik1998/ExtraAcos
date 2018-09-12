//
// Created by user on 08.09.18.
//

#include "QuadraticEquationSolverTest.h"
#include "gtest/gtest.h"
#include "../../common_libs/Result/Result.h"
#include "../../QuadraticEquationSolver/QuadraticEquationSolver.h"

//using namespace QuadraticEquationSolver;

TEST(QuadricQuationSolverTest, ONE_ROOT) {
    auto answers = QuadraticEquationSolver::solve(1, -2, 1); // x^2 - 2 * x + 1 = 0;
    ASSERT_EQ(answers.getTypeOfRoots(), Result::COUNTABLE);
    ASSERT_EQ(answers.getCount(), 1);
    ASSERT_EQ(answers.getRoots().size(), 1);
    ASSERT_EQ(*answers.getRoots().begin(), 1);
}

TEST(QuadricQuationSolverTest, TWO_ROOT) {
    using QuadraticEquationSolver::solve;

    auto answers = QuadraticEquationSolver::solve(1, 0, -1); // X^2 - 1= 0;
    ASSERT_EQ(answers.getTypeOfRoots(), Result::COUNTABLE);
    ASSERT_EQ(answers.getCount(), 2);
    ASSERT_EQ(answers.getRoots().size(), 2);
    ASSERT_EQ(*answers.getRoots().begin(), -1);
    ASSERT_EQ(*answers.getRoots().rbegin(), 1);
}

TEST(QuadricQuationSolverTest, NONE_ROOT) {
    using QuadraticEquationSolver::solve;

    auto answers = QuadraticEquationSolver::solve(-1, 0, -4); // - x^2  - 4= 0;
    ASSERT_EQ(answers.getTypeOfRoots(), Result::NONE);
    ASSERT_EQ(answers.getCount(), 0);
    ASSERT_EQ(answers.getRoots().size(), 0);
}

TEST(QuadricQuationSolverTest, INFINITY_ROOT) {
    using QuadraticEquationSolver::solve;

    auto answers = QuadraticEquationSolver::solve(0, 0, 0); //  0 * x = 0;
    ASSERT_EQ(answers.getTypeOfRoots(), Result::INFINITY_COUNT);
}

TEST(QuadricQuationSolverTest, NOT_QUADRIC) {
    using QuadraticEquationSolver::solve;

    auto answers = QuadraticEquationSolver::solve(0, 3, -1); // X^2 - 1= 0;
    ASSERT_EQ(answers.getTypeOfRoots(), Result::COUNTABLE);
    ASSERT_EQ(answers.getCount(), 1);
    ASSERT_EQ(answers.getRoots().size(), 1);
    ASSERT_DOUBLE_EQ(*answers.getRoots().begin(), 1. / 3 );
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}