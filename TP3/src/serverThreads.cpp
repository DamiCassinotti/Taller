#include "serverThreads.h"
#include "serverProcessClientThread.h"
#include "serverConnectionData.h"
#include <list>
#include <string>
#include <iostream>

Threads::Threads() {}

void Threads::addProcessClientThreadAndStart(commonSocket &sock,
                                             serverCardsData &cards,
                             serverConnectionData &is_server_connected) {
    Thread* thread = new serverProcessClientThread(sock, cards,
                                                  is_server_connected);
    this->threads.push_back(thread);
    thread->start();
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
