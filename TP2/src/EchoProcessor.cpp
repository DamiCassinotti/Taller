#include <iostream>
#include <string>
#include "EchoProcessor.h"

EchoProcessor::EchoProcessor(std::string name, std::string &input,
                             std::string &output, Logger &logger) :
        LineProcessor(name, input, output, logger) {
}

void EchoProcessor::run() {
    output = input;
    normalLog();
}

EchoProcessor::~EchoProcessor() { }
