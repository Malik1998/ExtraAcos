//
// Created by user on 13.09.18.
//

#ifndef STRINGSORTING_STRINGSORTER_H
#define STRINGSORTING_STRINGSORTER_H

/// sort text
namespace StringSorter {

    /// Text read to the variable, \n changed to \0 and then outputs AscendingText outputs AscendingFromEndText outputs NormalText
    /// are called with appropriate parametres
    /// \param SrcFileName - file where text must be got
    /// \param DistFileName - file where sorted text must be put
    void sortMyFile(const char *SrcFileName, const char *DistFileName);

    ///
    /// \param i
    /// \return
    bool isSpecial(char i);

    /// compare two objects
    /// \param a - first StringToCompare object to be compared
    /// \param b - StringToCompare object to be compared

    ///compare to char*
    /// \param a - first char*
    /// \param b - second char*
    /// \param firstStart - index to the first letter of first char*
    /// \param secondStart - index to the first letter of second char*
    /// \param firstIncrement - way to go through first char*
    /// \param secondIncrement - way to go through second char*
    /// \param firstEnd - index to the last letter of first char*
    /// \param secondEnd - index to the last letter of second char*
    /// \return - true, if char* a starting from firstStart and iterating with + firstIncrement
    ///                 is bigger than b starting from secondStart iterating with + secondIncrement
    ///                 Empty char* -> at the end
    ///           else, else
    bool comparator(const char* a,
                    const char* b,
                    size_t firstStart,
                    size_t secondStart,
                    int firstIncrement,
                    int secondIncrement,
                    size_t firstEnd,
                    size_t secondEnd);

    /// free space where text is
    /// \param text - pointer to first elemt of char
    /// \param indexes - pointer to array of indexes, where in left side \0 was put
    void freeText(char *text, char ** indexes, size_t countOfLines);
};


#endif //STRINGSORTING_STRINGSORTER_H
