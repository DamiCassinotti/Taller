#include "LineProcessor.h"
#include <iostream>

LineProcessor::LineProcessor(std::string name, std::string &input, std::string &output) : name(name), input(input), output(output) {
}

std::string LineProcessor::getOutput() {
    return output;
}

std::string LineProcessor::getName() {
    return name;
}

LineProcessor::~LineProcessor() { }

