//
// Created by user on 08.09.18.
//

#include "SafeStackTest.h"
#include "gtest/gtest.h"
#include "../../SafeStack/SafeStack.h"
#include "../../SafeStack/SafeStack.cpp"


TEST(SafeStackTest, FULL_NESS) {
    auto Stack = SafeStack<int>(-1);
    for (size_t i = 0; i < 10000000; i++) {
        auto error_code = Stack.push(i);
        if (error_code != SafeStack<int>::OK) {
            ASSERT_EQ(SafeStack<int>::ErrorPush, error_code);
            break;
        }
    }
}

TEST(SafeStackTest, CHANGE_FIRST_BYTES) {
    auto Stack = SafeStack<int>(-1);
    ((int *)(&Stack))[0] = 0;
    for (size_t i = 0; i < 10000000; i++) {
        auto error_code = Stack.push(i);
        if (error_code != SafeStack<int>::OK) {
            ASSERT_EQ(SafeStack<int>::ErroKanareika, error_code);
            break;
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}