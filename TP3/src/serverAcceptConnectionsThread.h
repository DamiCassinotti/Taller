#ifndef TP3_SERVERACCEPTCONNECTIONSTHREAD_H
#define TP3_SERVERACCEPTCONNECTIONSTHREAD_H

#include <list>
#include <string>
#include "serverThread.h"
#include "commonSocket.h"
#include "serverCardsData.h"
#include "serverProcessClientThread.h"
#include "serverThreads.h"
#include "serverConnectionData.h"


class serverAcceptConnectionsThread : public Thread {
private:
    std::string port;
    Threads threads;
    serverConnectionData &is_server_connected;
    serverCardsData cards;
public:
    serverAcceptConnectionsThread(std::string port,
                                  serverConnectionData &is_server_connected);
    void run();
    ~serverAcceptConnectionsThread();
};


#endif //TP3_SERVERACCEPTCONNECTIONSTHREAD_H
