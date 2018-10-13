//
// Created by user on 13.10.18.
//

#ifndef PROCESSOR_WORDTOCODECONVERTER_H
#define PROCESSOR_WORDTOCODECONVERTER_H


#include <fstream>

class WordToCodeConverter {

    enum ErrorCode {
        FAIL,
        OK
    };

    ErrorCode convert(std::ifstream& in);

};


#endif //PROCESSOR_WORDTOCODECONVERTER_H
