#include "MatchProcessor.h"
#include <iostream>

MatchProcessor::MatchProcessor(string name, string &input, string &output, regex rgx) : LineProcessor(name, input, output) {
    this->rgx = rgx;
}

void MatchProcessor::run() {
    if (std::regex_search(input, rgx))
        output = input;
    else
        output = string("");
    std::cout << "Match: " << input << "->" << output << "\n";
}

MatchProcessor::~MatchProcessor() {}