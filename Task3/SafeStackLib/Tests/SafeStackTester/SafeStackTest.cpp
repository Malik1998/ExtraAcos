//
// Created by user on 08.09.18.
//

#include "SafeStackTest.h"
#include "gtest/gtest.h"
#include "../../SafeStack/SafeStack.h"
#include "../../SafeStack/SafeStack.cpp"


TEST(SafeStackTest, FULL_NESS) {
    auto Stack = SafeStack<size_t >(-1);
    for (size_t i = 0; i < 10000000; i++) {
        auto error_code = Stack.push(i);
        if (error_code != SafeStack<size_t >::OK) {
#ifdef DEBUG
            ASSERT_EQ(SafeStack<size_t >::ErrorPush, error_code);
#endif
            break;
        }
    }
}

TEST(SafeStackTest, CHANGE_FIRST_BYTES) {
    auto Stack = SafeStack<size_t >(-1);
    ((int *)(&Stack))[0] = 0;
    for (size_t i = 0; i < 10000000; i++) {
        auto error_code = Stack.push(i);
        if (error_code != SafeStack<size_t >::OK) {
#ifdef DEBUG
            ASSERT_EQ(SafeStack<size_t >::ErroKanareika, error_code);
#endif
            break;
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}