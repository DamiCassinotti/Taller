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
    // Lanzo el thread que conecta clientes
    serverAcceptConnectionsThread accept_connections_thread(port,
                                                        is_server_connected);
    accept_connections_thread.start();
    // Lanzo el thread que escucha el input
    serverQuitThread quit_thread(is_server_connected);
    quit_thread.start();
    // Sincronizo los threads
    accept_connections_thread.join();
    quit_thread.join();
    return 0;
}

