#include "LineProcessor.h"

LineProcessor::LineProcessor(std::string &input, std::string &output) : input(input), output(output) {
}

std::string LineProcessor::getOutput() {
    return output;
}

LineProcessor::~LineProcessor() {}

