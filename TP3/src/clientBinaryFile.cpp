#include <netinet/in.h>
#include <bitset>
#include <iomanip>
#include <cstring>
#include "clientBinaryFile.h"
#include "clientNoMoreToReadException.h"
#include <string>

clientBinaryFile::clientBinaryFile(std::string file_name) {
    this->file.open(file_name);
    file.seekg(0, std::ios::beg);
}

bool clientBinaryFile::isOpen() {
    return this->file.is_open();
}

std::bitset<16> clientBinaryFile::getTwoBytes() {
    char memblock[sizeof(short)];
    if (!this->file.read(memblock, sizeof(short)))
        throw clientNoMoreToReadException();
    short result_short;
    memcpy(&result_short, memblock, sizeof(short));
    return (ntohs(result_short));
}

std::bitset<32> clientBinaryFile::getFourBytes() {
    char memblock[sizeof(int)];
    if (!this->file.read(memblock, sizeof(int)))
        throw clientNoMoreToReadException();
    int result_int;
    memcpy(&result_int, memblock, sizeof(int));
    return (ntohl(result_int));
}

bool clientBinaryFile::eof() {
    return this->file.eof();
}

clientBinaryFile::~clientBinaryFile(){
    this->file.close();
}
