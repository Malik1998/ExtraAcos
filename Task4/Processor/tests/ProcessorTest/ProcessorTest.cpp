//
// Created by user on 08.09.18.
//

#include <fcntl.h>
#include "ProcessorTest.h"
#include "gtest/gtest.h"
#include "../../Processor/Processor.h"
#include "iostream"
#include "../../Processor/Converter/WordToCodeConverter/WordToCodeConverter.h"
#include "../../Processor/Converter/CodeToByteConverter/CodeToByteConverter.h"
#include "../../Processor/FullFileReader/ReadFullFile/FullFileReader.h"
#include "../../Processor/Converter/ByteToCodeConverter/ByteToCodeConverter.h"
#include "../../Processor/Converter/CodeToWordConverter/CodeToWordConverter.h"

TEST(ProcessorTest, Factorial1) {
    std::stringstream in((char *)"1"); // (x - 8) * (x + 4)
    Processor processor = Processor("Factorial", Processor::WORD_COMMANDS, in);
    processor.execute();
}


TEST(ProcessorTest, SimpleTestOfAllComponentsWorkingAddPopPushInOut1) {
    std::stringstream in((char *)"5");
    std::stringstream out;
    Processor processor = Processor("CommandCode.txt", Processor::WORD_COMMANDS, in, out);
    processor.execute();
    int number = -3;
    out >> number;
    ASSERT_EQ(number, 112005);
}

TEST(ProcessorTest, SimpleTestOfAllComponentsWorkingAddPopPushInOut2) {
    std::stringstream in((char *)"8");
    std::stringstream out;
    Processor processor = Processor("CommandCode.txt", Processor::WORD_COMMANDS, in, out);
    processor.execute();
    int number = -3;
    out >> number;
    ASSERT_EQ(number, 112008);
}

TEST(ProcessorTest, ConverterCheck) {
    char* program2 = "push 2\n"
                    "pop\n"
                    "push 1\n"
                    "push 111999\n"
                    "add\n"
                    "in\n"
                    "add\n"
                    "out\n"
                    "end";
    char *program;
    WordToCodeConverter::convert(program2, (char *)"CODE_TEST_DIRECT");
    FullFileReader::readFullFile((char *)"CODE_TEST_DIRECT", &program);

    CodeToByteConverter::convert(program, (char *)"BYTE_TEST_DIRECT");
    delete[] program;
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT", &program);

    int fileDescriptor = open("BYTE_TEST_DIRECT", O_RDONLY);
    struct stat st;
    fstat(fileDescriptor, &st);
    auto fullTextSize = static_cast<size_t>(st.st_size);
    close(fileDescriptor);

    ByteToCodeConverter::convert(program, (char *)"CODE_TEST_UNDIRECT", fullTextSize);
    delete[] program;
    FullFileReader::readFullFile((char *)"CODE_TEST_UNDIRECT", &program);


    CodeToWordConverter::convert(program, (char *)"WORD_TEST_UNDIRECT");
    delete[] program;
    FullFileReader::readFullFile((char *)"WORD_TEST_UNDIRECT", &program);


    for (int i = 0; i < strlen(program2); i++) {
        ASSERT_EQ(program[i], program2[i]);
    }
}

TEST(ProcessorTest, JMP_PUSH_POP_TEST_CODE) {
    char* program2 = "push 2\n"
                     "push 1\n"
                     "push 111999\n"
                     "add\n"
                     "push rax\n"
                     "push rbx\n"
                     "push [100]\n"
                     "my_label:\n"
                     "in\n"
                     "add\n"
                     "out\n"
                     "jmp my_label\n"
                     "end";
    char *program;
    WordToCodeConverter::convert(program2, (char *)"CODE_TEST_DIRECT_JMP_PUSH");
}

TEST(ProcessorTest, JMP_PUSH_POP_TEST_BYTE) {
    char* program2 = "push 2\n"
                     "push 1\n"
                     "push 111999\n"
                     "add\n"
                     "push rax\n"
                     "push rbx\n"
                     "push [100]\n"
                     "my_label:\n"
                     "in\n"
                     "add\n"
                     "out\n"
                     "jmp my_label\n"
                     "end";
    char *program;
    WordToCodeConverter::convert(program2, (char *)"CODE_TEST_BYTEJMP");
    FullFileReader::readFullFile((char *)"CODE_TEST_BYTEJMP", &program);
    program2 = program;
    CodeToByteConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP");
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP", &program);

//    int fileDescriptor = open("BYTE_TEST_DIRECT__BYTEJMP", O_RDONLY);
//    struct stat st;
//    fstat(fileDescriptor, &st);
//    auto fullTextSize = static_cast<size_t>(st.st_size);
//    close(fileDescriptor);
//
//    ByteToCodeConverter::convert(program, (char *)"CODE_TEST_UNDIRECT_BYTEJMP", fullTextSize);
//    delete[] program;
//    FullFileReader::readFullFile((char *)"CODE_TEST_UNDIRECT_BYTEJMP", &program);
//
//    for (int i = 0; i < strlen(program2); i++) {
//        ASSERT_EQ(program[i], program2[i]);
//    }

}


TEST(ProcessorTest, JMP_PUSH_POP_TEST_BYTE_TO_CODE) {
    char* program2 = "push 2\n"
                     "push 1\n"
                     "push 111999\n"
                     "add\n"
                     "push rax\n"
                     "push rbx\n"
                     "push [100]\n"
                     "my_label:\n"
                     "in\n"
                     "add\n"
                     "out\n"
                     "jmp my_label\n"
                     "end";
    char *program;
    WordToCodeConverter::convert(program2, (char *)"CODE_TEST_BYTEJMP");
    FullFileReader::readFullFile((char *)"CODE_TEST_BYTEJMP", &program);
    program2 = program;
    CodeToByteConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP");
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP", &program);

    int fileDescriptor = open("BYTE_TEST_DIRECT__BYTEJMP", O_RDONLY);
    struct stat st;
    fstat(fileDescriptor, &st);
    auto fullTextSize = static_cast<size_t>(st.st_size);
    close(fileDescriptor);

    ByteToCodeConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", fullTextSize);
    delete[] program;
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", &program);

    for (int i = 0; i < strlen(program2); i++) {
        ASSERT_EQ(program[i], program2[i]);
    }

    delete[] program;

}

TEST(ProcessorTest, Look_AT_WORDS) {
    char* program2 = "push 2\n"
                     "jmp another_label\n"
                     "push 1\n"
                     "push 111999\n"
                     "another_label:\n"
                     "add\n"
                     "push rax\n"
                     "push rbx\n"
                     "push [100]\n"
                     "my_label:\n"
                     "in\n"
                     "add\n"
                     "out\n"
                     "jmp my_label\n"
                     "end";
    char *program;
    WordToCodeConverter::convert(program2, (char *)"CODE_TEST_BYTEJMP");
    FullFileReader::readFullFile((char *)"CODE_TEST_BYTEJMP", &program);
    CodeToByteConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP");
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP", &program);

    int fileDescriptor = open("BYTE_TEST_DIRECT__BYTEJMP", O_RDONLY);
    struct stat st;
    fstat(fileDescriptor, &st);
    auto fullTextSize = static_cast<size_t>(st.st_size);
    close(fileDescriptor);

    ByteToCodeConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", fullTextSize);
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", &program);

    CodeToWordConverter::convert(program, (char *)"Hard_program_word");
    FullFileReader::readFullFile((char *)"Hard_program_word", &program);

    std::cout << program2 << std::endl  << std::endl;
    std::cout << program << std::endl;


    delete[] program;

}

TEST(ProcessorTest, Look_AT_WORDS2) {
    char* program2 = "push 5\n"
                     "v:\n"
                     "push 3\n"
                     "ja d\n"
                     "push 2\n"
                     "out\n"
                     "push 1\n"
                     "jmp v\n"
                     "d:\n"
                     "out\n"
                     "end";
                     "end";
    char *program;
    WordToCodeConverter::convert(program2, (char *)"CODE_TEST_BYTEJMP");
    FullFileReader::readFullFile((char *)"CODE_TEST_BYTEJMP", &program);
    CodeToByteConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP");
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP", &program);

    int fileDescriptor = open("BYTE_TEST_DIRECT__BYTEJMP", O_RDONLY);
    struct stat st;
    fstat(fileDescriptor, &st);
    auto fullTextSize = static_cast<size_t>(st.st_size);
    close(fileDescriptor);

    ByteToCodeConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", fullTextSize);
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", &program);

    CodeToWordConverter::convert(program, (char *)"Hard_program_word");
    FullFileReader::readFullFile((char *)"Hard_program_word", &program);

    std::cout << program2 << std::endl  << std::endl;
    std::cout << program << std::endl;


    delete[] program;

}


TEST(ProcessorTest, SimpleTestOfAllComponentsWorkingAddPopPushInOutJUMP2) {
    Processor processor = Processor("CommandCodeJump", Processor::WORD_COMMANDS);
    processor.execute();
}

TEST(ProcessorTest, QuadricQuatationSolver1) {
    std::stringstream in((char *)"1 -1 -6"); // (x - 3) * (x + 2)
    Processor processor = Processor("QuatationSolver", Processor::WORD_COMMANDS, in);
    processor.execute();
}

TEST(ProcessorTest, QuadricQuatationSolver2) {
    std::stringstream in((char *)"1 -6 9"); // (x - 3) ^ 2
    Processor processor = Processor("QuatationSolver", Processor::WORD_COMMANDS, in);
    processor.execute();
}

TEST(ProcessorTest, QuadricQuatationSolver3) {
    std::stringstream in((char *)"1 -4 -32"); // (x - 8) * (x + 4)
    Processor processor = Processor("QuatationSolver", Processor::WORD_COMMANDS, in);
    processor.execute();
}

TEST(ProcessorTest, Factorial1Test) {
    char* program2;
    FullFileReader::readFullFile((char *)"Factorial", &program2);

    char *program;
    WordToCodeConverter::convert(program2, (char *)"CODE_TEST_BYTEJMP");
    FullFileReader::readFullFile((char *)"CODE_TEST_BYTEJMP", &program);
    CodeToByteConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP");
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP", &program);

    int fileDescriptor = open("BYTE_TEST_DIRECT__BYTEJMP", O_RDONLY);
    struct stat st;
    fstat(fileDescriptor, &st);
    auto fullTextSize = static_cast<size_t>(st.st_size);
    close(fileDescriptor);

    ByteToCodeConverter::convert(program, (char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", fullTextSize);
    FullFileReader::readFullFile((char *)"BYTE_TEST_DIRECT__BYTEJMP_CODE", &program);

    CodeToWordConverter::convert(program, (char *)"Hard_program_word");
    FullFileReader::readFullFile((char *)"Hard_program_word", &program);

    std::cout << program2 << std::endl  << std::endl;
    std::cout << program << std::endl;


    delete[] program;
}


TEST(ProcessorTest, Factorial2) {
    std::stringstream in((char *)"5"); // (x - 8) * (x + 4)
    Processor processor = Processor("Factorial", Processor::WORD_COMMANDS, in);
    processor.execute();
}

TEST(ProcessorTest, Factorial3) {
    std::stringstream in((char *)"10"); // (x - 8) * (x + 4)
    Processor processor = Processor("Factorial", Processor::WORD_COMMANDS, in);
    processor.execute();
}

TEST(ProcessorTest, Factorial4) {
    std::stringstream in((char *)"11"); // (x - 8) * (x + 4)
    Processor processor = Processor("Factorial", Processor::WORD_COMMANDS, in);
    processor.execute();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}