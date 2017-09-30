#include "Writer.h"
#include <iostream>
#include <string>

Writer::Writer(File &file, BlockingString &input) : Thread(), file(file),
                                                    input(input) {}

void Writer::run() {
    std::string new_line = input.getString();
    while (new_line != "\n\n") {
        file.writeLine(new_line);
        new_line = input.getString();
    }
}

Writer::~Writer() {}
