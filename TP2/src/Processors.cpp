#include "Processors.h"
#include <list>

Processors::Processors() {}

void Processors::append(Thread *processor) {
    this->processors.push_back(processor);
}

Thread* Processors::back() {
    return this->processors.back();
}

std::list<Thread*>::iterator Processors::begin() {
    return this->processors.begin();
}

std::list<Thread*>::iterator Processors::end() {
    return this->processors.end();
}

Processors::~Processors() {
    //for (Thread* processor : this->processors) {
    //    delete processor;
    //}
}

void Processors::join() {
    for (Thread* thread : processors) {
        thread->join();
        delete thread;
    }
}
