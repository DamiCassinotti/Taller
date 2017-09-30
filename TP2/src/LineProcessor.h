#ifndef TP2_LINEPROCESSOR_H
#define TP2_LINEPROCESSOR_H

#include <stdbool.h>
#include <string>
#include "Thread.h"
#include "Logger.h"
#include "BlockingString.h"

class LineProcessor : public Thread {
protected:
    std::string name;
    BlockingString &input;
    BlockingString &output;
    Logger &logger;
    void normalLog();
public:
    LineProcessor(std::string name, BlockingString &input,
                  BlockingString &output, Logger &logger);
    virtual void run() = 0;
    virtual ~LineProcessor();
};

#endif //TP2_LINEPROCESSOR_H
