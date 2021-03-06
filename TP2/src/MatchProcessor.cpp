#include "MatchProcessor.h"
#include <iostream>
#include <string>

MatchProcessor::MatchProcessor(std::string name, BlockingString &input,
                               BlockingString &output, std::regex rgx,
                               Logger &logger) :
        LineProcessor(name, input, output, logger) {
    this->rgx = rgx;
}

void MatchProcessor::run() {
    std::string input_content = input.getString();
    while (input_content != "\n\n") {
        if (std::regex_search(input_content, rgx)) {
            output.insert(input_content);
            normalLog(input_content, input_content);
        } else {
            normalLog(input_content, "(Filtrado)");
        }
        input_content = input.getString();
    }
    output.insert(input_content);
}

MatchProcessor::~MatchProcessor() {}
