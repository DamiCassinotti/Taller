#include "Processors.h"
#include <list>

Processors::Processors() {}

void Processors::append(LineProcessor *processor) {
    this->processors.push_back(processor);
}

LineProcessor* Processors::back() {
    return this->processors.back();
}

std::list<LineProcessor*>::iterator Processors::begin() {
    return this->processors.begin();
}

std::list<LineProcessor*>::iterator Processors::end() {
    return this->processors.end();
}

Processors::~Processors() {
    for (LineProcessor* processor : this->processors) {
        delete processor;
    }
}
