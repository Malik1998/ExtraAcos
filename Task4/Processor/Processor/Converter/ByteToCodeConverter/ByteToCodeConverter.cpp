//
// Created by user on 14.10.18.
//

#include "ByteToCodeConverter.h"

#include <fstream>
#include <cstring>
#include "../../CommandService/CommandService.h"

namespace ByteToCodeConverter {

    ErrorCode convert(char *program, char *filename, size_t length) {

        std::ofstream myfile;
        myfile.open(filename);
        size_t currentPosition = 0;
        while (currentPosition < length) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandByte(program + currentPosition);
            myfile << command.first;
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {
                    myfile.close();
                    return OK;
                } else {
                    myfile << "---- UNKNOWN COMMAND --------";
                    myfile.close();
                    return FAIL;
                }
            }

            currentPosition += command.second;


            if (command.first == CommandService::Command::push) {

                if (currentPosition + 4 < length) {
                    int number = int((unsigned char)(program[currentPosition]) |
                                     (unsigned char)(program[currentPosition + 1]) << 8 |
                                     (unsigned char)(program[currentPosition + 2]) << 16 |
                                     (unsigned char)(program[currentPosition + 3]) << 24);
                    currentPosition += 4;
                    myfile << " " << number;
                } else {
                    myfile << "---- Nothing to push --------";
                    myfile.close();
                    return FAIL;
                }
            }

            myfile << std::endl;


        }
        myfile << "--- NO ENDING -----";
        myfile.close();
        return FAIL;
    }
}
