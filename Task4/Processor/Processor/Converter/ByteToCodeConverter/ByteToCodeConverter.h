//
// Created by user on 14.10.18.
//

#ifndef PROCESSOR_BYTETOCODECONVERTER_H
#define PROCESSOR_BYTETOCODECONVERTER_H


#include <cstddef>

namespace ByteToCodeConverter {
    enum ErrorCode {
        FAIL,
        OK
    };

    static const char* filename = "Byte.code";


    ErrorCode convert(char* program, char* filename_ = const_cast<char *>("Code.code"), size_t length = 0);
};


#endif //PROCESSOR_BYTETOCODECONVERTER_H
