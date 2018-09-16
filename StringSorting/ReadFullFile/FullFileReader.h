//
// Created by user on 13.09.18.
//

#ifndef STRINGSORTING_FULLFILEREADER_H
#define STRINGSORTING_FULLFILEREADER_H


namespace FullFileReader {
    void readFullFile(char* FileName, char ** text);

    size_t changeSlashesToNulles(char *text, size_t ** indexes);

    void outputInFile(size_t * indexes, const char *text, char* FileName, size_t countOfLines, int typeOfWriting);
};


#endif //STRINGSORTING_FULLFILEREADER_H
