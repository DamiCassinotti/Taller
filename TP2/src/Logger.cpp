#include "Logger.h"
#include <string>

Logger::Logger() {}

void Logger::addProcessor(std::string name) {
    this->processors.push_back(name);
}

void Logger::log(std::string processor_name, std::string line) {
    this->lines_by_processor[processor_name].push_back(line);
}

void Logger::finnishLogging() {
    int processors_count = 0;
    for (std::string processor : processors) {
        ++processors_count;
        std::cerr << "(" << processors_count << ") " << processor << "\n";
        int lines_count = 0;
        for (std::string line : lines_by_processor[processor]) {
            ++lines_count;
            std::cerr << line << "\n";
        }
        if (processor != processors.back())
            std::cerr << "\n";
    }
}

Logger::~Logger() {}
