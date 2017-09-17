#ifndef TP2_ECHOPROCESSOR_H
#define TP2_ECHOPROCESSOR_H

#include "LineProcessor.h"

class EchoProcessor: public LineProcessor {

public:
    EchoProcessor(std::string* input, std::string* output);
    void run();
    ~EchoProcessor();
};

#endif //TP2_ECHOPROCESSOR_H
