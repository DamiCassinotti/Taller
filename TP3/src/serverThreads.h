#ifndef TP2_PROCESSORS_H
#define TP2_PROCESSORS_H

#include <list>
#include <string>
#include "serverThread.h"
#include "commonSocket.h"
#include "serverCardsData.h"

class Threads {
private:
    std::list<Thread*> threads;
public:
    Threads();
    void addProcessClientThreadAndStart(commonSocket& sock,
                                        serverCardsData& cards,
                                        bool& is_server_connected);
    void start();
    void join();
    ~Threads();
};

#endif //TP2_PROCESSORS_H
