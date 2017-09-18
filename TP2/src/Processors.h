#ifndef TP2_PROCESSORS_H
#define TP2_PROCESSORS_H

#include <list>
#include "LineProcessor.h"
using namespace std;

class Processors {
private:
    list<LineProcessor*> processors;
public:
    Processors();
    void append(LineProcessor* processor);
    LineProcessor* back();
    list<LineProcessor*>::iterator begin();
    list<LineProcessor*>::iterator end();
    ~Processors();
};

#endif //TP2_PROCESSORS_H
