//
// Created by user on 13.09.18.
//

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cwchar>
#include <iostream>
#include <fcntl.h>
#include "StringSorter.h"
#include "../ReadFullFile/FullFileReader.h"

namespace StringSorter {
    bool isSpecial(char i) {
        return !((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'));
    }
    bool comparator(const char* a,
                    const char* b,
                    size_t firstStart,
                    size_t secondStart,
                    int firstIncrement,
                    int secondIncrement,
                    size_t firstEnd,
                    size_t secondEnd) {
        // empty -> to the end
        if (firstEnd == firstStart) {
            return false;
        }
        if (secondEnd == secondStart) {
            return true;
        }
        while (firstEnd != firstStart && secondEnd != secondStart) {
            if (isSpecial(a[firstStart]) || isSpecial(b[secondStart])) {
                if (isSpecial(a[firstStart])) {
                    firstStart += firstIncrement;
                }
                if (isSpecial(b[secondStart])) {
                    secondStart += secondIncrement;
                }
            } else if (a[firstStart] != b[secondStart]) {
                return a[firstStart] < b[secondStart];
            } else {
                firstStart += firstIncrement;
                secondStart += secondIncrement;
            }
        }
        // if smaller -> less
        return firstEnd == firstStart;
    }

    void sortMyFile(char *SrcFileName, char *DistFileName) {
        char* text;
        FullFileReader::readFullFile(SrcFileName, &text);
        size_t * indexes;
        size_t countOfLines = FullFileReader::changeSlashesToNulles(text, &indexes);

        size_t *standartIndexes = new size_t[countOfLines + 1];
        std::copy(indexes, indexes + countOfLines, standartIndexes);

        std::sort(indexes, indexes + countOfLines, [&text] (size_t a, size_t b) {
            return comparator(text + a, text + b, 0, 0, 1, 1, (strlen(text + a) == 0) ? 0 : strlen(text + a) - 1,
                              (strlen(text + b) == 0) ? 0 : strlen(text + b) - 1);
        });

        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_CREAT | O_WRONLY | O_TRUNC);


        std::sort(indexes, indexes + countOfLines, [&text] (size_t a, size_t b) {
            return comparator(text + a, text + b, (strlen(text + a) == 0) ? 0 : strlen(text + a) - 1,
                              (strlen(text + b) == 0) ? 0 : strlen(text + b) - 1, -1, -1, 0, 0);
        });
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);


        FullFileReader::outputInFile(standartIndexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);

    }

}
