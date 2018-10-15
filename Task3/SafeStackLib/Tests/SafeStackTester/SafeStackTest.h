//
// Created by user on 08.09.18.
//

#ifndef SAFESTACK_SAFESTACKTEST_H
#define SAFESTACK_SAFESTACKTEST_H
#define DEBUG
#include <gtest/gtest.h>

class SafeStackTest : public ::testing::Test {
public:
    SafeStackTest() { /* init protected members here */ };
    ~SafeStackTest() { /* free protected members here */ };
    void SetUp() { /* called before every test */ };
    void TearDown() { /* called after every test */ };
};


#endif //SAFESTACK_SAFESTACKTEST_H
