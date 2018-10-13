//
// Created by user on 13.10.18.
//

#include "Processor.h"

Processor::AnswerFromServe Processor::serveCommand(Processor::Command command, int number = 0) {
    switch(command) {
        case push: {
            stack.push(number);
            return OK;
        }
        case pop: {
            stack.getFrontSafe();
            return OK;
        }
        case add: {
            int a = stack.getFrontSafe().first;
            stack.pop();
            int b = stack.getFrontSafe().first;
            stack.push(a + b);
            return OK;
        }
        case multiply: {
            int a = stack.getFrontSafe().first;
            stack.pop();
            int b = stack.getFrontSafe().first;
            stack.push(a * b);
            return OK;
        }
        case div: {
            int a = stack.getFrontSafe().first;
            stack.pop();
            int b = stack.getFrontSafe().first;
            stack.push(a / b);
            return OK;
        }
        case in: {
            return READ;
        }
        case out: {
            return WRITE;
        }
        case end: {
            return END;
        }
    }
}
