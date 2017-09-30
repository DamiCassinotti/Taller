#include "File.h"
#include <iostream>
#include <string>

#define FIN_LINEA '\n'

File::File(FILE* file) {
    this->file = file;
}

File::File(const char* path, const char* flag) {
    this->file = fopen(path, flag);
}

File::~File() {
    fclose(this->file);
}

std::string File::readLine() {
    char c;
    std::string buffer("");
    while ((c = fgetc(this->file)) != FIN_LINEA && c != EOF) {
        buffer += c;
    }
    return buffer;
}

void File::writeLine(std::string line) {
    fprintf(this->file, "%s", line.c_str());
}

bool File::onEof() {
    return feof(this->file);
}

void File::changeFile(const char* path, const char* flag) {
    if (this->file != stdin && this->file != stdout)
        fclose(this->file);
    this->file = fopen(path, flag);
}
