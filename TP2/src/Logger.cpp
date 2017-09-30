#include "Logger.h"
#include <string>

Logger::Logger() : should_log(false) {}

void Logger::addProcessor(std::string name) {
    if (!should_log) return;
    this->processors.push_back(name);
}

void Logger::log(std::string processor_name, std::string line) {
    if (!should_log) return;
    std::lock_guard<std::mutex> lock(mtx);
    this->lines_by_processor[processor_name].push_back(line);
}

void Logger::finnishLogging() {
    if (!should_log) return;
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

void Logger::setShouldLog(bool should) {
    should_log = should;
}

Logger::~Logger() {}
