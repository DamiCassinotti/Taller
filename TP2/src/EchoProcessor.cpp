#include <iostream>
#include <string>
#include "EchoProcessor.h"

EchoProcessor::EchoProcessor(std::string name, BlockingString &input,
                             BlockingString &output, Logger &logger) :
        LineProcessor(name, input, output, logger) {
}

void EchoProcessor::run() {
    std::string input_content = input.getString();
    while (input_content != "\n\n") {
        output.insert(input_content);
        input_content = input.getString();
    }
    output.insert(input_content);
}

EchoProcessor::~EchoProcessor() { }
