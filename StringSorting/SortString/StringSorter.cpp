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
    class StringToCompare {
    private:
        const char* data;
        int increment;
        size_t firstElement;
        size_t lastElement;
        size_t currentElement;
    public:
        explicit StringToCompare(const char *data_, int increment_, size_t firstElement_, size_t lastElement_)
                : data(data_), increment(increment_), firstElement(firstElement_), lastElement(lastElement_),
                  currentElement(firstElement_) {}

        bool isEmpty() {
            return firstElement == lastElement;
        }

        bool hasNext() {
            return currentElement != lastElement;
        }

        bool isNextSpecial() {
            char b = data[currentElement + increment];
            return !((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'));
        }

        char next() {
            char b = data[currentElement];
            currentElement += increment;
            return b;
        }

        void skipSpecial() {
            while(hasNext()) {
                if (isNextSpecial()) {
                    next();
                } else {
                    break;
                }
            }
        }
    };

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
                char aChar = a.next();
                char bChar = b.next();
                if (aChar != bChar) {
                    return aChar < bChar;
                }
            }
        }

        return a.hasNext();
    }

    void outputAscendingText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName) {
        std::sort(indexes, indexes + countOfLines, [&text] (size_t a, size_t b) {
            return comparator(StringToCompare(text + a, 1, 0, (strlen(text + a) == 0) ? 0 : strlen(text + a) - 1),
                              StringToCompare(text + b, 1, 0, (strlen(text + b) == 0) ? 0 : strlen(text + b) - 1));
        });
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_CREAT | O_WRONLY | O_TRUNC);
    }

    void outputAscendingFromEndText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName) {
        std::sort(indexes, indexes + countOfLines, [&text] (size_t a, size_t b) {
            return comparator(StringToCompare(text + a, -1, (strlen(text + a) == 0) ? 0 : strlen(text + a) - 1, 0),
                              StringToCompare(text + b, -1, (strlen(text + b) == 0) ? 0 : strlen(text + b) - 1, 0));
        });
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);
    }

    void outputNormalText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName) {
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);
    }

    void sortMyFile(char *SrcFileName, char *DistFileName) {
        char* text;
        FullFileReader::readFullFile(SrcFileName, &text);
        size_t * standardIndexes;
        size_t countOfLines = FullFileReader::changeSlashesToNulles(text, &standardIndexes);

        auto *indexes = new size_t[countOfLines + 1];
        std::copy(standardIndexes, standardIndexes + countOfLines, indexes);

        outputAscendingText(indexes, countOfLines, text, DistFileName);

        outputAscendingFromEndText(indexes, countOfLines, text, DistFileName);

        outputNormalText(standardIndexes, countOfLines, text, DistFileName);

    }

}
