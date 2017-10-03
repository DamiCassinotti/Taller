#ifndef TP2_FILE_H
#define TP2_FILE_H

#include <stdio.h>
#include <string>

class File {
private:
    FILE *file;
public:
    File(const char* path, const char* flag);
    explicit File(FILE *file);
    ~File();
    std::string readLine();
    void writeLine(std::string line);
    bool onEof();
    void changeFile(const char* path, const char* flag);
};

#endif //TP2_FILE_H
