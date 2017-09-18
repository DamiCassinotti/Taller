#include "File.h"
#define FIN_LINEA '\n'

File::File(FILE* file) {
    this->file = file;
}

File::File(const string path, const string flag) {
    this->file = fopen(path.c_str(), flag.c_str());
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
