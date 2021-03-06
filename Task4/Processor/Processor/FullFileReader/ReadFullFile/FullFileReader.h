//
// Created by user on 13.09.18.
//

#ifndef STRINGSORTING_FULLFILEREADER_H
#define STRINGSORTING_FULLFILEREADER_H
#include <cstdio>

/// Change full file into variable and manupulate with it
namespace FullFileReader {
    /// read file to text pointer
    /// \param FileName - name of the file to be read
    /// \param text - variable, that will point to text
    int readFullFile(const char *FileName, char ** text);

    /// change \n to \0
    /// \param text - variable pointing to text, where \n to be changed
    /// \param indexes - array where elemnts will index to the new tokens
    /// \return count of elemnts in indexes
    int changeSlashesToNulles(char *text, int ** indexes);


    /// write text to file with order written in indexes array to the FileName file
    /// \param indexes  - array with order
    /// \param text - text where we will read
    /// \param FileName - file where to safe file
    /// \param countOfLines - count of elements in indexes
    /// \param typeOfWriting - parametres to open the file
    void outputInFile(int * indexes, const char *text, const char *FileName, int countOfLines, int typeOfWriting);
};


#endif //STRINGSORTING_FULLFILEREADER_H
