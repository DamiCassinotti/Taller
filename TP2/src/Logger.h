#ifndef TP2_LOGGER_H
#define TP2_LOGGER_H

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <mutex>

class Logger {
private:
    std::map<std::string, std::list<std::string>> lines_by_processor;
    std::list<std::string> processors;
    bool should_log;
    std::mutex mtx;
public:
    Logger();
    void addProcessor(std::string name);
    void log(std::string processor_name, std::string line);
    void finnishLogging();
    void setShouldLog(bool should);
    ~Logger();
};


#endif //TP2_LOGGER_H
