//
// Created by user on 13.10.18.
//

#ifndef PROCESSOR_WORDTOCODECONVERTER_H
#define PROCESSOR_WORDTOCODECONVERTER_H


#include <fstream>
#include "../CommandService/CommandService.h"

class WordToCodeConverter {

    enum ErrorCode {
        FAIL,
        OK
    };

public:
    ErrorCode convert(char* program, char* filename = (char *)"CodeProgram.code");

};


#endif //PROCESSOR_WORDTOCODECONVERTER_H
