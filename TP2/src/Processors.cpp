#include "Processors.h"

Processors::Processors() {

}

void Processors::append(LineProcessor *processor) {
    this->processors.push_back(processor);
}

LineProcessor* Processors::back() {
    return this->processors.back();
}

list<LineProcessor*>::iterator Processors::begin() {
    return this->processors.begin();
}

list<LineProcessor*>::iterator Processors::end() {
    return this->processors.end();
}

Processors::~Processors() {
    for (LineProcessor* processor : this->processors) {
        delete processor;
    }
}
