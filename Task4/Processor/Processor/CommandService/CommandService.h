//
// Created by user on 14.10.18.
//

#ifndef PROCESSOR_COMMANDSERVICE_H
#define PROCESSOR_COMMANDSERVICE_H


#include <iosfwd>
#include <string>



namespace CommandService {

    static const size_t number_of_commands = 10;

    enum Command {
        push = 0,
        pop = 1,
        add = 2,
        sub = 3,
        multiply = 4,
        divi = 5,
        in = 6,
        out = 7,
        end = 8,
        no_such_command = 9
    };

    static const char* commands[number_of_commands] = {
            "push",
            "pop",
            "add",
            "sub",
            "multiply",
            "div",
            "in",
            "out",
            "end",
            "no_such_command"
    };

    std::pair<Command, int> extractCommandWord(char *in);
    std::pair<Command, int> extractCommandCode(char *in);
    std::pair<Command, int> extractCommandByte(char *in);
};


#endif //PROCESSOR_COMMANDSERVICE_H
