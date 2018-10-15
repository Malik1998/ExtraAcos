//
// Created by user on 14.10.18.
//

#include "ByteToCodeConverter.h"

#include <fstream>
#include <cstring>
#include "../../CommandService/CommandService.h"

namespace ByteToCodeConverter {

    ErrorCode convert(char *program, char *filename) {

        std::ofstream myfile;
        myfile.open(filename, std::ios::binary | std::ios::out);
        size_t currentPosition = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
            char encodedCommand = static_cast<char>(command.first);
            myfile.write(&encodedCommand, sizeof(encodedCommand));
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
                int tempPosition = 0;
                int number = -1;
                if (sscanf(program + currentPosition, "%d%n", &number, &tempPosition)) {
                    currentPosition += tempPosition;
                    myfile.write(reinterpret_cast<const char *>(&number), sizeof(number));
                } else {
                    myfile << "---- Nothing to push --------";
                    myfile.close();
                    return FAIL;
                }
            }


        }
        myfile << "--- NO ENDING -----";
        myfile.close();
        return FAIL;
    }
}
