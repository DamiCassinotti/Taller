#include "ReplaceProcessor.h"

ReplaceProcessor::ReplaceProcessor(string &input, string &output, regex rgx, string replacement) : LineProcessor(input, output) {
    this->rgx = rgx;
    this->replacement = replacement;
}

void ReplaceProcessor::run() {
    output = regex_replace(input, rgx, replacement);
}

ReplaceProcessor::~ReplaceProcessor() {}