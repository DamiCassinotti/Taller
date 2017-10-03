#ifndef TP3_SERVERACCEPTCONNECTIONSTHREAD_H
#define TP3_SERVERACCEPTCONNECTIONSTHREAD_H

#include <list>
#include "serverThread.h"
#include "commonSocket.h"
#include "serverCardsData.h"
#include "serverProcessClientThread.h"
#include "serverThreads.h"


class serverAcceptConnectionsThread : public Thread {
private:
    std::string port;
    Threads threads;
    std::list<commonSocket> sockets;
    bool is_server_connected;
    serverCardsData cards;
public:
    serverAcceptConnectionsThread(std::string port, bool& is_server_connected);
    void run();
    ~serverAcceptConnectionsThread();
};


#endif //TP3_SERVERACCEPTCONNECTIONSTHREAD_H
