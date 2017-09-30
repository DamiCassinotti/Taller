#include "ReplaceProcessor.h"
#include <string>

ReplaceProcessor::ReplaceProcessor(std::string name, BlockingString &input,
                                   BlockingString &output, std::regex rgx,
                                   std::string replacement, Logger &logger) :
        LineProcessor(name, input, output, logger) {
    this->rgx = rgx;
    this->replacement = replacement;
}

void ReplaceProcessor::run() {
    std::string input_content = input.getString();
    while (input_content != "\n\n") {
        std::string output_content = std::regex_replace(input_content, rgx, replacement);
        output.insert(output_content);
        //normalLog();
        input_content = input.getString();
    }
    output.insert(input_content);
}

ReplaceProcessor::~ReplaceProcessor() {}
