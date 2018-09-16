//
// Created by user on 13.09.18.
//

#ifndef STRINGSORTING_STRINGSORTER_H
#define STRINGSORTING_STRINGSORTER_H


namespace StringSorter {

    class StringToCompare;
    

    bool comparator(StringToCompare&& a, StringToCompare&& b);

    void outputAscendingText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName);

    void outputAscendingFromEndText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName);

    void outputNormalText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName);

    void sortMyFile(char *SrcFileName, char *DistFileName);
};


#endif //STRINGSORTING_STRINGSORTER_H
