#include "File.h"
#define FIN_LINEA '\n'

File::File() {
    this->file = stdin;
}

File::File(const string path, const string flag) {
    this->file = fopen(path.c_str(), flag.c_str());
}

File::~File() {
    fclose(this->file);
}

string File::leerLinea() {
    char c;
    string buffer("");
    while ((c = fgetc(this->file)) != FIN_LINEA && c != EOF) {
        buffer += c;
    }
    return buffer;
}

int File::onEof() {
    return feof(this->file);
}
