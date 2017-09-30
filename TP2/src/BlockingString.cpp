#include "BlockingString.h"
#include <iostream>
#include <string>

BlockingString::BlockingString() {}

BlockingString::~BlockingString() {}

void BlockingString::insert(std::string new_input) {
    std::unique_lock<std::mutex> lock(mtx);
    input_ready.wait(lock, [=]{return input == "";});
    this->input = new_input;
    output_ready.notify_all();
}

std::string BlockingString::getString() {
    std::unique_lock<std::mutex> lock(mtx);
    output_ready.wait(lock, [=]{return input != "";});
    std::string input_cpy(input);
    input = std::string();
    input_ready.notify_all();
    return input_cpy;
}
