//
// Created by user on 16.09.18.
//

#ifndef STRINGSORTING_STRINGTOCOMPARE_H
#define STRINGSORTING_STRINGTOCOMPARE_H

#include <cstddef>

class StringSorted::StringToCompare {
private:
    const char *data;
    int increment;
    size_t firstElement;
    size_t lastElement;
    size_t currentElement;
public:
    StringToCompare(const char *data_, int increment_, size_t firstElement_, size_t lastElement_);

    bool isEmpty();

    bool hasNext();

    bool isNextSpecial();

    char next();

    void skipSpecial();
};
#endif //STRINGSORTING_STRINGTOCOMPARE_H
