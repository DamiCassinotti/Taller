#include "LineProcessor.h"
#include <string>

LineProcessor::LineProcessor(std::string name, BlockingString &input,
                             BlockingString &output, Logger &logger) :
        name(name), input(input), output(output), logger(logger) {
    logger.addProcessor(name);
}

void LineProcessor::normalLog(std::string input_content,
                              std::string output_content) {
    logger.log(name, input_content + " -> " + output_content);
}

LineProcessor::~LineProcessor() { }
