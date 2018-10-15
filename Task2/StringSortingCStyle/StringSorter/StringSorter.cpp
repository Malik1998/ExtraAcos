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
#include "../FullFileReader/FullFileReader.h"

namespace StringSorter {
    bool isSpecial(char i) {
        return !(tolower(i) >= 'a' && tolower(i) <= 'z');
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
            } else if (tolower(a[firstStart]) != tolower(b[secondStart])) {
                return tolower(a[firstStart]) < tolower(b[secondStart]);
            } else {
                firstStart += firstIncrement;
                secondStart += secondIncrement;
            }
        }
        // if smaller -> less
        return firstEnd != firstStart;
    }

    void freeText(char *text, char ** indexes, size_t countOfLines) {
        for (size_t i = 0; i < countOfLines; ++i) {
            if (indexes[i] != text) {
                (indexes[i] - 1)[0] = '\n';
            }
        }
        free(text);
    }

    void sortMyFile(const char *SrcFileName, const char *DistFileName) {
        char* text = nullptr;
        FullFileReader::readFullFile(SrcFileName, &text);

        char ** standartIndexes = nullptr;
        size_t countOfLines = FullFileReader::changeSlashesToNulles(text, &standartIndexes);

        char **indexes = new char*[countOfLines + 1];
        std::copy(standartIndexes, standartIndexes + countOfLines, indexes);

        std::sort(indexes, indexes + countOfLines, [] (char *a, char *b) {
            return comparator(a, b, 0, 0, 1, 1, (strlen(a) == 0) ? 0 : strlen(a) - 1,
                              (strlen(b) == 0) ? 0 : strlen(b) - 1);
        });

        FullFileReader::outputInFile(indexes, DistFileName, countOfLines, O_CREAT | O_WRONLY | O_TRUNC);


        std::sort(indexes, indexes + countOfLines, [] (char *a, char *b) {
            return comparator(a, b, (strlen(a) == 0) ? 0 : strlen(a) - 1,
                              (strlen(b) == 0) ? 0 : strlen(b) - 1,
                              -1, -1, 0, 0);
        });

        FullFileReader::outputInFile(indexes, DistFileName, countOfLines, O_WRONLY | O_APPEND);

        FullFileReader::outputInFile(standartIndexes, DistFileName, countOfLines, O_WRONLY | O_APPEND);


        freeText(text, indexes, countOfLines);
        free(standartIndexes);
        free(indexes);
    }


}
