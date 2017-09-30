#include "Processors.h"
#include <list>

Threads::Threads() {}

void Threads::addEchoThread(std::string name, BlockingString &input,
                               BlockingString &output, Logger &logger) {
    Thread* echo = new EchoProcessor(name, input, output, logger);
    this->threads.push_back(echo);
}

void Threads::addMatchThread(std::string name, BlockingString &input,
                               BlockingString &output, std::regex rgx,
                               Logger &logger) {
    Thread* match = new MatchProcessor(name, input, output, rgx, logger);
    this->threads.push_back(match);
}

void Threads::addReplaceThread(std::string name, BlockingString &input,
                                  BlockingString &output, std::regex rgx,
                                  std::string replacement, Logger &logger) {
    Thread* replace = new ReplaceProcessor(name, input, output, rgx,
                                           replacement, logger);
    this->threads.push_back(replace);
}

void Threads::addReaderThread(File &file, BlockingString &input) {
    Thread* reader = new Reader(file, input);
    this->threads.push_back(reader);
}

void Threads::addWriterThread(File &file, BlockingString &input) {
    Thread* writer = new Writer(file, input);
    this->threads.push_back(writer);
}

void Threads::append(Thread *processor) {
    this->threads.push_back(processor);
}

void Threads::start() {
    for (Thread* thread : threads) {
        thread->start();
    }
}

void Threads::join() {
    for (Thread* thread : threads) {
        thread->join();
    }
}

Threads::~Threads() {
    for (Thread* processor : this->threads) {
        delete processor;
    }
}
