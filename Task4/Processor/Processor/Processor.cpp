//
// Created by user on 13.10.18.
//

#include <cstring>
#include "Processor.h"
#include "FullFileReader/ReadFullFile/FullFileReader.h"
#include "Converter/WordToCodeConverter/WordToCodeConverter.h"
#include "Converter/CodeToByteConverter/CodeToByteConverter.h"

//#ifdef DEBUG
//
//#define READ_NUMBER std::cin>>number;
//
//#else
//
//#define READ_NUMBER  std::cin>>number;
////scanf("%d", &number);
//
//#endif

using namespace CommandService;
Processor::Processor(char *filename, Processor::TypeOfProgram typeOfProgram,
        std::istream& in, std::ostream& out) : stack(-1),
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

//    for(int i = 0; i < sizeOfProgram; i++) {
//        std::cout << std::oct << int(programm[i]) << "\n";
//    }

}

void Processor::execute() {

    for (size_t i = 0; i < sizeOfProgram; ) {
        auto command = extractCommandByte(programm + i);
        i += command.second;

        if (command.first == CommandService::Command::end ||
            command.first == CommandService::Command::no_such_command) {
            return;
        }

        switch (command.first) {
            case CommandService::Command::push : {
                int number = getNumber(programm + i);
                i += 4;
                stack.push(number);
                break;
            }
            case CommandService::Command::pop : {
                stack.pop();
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
        }

    }

}

int Processor::getNumber(char *string) {
    return int((unsigned char)(string[0]) |
                (unsigned char)(string[1]) << 8 |
                (unsigned char)(string[2]) << 16 |
                (unsigned char)(string[3]) << 24);
}


//ProcessorTest::ProcessorTest(std::istream &in, ProcessorTest::TypeOfProgram typeOfProgram): stack(-1) {
//
//}
