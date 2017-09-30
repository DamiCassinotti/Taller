#include "LineProcessor.h"
#include <string>

LineProcessor::LineProcessor(std::string name, BlockingString &input,
                             BlockingString &output, Logger &logger) :
        name(name), input(input), output(output), logger(logger) {
    logger.addProcessor(name);
}

void LineProcessor::normalLog() {
    logger.log(name, input.getString() + " -> " + output.getString());
}

LineProcessor::~LineProcessor() { }
