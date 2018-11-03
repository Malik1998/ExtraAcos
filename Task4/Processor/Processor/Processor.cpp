//
// Created by user on 13.10.18.
//

#include <cstring>
#include <cmath>
#include "Processor.h"
#include "FullFileReader/ReadFullFile/FullFileReader.h"
#include "Converter/WordToCodeConverter/WordToCodeConverter.h"
#include "Converter/CodeToByteConverter/CodeToByteConverter.h"

using namespace CommandService;
Processor::Processor(char *filename, Processor::TypeOfProgram typeOfProgram,
        std::istream& in, std::ostream& out) : stack(-1), stackOfCalls(-1),
        cin(in), cout(out)
        {
    switch (typeOfProgram) {
        case WORD_COMMANDS : {
            char* prog_code = nullptr;
            FullFileReader::readFullFile(filename, &prog_code);
            WordToCodeConverter::convert(prog_code);
            filename = const_cast<char *>(WordToCodeConverter::filename);
            typeOfProgram = DECODED_COMMANDS;
            delete[] prog_code;
        }
        case DECODED_COMMANDS: {
            char* prog_code = nullptr;
            FullFileReader::readFullFile(filename, &prog_code);
            CodeToByteConverter::convert(prog_code);
            filename = const_cast<char *>(CodeToByteConverter::filename);
            typeOfProgram = BYTECODE;
            delete[] prog_code;
        }
        case BYTECODE: {
            sizeOfProgram = FullFileReader::readFullFile(filename, &programm);
        }
    }

}

void Processor::execute() {
size_t count_line = 0;
    for (size_t i = 0; i < sizeOfProgram; ) {
        auto command = extractCommandByte(programm + i);
        i += command.second;
count_line++;
        if (command.first == CommandService::Command::end ||
            command.first == CommandService::Command::no_such_command) {
            return;
        }
        switch (command.first) {
            case CommandService::Command::push : {
                int length = getNumber(programm + i);
                i += 4;
                auto typeOfMemory = CommandService::getTypeOfMemory(programm + i);
                i += typeOfMemory.second;

                switch (typeOfMemory.first) {
                    case RAM: {
                        int number = getNumberChar(programm + i, length - 2);
                        i = i - typeOfMemory.second + length;
                        stack.push(ram[number]);
                        break;
                    }
                    case STACK: {
                        int number = getNumberChar(programm + i, length);
                        i += length;
                        stack.push(number);
                        break;
                    }
                    default: {
                        switch (typeOfMemory.first) {
                            case RAX: {
                                stack.push(rax);
                                break;
                            }
                            case RBX: {
                                stack.push(rbx);
                                break;
                            }
                            case RCX: {
                                stack.push(rcx);
                                break;
                            }
                            case RDX: {
                                stack.push(rdx);
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case CommandService::Command::pop : {
                int a = stack.getFrontUnsafe();
                stack.pop();
                int length = getNumber(programm + i);
                i += 4;
                auto typeOfMemory = CommandService::getTypeOfMemory(programm + i);
                i += typeOfMemory.second;
                switch (typeOfMemory.first) {
                    case RAM: {
                        int number = getNumberChar(programm + i, length - 2);
                        i = i - typeOfMemory.second + length;
                        ram[number] = a;
                        break;
                    }
                    case STACK: {
                        // DEPRECATED
                        break;
                    }
                    default: {
                        switch (typeOfMemory.first) {
                            case RAX: {
                                rax = a;
                                break;
                            }
                            case RBX: {
                                rbx = a;
                                break;
                            }
                            case RCX: {
                                rcx = a;
                                break;
                            }
                            case RDX: {
                                rdx = a;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case CommandService::Command::sub : {
                int a = stack.getFrontSafe().first;
                stack.pop();
                int b = stack.getFrontSafe().first;
                stack.pop();
                stack.push(a - b);
                break;
            }
            case CommandService::Command::multiply : {
                int a = stack.getFrontSafe().first;
                stack.pop();
                int b = stack.getFrontSafe().first;
                stack.pop();
                stack.push(a * b);
                break;
            }
            case CommandService::Command::divi : {
                int a = stack.getFrontSafe().first;
                stack.pop();
                int b = stack.getFrontSafe().first;
                stack.pop();
                stack.push(a / b);
                break;
            }
            case CommandService::Command::add : {
                int a = stack.getFrontSafe().first;
                stack.pop();
                int b = stack.getFrontSafe().first;
                stack.pop();
                stack.push(a + b);
                break;
            }
            case CommandService::Command::sqrt: {
                int a = stack.getFrontUnsafe();
                stack.pop();
                stack.push(static_cast<int>(std::sqrt(a)));
                break;
            }
            case CommandService::Command::in : {
                int number = 0;
                //scanf("%*s %d", &number);
                cin >> number;
                stack.push(number);
                break;
            }
            case CommandService::Command::out : {
                SafeStack<int>::ErrorCodes errorCode;
                do {
                    auto element = stack.getFrontSafe();
                    errorCode = element.second;
                    if (errorCode == SafeStack<int>::ErrorCodes::OK) {
                        cout << element.first << std::endl;
                    }
                    stack.pop();
                } while(errorCode == SafeStack<int>::ErrorCodes::OK);
                break;
            }
            case CommandService::jmp : {
                auto number = static_cast<int>(getNumber(programm + i));
                i = static_cast<size_t>(number);
                break;
            }
            case CommandService::ja : {
                conditionalJump(&i, CommandService::ja);
                break;
            }
            case CommandService::je : {
                conditionalJump(&i, CommandService::je);
                break;
            }
            case CommandService::Command::call : {
                auto number = static_cast<int>(getNumber(programm + i));
                stackOfCalls.push(static_cast<int>(i + 4));
                i = static_cast<size_t>(number);
                break;
            }
            case CommandService::Command::ret : {
                auto b = stackOfCalls.getFrontUnsafe();
                stackOfCalls.pop();
                i = static_cast<size_t>(b);
            }
        }

    }

}



int Processor::getNumber(char *string) {
    return int((unsigned char)(string[0]) |
                (unsigned char)(string[1]) << 8 |
                (unsigned char)(string[2]) << 16 |
                (unsigned char)(string[3]) << 24);
}

int Processor::getNumberChar(char *string, int length) {

    int number = 0;
    for (int i = 0; i < length; i++) {
        number = number * 10 + (string[i] - '0');
    }
    return number;
}

void Processor::conditionalJump(size_t *i, CommandService::Command command) {
    auto number = static_cast<size_t>(getNumber(programm + *i));
    int fir = stack.getFrontSafe().first;
    stack.pop();
    int sec = stack.getFrontSafe().first;
    stack.push(fir);

    bool toJump  = false;

    switch (command) {
        case ja: {
            if (fir > sec) {
                toJump = true;
            }
            break;
        }
        case je: {
            if (fir == sec) {
                toJump = true;
            }
            break;
        }
    }

    if (toJump) {
        (*i) = number;
    } else {
        (*i) += 4;
    }
}


//ProcessorTest::ProcessorTest(std::istream &in, ProcessorTest::TypeOfProgram typeOfProgram): stack(-1) {
//
//}
