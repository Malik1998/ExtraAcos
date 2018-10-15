//
// Created by user on 14.10.18.
//

#ifndef PROCESSOR_CODETOWORDCONVERTER_H
#define PROCESSOR_CODETOWORDCONVERTER_H


namespace CodeToWordConverter {
    enum ErrorCode {
        FAIL,
        OK
    };

    ErrorCode convert(char* program, char* filename = (char *)"WordProgram.code");

};


#endif //PROCESSOR_CODETOWORDCONVERTER_H
