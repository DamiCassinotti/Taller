#include <iostream>
#include "EchoProcessor.h"

EchoProcessor::EchoProcessor(std::string &input, std::string &output) : LineProcessor(input, output) {
}

void EchoProcessor::run() {
    output = input;
    std::cout << "Echo: " << input << "->" << output << "\n";
}

EchoProcessor::~EchoProcessor() { }