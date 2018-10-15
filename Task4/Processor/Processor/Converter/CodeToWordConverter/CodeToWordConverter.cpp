//
// Created by user on 14.10.18.
//

#include <cstdio>
#include <fstream>
#include <cstring>
#include "CodeToWordConverter.h"
#include "../../CommandService/CommandService.h"


namespace CodeToWordConverter {
using namespace CommandService;

    ErrorCode convert(char *program, char *filename) {
        std::ofstream myfile;
        myfile.open(filename);
        size_t currentPosition = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {
                    myfile << commands[static_cast<size_t>(command.first)] << std::endl;
                    myfile.close();
                    return OK;
                } else {
                    myfile << "---- UNKNOWN COMMAND --------" << std::endl;
                    myfile.close();
                    return FAIL;
                }
            }

            currentPosition += command.second;

            myfile << commands[static_cast<size_t>(command.first)];

            if (command.first == CommandService::Command::push) {
                int tempPosition = 0;
                int number = -1;
                if (sscanf(program + currentPosition, "%d%n", &number, &tempPosition)) {
                    currentPosition += tempPosition;
                    myfile << " " << number;
                } else {
                    myfile << "---- Nothing to push --------" << std::endl;
                    myfile.close();
                    return FAIL;
                }
            }

            myfile << std::endl;

        }
        myfile << "--- NO ENDING -----" << std::endl;
        myfile.close();
        return FAIL;
    }
};