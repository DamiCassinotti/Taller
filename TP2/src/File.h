#ifndef TP2_FILE_H
#define TP2_FILE_H

#include <stdio.h>
#include <string>
using namespace std;

class File {
private:
    FILE* file;
public:
    File(const string path, const string flag);
    File();
    ~File();
    string leerLinea();
    int onEof();
};

#endif //TP2_FILE_H
