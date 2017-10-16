#ifndef TP2_PROCESSORS_H
#define TP2_PROCESSORS_H

#include <list>
#include <string>
#include "serverThread.h"
#include "commonSocket.h"
#include "serverCardsData.h"
#include "serverConnectionData.h"

class Threads {
private:
    std::list<Thread*> threads;
public:
    Threads();
    void addProcessClientThreadAndStart(commonSocket& sock,
                                        serverCardsData& cards,
                                    serverConnectionData &is_server_connected);
    void addQuitThreadAndStart(serverConnectionData &is_server_connected,
                               commonSocket &connection);
    void join();
    ~Threads();
};

#endif //TP2_PROCESSORS_H
