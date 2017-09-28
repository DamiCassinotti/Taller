#ifndef TP2_LINEPROCESSOR_H
#define TP2_LINEPROCESSOR_H

#include <stdbool.h>
#include <string>
#include "Logger.h"

class LineProcessor {
protected:
    std::string name;
    std::string &input;
    std::string &output;
    Logger &logger;
    void normalLog();
public:
    LineProcessor(std::string name, std::string &input,
                  std::string &output, Logger &logger);
    virtual void run() = 0;
    std::string getName();
    std::string getOutput();
    virtual ~LineProcessor();
};

#endif //TP2_LINEPROCESSOR_H
