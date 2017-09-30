#include "Reader.h"
#include <iostream>

Reader::Reader(File &file, BlockingString &input) : Thread(), file(file), input(input) {}

void Reader::run() {
    while (!file.onEof()) {
        std::string new_line = file.readLine();
        input.insert(new_line);
    }
    input.insert("\n\n");
}

Reader::~Reader() {}

