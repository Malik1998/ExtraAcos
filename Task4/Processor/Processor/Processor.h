//
// Created by user on 13.10.18.
//

#ifndef PROCESSOR_PROCESSOR_H
#define PROCESSOR_PROCESSOR_H

#include <iostream>
#include "SafeStack/SafeStack.h"
#include "CommandService/CommandService.h"

#define SIZE_OF_STACK 100

class Processor {
private:
    SafeStack<int> stack;
    char* programm;
    size_t sizeOfProgram;
    std::istream& cin;
    std::ostream& cout;
    int rax, rbx, rcx, rdx;

    static const int RAM_SIZE = 1024;
    int ram[RAM_SIZE];

public:
    enum TypeOfProgram {
        BYTECODE,
        DECODED_COMMANDS,
        WORD_COMMANDS
    };

    enum AnswerFromServe {
        OK,
        READ,
        WRITE,
        END
    };

   // ProcessorTest(std::istream& in, TypeOfProgram typeOfProgram);
    Processor(char* filename, TypeOfProgram typeOfProgram, std::istream& in = std::cin, std::ostream& out = std::cout);
    void execute();

private:
    void conditionalJump(size_t *i, CommandService::Command command);
    int getNumber(char *string);
};


#endif //PROCESSOR_PROCESSOR_H
