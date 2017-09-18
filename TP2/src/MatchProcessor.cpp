#include "MatchProcessor.h"

MatchProcessor::MatchProcessor(string &input, string &output, regex rgx) : LineProcessor(input, output) {
    this->rgx = rgx;
}

void MatchProcessor::run() {
    if (std::regex_match(input, rgx))
        output = input;
    else
        output = string("");
}

MatchProcessor::~MatchProcessor() {}