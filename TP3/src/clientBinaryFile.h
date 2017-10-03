#ifndef TP3_CLIENTBINARYFILE_H
#define TP3_CLIENTBINARYFILE_H

#include <iostream>
#include <fstream>
#include <string>

class clientBinaryFile {
private:
    std::ifstream file;
public:
    explicit clientBinaryFile(std::string file_name);
    bool isOpen();
    std::bitset<16> getTwoBytes();
    std::bitset<32> getFourBytes();
    bool eof();
    ~clientBinaryFile();
};


#endif //TP3_CLIENTBINARYFILE_H
