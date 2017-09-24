#ifndef TP2_FILE_H
#define TP2_FILE_H

#include <stdio.h>
#include <string>

using namespace std;

class File {
private:
    FILE *file;
public:
    File(const char* path, const char* flag);
    File(FILE *file);
    ~File();
    string readLine();
    void writeLine(string line);
    int onEof();
    void changeFile(const char* path, const char* flag);
};

#endif //TP2_FILE_H
