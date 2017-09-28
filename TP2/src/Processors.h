#ifndef TP2_PROCESSORS_H
#define TP2_PROCESSORS_H

#include <list>
#include "LineProcessor.h"

class Processors {
private:
    std::list<LineProcessor*> processors;
public:
    Processors();
    void append(LineProcessor* processor);
    LineProcessor* back();
    std::list<LineProcessor*>::iterator begin();
    std::list<LineProcessor*>::iterator end();
    ~Processors();
};

#endif //TP2_PROCESSORS_H
