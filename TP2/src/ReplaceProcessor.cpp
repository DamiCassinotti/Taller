#include "ReplaceProcessor.h"
#include <iostream>

ReplaceProcessor::ReplaceProcessor(string name, string &input, string &output, regex rgx, string replacement) : LineProcessor(name, input, output) {
    this->rgx = rgx;
    this->replacement = replacement;
}

void ReplaceProcessor::run() {
    output = regex_replace(input, rgx, replacement);
    std::cout << "Replace: " << input << "->" << output << "\n";
}

ReplaceProcessor::~ReplaceProcessor() {}