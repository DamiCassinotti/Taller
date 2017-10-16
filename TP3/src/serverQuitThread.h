#ifndef TP3_SERVERQUITTHREAD_H
#define TP3_SERVERQUITTHREAD_H


#include "commonFile.h"
#include "serverThread.h"
#include "serverConnectionData.h"
#include "commonSocket.h"

class serverQuitThread : public Thread {
private:
    serverConnectionData &is_server_connected;
    File input;
    commonSocket connection;
public:
    explicit serverQuitThread(serverConnectionData &is_server_connected,
                              commonSocket &connection);
    void run() override;
    ~serverQuitThread();
};


#endif //TP3_SERVERQUITTHREAD_H
