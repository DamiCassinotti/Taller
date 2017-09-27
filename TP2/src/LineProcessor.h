#ifndef TP2_LINEPROCESSOR_H
#define TP2_LINEPROCESSOR_H

#include <stdbool.h>
#include <string>

class LineProcessor {

protected:
    std::string name;
    std::string &input;
    std::string &output;

public:
    LineProcessor(std::string name, std::string &input, std::string &output);
    virtual void run() = 0;
    std::string getName();
    std::string getOutput();
    virtual ~LineProcessor();
};

#endif //TP2_LINEPROCESSOR_H
