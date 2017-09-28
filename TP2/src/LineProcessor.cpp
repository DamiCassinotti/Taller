#include "LineProcessor.h"
#include <string>

LineProcessor::LineProcessor(std::string name, std::string &input,
                             std::string &output, Logger &logger) :
        name(name), input(input), output(output), logger(logger) {
    logger.addProcessor(name);
}

std::string LineProcessor::getOutput() {
    return output;
}

std::string LineProcessor::getName() {
    return name;
}

void LineProcessor::normalLog() {
    if (input != "")
        logger.log(name, input + " -> " + output);
}

LineProcessor::~LineProcessor() { }
