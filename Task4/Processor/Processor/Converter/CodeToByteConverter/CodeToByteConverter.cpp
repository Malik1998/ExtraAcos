//
// Created by user on 14.10.18.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include "CodeToByteConverter.h"
#include "../../CommandService/CommandService.h"

namespace CodeToByteConverter {

    ErrorCode convert(char *program, char *filename) {

        std::map<int, int> labels = getLabels(program);
        std::ofstream myfile;
        myfile.open(filename, std::ios::binary | std::ios::out);
        size_t currentPosition = 0;
        size_t currentLine = 0;
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

            switch (command.first) {
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    currentPosition += pushPopString.second;
                    int length = static_cast<int>(pushPopString.first.length());
                    myfile.write(reinterpret_cast<const char *>(&length), sizeof(length));
                    myfile.write((pushPopString.first.c_str()), length);
                    break;
                }
                case CommandService::Command::jmp : {

                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    int labelPointer = static_cast<int>(labels[std::stoi(labelName.first)]);

                    myfile.write(reinterpret_cast<const char *>(&labelPointer), sizeof(labelPointer));
                    break;
                }
            }
            currentLine++;
        }
        myfile << "--- NO ENDING -----";
        myfile.close();
        return FAIL;
    }

    std::map<int, int>  getLabels(char* program) {
        std::map<int, int> labels;
        size_t currentPosition = 0;
        int pos = 0;
        int currentLine = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                break;
            }

            labels[currentLine] = pos;
            pos++;
            currentPosition += command.second;

            switch (command.first) {
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    pos += 4 + (int)(pushPopString.first.length());
                    currentPosition += pushPopString.second;
                    break;
                }
                case CommandService::Command::jmp : {

                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    pos += 4;
                    break;
                }
            }

            currentLine++;
        }

        return labels;
    }
}
