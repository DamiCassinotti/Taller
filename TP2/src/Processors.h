#ifndef TP2_PROCESSORS_H
#define TP2_PROCESSORS_H

#include <list>
#include "LineProcessor.h"

class Processors {
private:
    std::list<Thread*> processors;
public:
    Processors();
    void append(Thread* processor);
    Thread* back();
    std::list<Thread*>::iterator begin();
    std::list<Thread*>::iterator end();
    void join();
    ~Processors();
};

#endif //TP2_PROCESSORS_H
