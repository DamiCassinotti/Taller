#include <string>
#include <iostream>
#include "serverAcceptConnectionsThread.h"
#include "serverQuitThread.h"
#include "serverConnectionData.h"

#define OK 0;
#define PORT_POSITION 1

int main(int argc, char* argv[]) {
    if (argc != 2)
        return OK;
    std::string port(argv[PORT_POSITION]);
    serverConnectionData is_server_connected;
    serverAcceptConnectionsThread accept_connections_thread(port,
                                                        is_server_connected);
    accept_connections_thread.start();
    accept_connections_thread.join();
    return 0;
}

