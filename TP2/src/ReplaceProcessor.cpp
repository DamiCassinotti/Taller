#include "ReplaceProcessor.h"
#include <string>

ReplaceProcessor::ReplaceProcessor(std::string name, std::string &input,
                                   std::string &output, std::regex rgx,
                                   std::string replacement, Logger &logger) :
        LineProcessor(name, input, output, logger) {
    this->rgx = rgx;
    this->replacement = replacement;
}

void ReplaceProcessor::run() {
    output = std::regex_replace(input, rgx, replacement);
    normalLog();
}

ReplaceProcessor::~ReplaceProcessor() {}
