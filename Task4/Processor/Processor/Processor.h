//
// Created by user on 13.10.18.
//

#ifndef PROCESSOR_PROCESSOR_H
#define PROCESSOR_PROCESSOR_H

#include "../../../Task3/SafeStackCStyle/SafeStack/SafeStack.cpp"

class Processor {
    SafeStack<int> stack;
    enum Command {
        push,
        pop,
        add,
        sub,
        multiply,
        div,
        in,
        out,
        end
    };

    enum AnswerFromServe {
        OK,
        READ,
        WRITE,
        END
    };

    AnswerFromServe serveCommand(Command command, int number);

};


#endif //PROCESSOR_PROCESSOR_H
