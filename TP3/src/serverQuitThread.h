#ifndef TP3_SERVERQUITTHREAD_H
#define TP3_SERVERQUITTHREAD_H


#include "commonFile.h"
#include "serverThread.h"
#include "serverConnectionData.h"

class serverQuitThread : public Thread {
private:
    serverConnectionData &is_server_connected;
    File input;
public:
    explicit serverQuitThread(serverConnectionData &is_server_connected);
    void run() override;
    ~serverQuitThread();
};


#endif //TP3_SERVERQUITTHREAD_H
