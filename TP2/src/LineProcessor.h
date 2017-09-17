#ifndef TP2_LINEPROCESSOR_H
#define TP2_LINEPROCESSOR_H

#include <stdbool.h>
#include <string>

class LineProcessor {

protected:
    std::string* input;
    std::string* output;

public:
    virtual void run() = 0;
    std::string getOutput();
    virtual ~LineProcessor() = 0;
};

#endif //TP2_LINEPROCESSOR_H
