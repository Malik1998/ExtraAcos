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

    StringToCompare::StringToCompare(const char *data_, int increment_, size_t firstElement_, size_t lastElement_)
            : data(data_), increment(increment_), firstElement(firstElement_), lastElement(lastElement_),
              currentElement(firstElement_) {}

    bool StringToCompare::isEmpty() {
        return firstElement == lastElement;
    }

    bool StringToCompare::hasNext() {
        return currentElement != lastElement;
    }

    bool StringToCompare::isNextSpecial() {
        char b = static_cast<char>(tolower(data[currentElement]));
        return !(b >= 'a' && b <= 'z');
    }

    char StringToCompare::next() {
        char b = data[currentElement];
        currentElement += increment;
        return b;
    }

    void StringToCompare::skipSpecial() {
        while(hasNext()) {
            if (isNextSpecial()) {
                next();
            } else {
                break;
            }
        }
    }

    bool comparator(StringToCompare&& a, StringToCompare&& b) {
        if (a.isEmpty()) {
            return false;
        }
        if (b.isEmpty()) {
            return true;
        }
        while (a.hasNext() && b.hasNext()) {
            if (a.isNextSpecial() || b.isNextSpecial()) {
                if (a.isNextSpecial()) {
                    a.skipSpecial();
                }
                if (b.isNextSpecial()) {
                    b.skipSpecial();
                }
            } else {
                char aChar = static_cast<char>(tolower(a.next()));
                char bChar = static_cast<char>(tolower(b.next()));
                if (aChar != bChar) {
                    return aChar < bChar;
                }
            }
        }

        return a.hasNext();
    }

    void outputAscendingText(size_t *indexes, size_t countOfLines, char *text, const char *DistFileName) {
        std::sort(indexes, indexes + countOfLines, [&text] (size_t a, size_t b) {
            return comparator(StringToCompare(text + a, 1, 0, (strlen(text + a) == 0) ? 0 : strlen(text + a) - 1),
                              StringToCompare(text + b, 1, 0, (strlen(text + b) == 0) ? 0 : strlen(text + b) - 1));
        });
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_CREAT | O_WRONLY | O_TRUNC);
    }

    void outputAscendingFromEndText(size_t *indexes, size_t countOfLines, char *text, const char *DistFileName) {
        std::sort(indexes, indexes + countOfLines, [&text] (size_t a, size_t b) {
            return comparator(StringToCompare(text + a, -1, (strlen(text + a) == 0) ? 0 : strlen(text + a) - 1, 0),
                              StringToCompare(text + b, -1, (strlen(text + b) == 0) ? 0 : strlen(text + b) - 1, 0));
        });
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);
    }

    void outputNormalText(size_t *indexes, size_t countOfLines, char *text, const char *DistFileName) {
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);
    }

    void freeText(char *text, size_t* indexes, size_t countOfLines) {
        for (size_t i = 0; i < countOfLines; ++i) {
            if (indexes[i] != 0) {
                text[indexes[i] - 1] = '\n';
            }
        }
        free(text);
    }

    void sortMyFile(const char *SrcFileName, const char *DistFileName) {
        char* text = nullptr;
        FullFileReader::readFullFile(SrcFileName, &text);
        size_t * standardIndexes = nullptr;
        size_t countOfLines = FullFileReader::changeSlashesToNulles(text, &standardIndexes);

        auto *indexes = new size_t[countOfLines + 1];
        std::copy(standardIndexes, standardIndexes + countOfLines, indexes);

        outputAscendingText(indexes, countOfLines, text, DistFileName);

        outputAscendingFromEndText(indexes, countOfLines, text, DistFileName);

        outputNormalText(standardIndexes, countOfLines, text, DistFileName);

        freeText(text, standardIndexes, countOfLines);
        free(indexes);
        free(standardIndexes);
    }

}
