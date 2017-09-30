#ifndef TP2_PROCESSORS_H
#define TP2_PROCESSORS_H

#include <list>
#include "EchoProcessor.h"
#include "MatchProcessor.h"
#include "ReplaceProcessor.h"
#include "Reader.h"
#include "Writer.h"

class Threads {
private:
    std::list<Thread*> threads;
public:
    Threads();
    void addEchoThread(std::string name, BlockingString &input,
                       BlockingString &output, Logger &logger);
    void addMatchThread(std::string name, BlockingString &input,
                       BlockingString &output, std::regex rgx, Logger &logger);
    void addReplaceThread(std::string name, BlockingString &input,
                          BlockingString &output, std::regex rgx, std::string
                          replacement, Logger &logger);
    void addReaderThread(File &file, BlockingString &input);
    void addWriterThread(File &file, BlockingString &input);
    void append(Thread* processor);
    void start();
    void join();
    ~Threads();
};

#endif //TP2_PROCESSORS_H
