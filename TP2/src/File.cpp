#include "File.h"
#define FIN_LINEA '\n'

#include <iostream>

File::File(FILE* file) {
    this->file = file;
}

File::File(const char* path, const char* flag) {
    this->file = fopen(path, flag);
}

File::~File() {
    fclose(this->file);
}

string File::readLine() {
    char c;
    string buffer("");
    while ((c = fgetc(this->file)) != FIN_LINEA && c != EOF) {
        buffer += c;
    }
    return buffer;
}

void File::writeLine(string line) {
    fprintf(this->file, "%s\n", line.c_str());
}

int File::onEof() {
    return feof(this->file);
}

void File::changeFile(const char* path, const char* flag) {
    //fclose(this->file);
    this->file = fopen(path, flag);
}
