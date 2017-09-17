#include "EchoProcessor.h"

EchoProcessor::EchoProcessor(std::string* input, std::string* output) {
    this->input = input;
    this->output = output;
}

void EchoProcessor::run() {
    *output = *input;
}

EchoProcessor::~EchoProcessor() {
    //delete this->input;
    //delete this->output;
}