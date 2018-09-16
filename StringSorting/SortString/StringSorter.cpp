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
    bool isSpecial(char i);

    void sortMyFile(char *SrcFileName, char *DistFileName) {
        char* text;
        FullFileReader::readFullFile(SrcFileName, &text);
        size_t * indexes;
        size_t countOfLines = FullFileReader::changeSlashesToNulles(text, &indexes);

        std::sort(indexes, indexes + countOfLines, [indexes, &text] (size_t a, size_t b) {
            if (text[a] == '\0' || text[b] == '\0') {
                return text[a] != '\0'; // Empty lines at the end)
            }
            size_t i = strlen(text + a) - 1;
            size_t j = strlen(text + b) - 1;
            while (i >= 0 && j >= 0) {
                if (isSpecial(text[a + i]) || isSpecial(text[b + j])) {
                    if (isSpecial(text[a + i])) {
                        if (i == 0) {
                            return true;
                        }
                        i--;
                    }
                    if (isSpecial(text[b + j])) {
                        if (j == 0) {
                            return false;
                        }
                        j--;
                    }
                } else if (text[a + i] != text[b + j]) {
                    return text[a + i] < text[b + j];
                } else {
                    if (i == 0 || j == 0) {
                        if (i == 0) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                    i--, j--;
                }
            }
            return true;
        });

        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_CREAT | O_WRONLY);
        std::sort(indexes, indexes + countOfLines, [indexes, &text] (size_t a, size_t b) {
            if (text[a] == '\0' || text[b] == '\0') {
                return text[a] != '\0'; // Empty lines at the end)
            }
            for (size_t i = 0, j = 0; i < strlen(reinterpret_cast<const char *>(text + a)) &&
                    j < strlen(reinterpret_cast<const char *>(text + b));) {
                if (text[a + i] != text[b + j]) {
                    return text[a + i] < text[b + j];
                } else if (isSpecial(text[a + i]) || isSpecial(text[b + j])) {
                    if (isSpecial(text[a + i])) {
                        i++;
                    }
                    if (isSpecial(text[b + j])) {
                        j++;
                    }
                } else {
                    i++, j++;
                }
            }
            return true;
        });

        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);

        std::sort(indexes, indexes + countOfLines);
        FullFileReader::outputInFile(indexes, text, DistFileName, countOfLines, O_WRONLY | O_APPEND);

    }

    bool isSpecial(char i) {
        return !((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'));
    }
    
}
