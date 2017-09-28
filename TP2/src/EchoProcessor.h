#ifndef TP2_ECHOPROCESSOR_H
#define TP2_ECHOPROCESSOR_H

#include <string>
#include "LineProcessor.h"

class EchoProcessor: public LineProcessor {
public:
    EchoProcessor(std::string name, std::string &input, std::string &output,
                  Logger &logger);
    void run() override;
    ~EchoProcessor();
};

#endif //TP2_ECHOPROCESSOR_H
