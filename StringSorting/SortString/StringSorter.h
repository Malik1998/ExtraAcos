//
// Created by user on 13.09.18.
//

#ifndef STRINGSORTING_STRINGSORTER_H
#define STRINGSORTING_STRINGSORTER_H

/// namespace that will Sort text in linux encoding
namespace StringSorter {

/// class that will be used in comparator
/// It will help to interate through char*
    class StringToCompare {
    private:
        /// text to compare
        const char *data;
        /// next elemnt will be taken as currentElement + increment
        int increment;
        /// index of start
        size_t firstElement;
        /// index of end
        size_t lastElement;
        /// index where we are looking at
        size_t currentElement;
    public:
        /// constructor that will set currentElement = firstElement_
        /// \param data_  - char* to be compared
        /// \param increment_ - how we iterate through char*
        /// \param firstElement_ - index of start
        /// \param lastElement_  - index of end
        StringToCompare(const char *data_, int increment_, size_t firstElement_, size_t lastElement_);

        /// check if given char* is empty
        /// \return true - if empty
        bool isEmpty();

        /// check if we can further as: currentElement + increment
        /// \return true if currentElement + increment != lastElement
        bool hasNext();

        /// check if next element (currentElement + increment), is not in A..Za..z
        /// Call only if hasNext() - true!!!
        /// \return true - if next char is not A..Za..z
        bool isNextSpecial();

        /// call only if currentElement is adequate
        /// \return current char
        char next();

        /// make currentElement point to element that is going after special symbols
        void skipSpecial();
    };


    /// compare two objects
    /// \param a - first StringToCompare object to be compared
    /// \param b - StringToCompare object to be compared
    /// \return - true, if object a starting from a.firstElement and iterating with + a.increment
    ///                 is bigger than b starting from b.firstElemnt iterating with + b.increment
    ///                 Empty char* -> at the end
    ///           else, else
    bool comparator(StringToCompare&& a, StringToCompare&& b);

    /// Truncate file DistFileName or create it and write there text sorted Ascending
    /// \param indexes - array where sorted indexes will be
    /// \param countOfLines - count of elements in indexes
    /// \param text -  full text
    /// \param DistFileName - file where text must be printed
    void outputAscendingText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName);

    /// Append to file DistFileName text sorted Ascending starting from the end of line
    /// \param indexes - array where sorted indexes will be
    /// \param countOfLines - count of elements in indexes
    /// \param text -  full text
    /// \param DistFileName - file where text must be printed
    void outputAscendingFromEndText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName);

    /// Append to file DistFileName full text
    /// \param indexes - array where sorted indexes will be
    /// \param countOfLines - count of elements in indexes
    /// \param text -  full text
    /// \param DistFileName - file where text must be printed
    void outputNormalText(size_t *indexes, size_t countOfLines, char *text, char *DistFileName);

    /// Text read to the variable, \n changed to \0 and then outputAscendingText outputAscendingFromEndText outputNormalText
    /// are called with appropriate parametres
    /// \param SrcFileName - file where text must be got
    /// \param DistFileName - file where sorted text must be put
    void sortMyFile(char *SrcFileName, char *DistFileName);
};


#endif //STRINGSORTING_STRINGSORTER_H
