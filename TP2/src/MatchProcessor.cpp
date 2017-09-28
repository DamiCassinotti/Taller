#include "MatchProcessor.h"
#include <iostream>
#include <string>

MatchProcessor::MatchProcessor(std::string name, std::string &input,
                               std::string &output, std::regex rgx,
                               Logger &logger) :
        LineProcessor(name, input, output, logger) {
    this->rgx = rgx;
}

void MatchProcessor::run() {
    if (std::regex_search(input, rgx)){
        output = input;
        normalLog();
    } else {
        output = std::string("");
        filteredLog();
    }
}

void MatchProcessor::filteredLog() {
    if (input != "")
        logger.log(name, input + " -> " + "(Filtrado)");
}

MatchProcessor::~MatchProcessor() {}
