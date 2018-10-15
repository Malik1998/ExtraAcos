//
// Created by user on 14.10.18.
//

#include <cstring>
#include "CommandService.h"
#define MAX_LENGTH 30

namespace CommandService {

    std::pair<Command, int> extractCommandWord(char *in) {
        char command[MAX_LENGTH];
        int position = 0;
        sscanf(in, "%s%n", command, &position);
        for (size_t i = 0; i < number_of_commands; i++) {
            if (std::strcmp(commands[i], command) == 0) {
                return std::make_pair(static_cast<Command>(i), position);
            }
        }
        return std::make_pair(static_cast<Command>(number_of_commands), -1);
    }

    std::pair<Command, int> extractCommandCode(char *in) {
        size_t command;
        int position = 0;
        sscanf(in, "%d%n", &command, &position);
        return std::make_pair(static_cast<Command>(command), position);
    }

    std::pair<Command, int> extractCommandByte(char *in) {
        char command = in[0];
        int position = 1;
        //sscanf(in, "%u%n", &command, &position);
        return std::make_pair(static_cast<Command>(command), position);
    }
}