//
// Created by user on 08.09.18.
//

#include "ProcessorTest.h"
#include "gtest/gtest.h"
#include "../../Processor/Processor.h"
#include "iostream"

TEST(ProcessorTest, SimpleTestOfAllComponentsWorkingAddPopPushInOut) {
    std::stringstream in((char *)"5");
    std::stringstream out;
    Processor processor = Processor("CommandCode.txt", Processor::WORD_COMMANDS, in, out);
    processor.execute();
    int number = -3;
    out >> number;
    ASSERT_EQ(number, 112005);
}

TEST(ProcessorTest, CHANGE_FIRST_BYTES) {
    std::stringstream in((char *)"8");
    std::stringstream out;
    Processor processor = Processor("CommandCode.txt", Processor::WORD_COMMANDS, in, out);
    processor.execute();
    int number = -3;
    out >> number;
    ASSERT_EQ(number, 112008);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}