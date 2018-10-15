//
// Created by user on 13.10.18.
//

#include <ostream>
#include "cstring"
#include "WordToCodeConverter.h"
#define MAX_LINE_SIZE 256
#define FILE_NAME CODE_COMMANDS

WordToCodeConverter::ErrorCode WordToCodeConverter::convert(char *program, char *filename) {

    std::ofstream myfile;
    myfile.open(filename);
    size_t currentPosition = 0;
    while (currentPosition != std::strlen(program)) {
        auto command = std::make_pair(CommandService::Command::no_such_command, 0);
        command = CommandService::extractCommand(program + currentPosition);
        if (command.first == CommandService::Command::end ||
            command.first == CommandService::Command::no_such_command) {
            if (command.first == CommandService::Command::end) {
                myfile << static_cast<size_t>(command.first) << std::endl;
                myfile.close();
                return OK;
            } else {
                myfile << "---- UNKNOWN COMMAND --------" << std::endl;
                myfile.close();
                return FAIL;
            }
        }

        currentPosition += command.second;

        myfile << static_cast<size_t>(command.first);

        if (command.first == CommandService::Command::push) {
            int tempPosition = 0;
            int number = -1;
            if (sscanf(program + currentPosition, "%d%n", &number, &tempPosition) ) {
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
