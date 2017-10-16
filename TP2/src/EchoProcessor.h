#ifndef TP2_ECHOPROCESSOR_H
#define TP2_ECHOPROCESSOR_H

#include <string>
#include "LineProcessor.h"
#include "BlockingString.h"

// Modelo para el comando 'echo'
class EchoProcessor: public LineProcessor {
public:
    EchoProcessor(std::string name, BlockingString &input,
                  BlockingString &output, Logger &logger);
    void run() override;
    ~EchoProcessor();
};

#endif //TP2_ECHOPROCESSOR_H
