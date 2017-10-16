#include <iostream>
#include "serverAcceptConnectionsThread.h"
#include "serverQuitThread.h"
#include <string>
#include <list>

serverAcceptConnectionsThread::serverAcceptConnectionsThread(std::string port,
                     serverConnectionData &is_server_connected) : port(port),
                                     is_server_connected(is_server_connected) {}

void serverAcceptConnectionsThread::run() {
    commonSocket connection;
    connection.bindAndListen(port);
    threads.addQuitThreadAndStart(is_server_connected, connection);
    std::list<commonSocket> clientes;
    while (is_server_connected.getConnected()) {
        clientes.emplace_back();
        clientes.back().accept(connection);
        this->threads.addProcessClientThreadAndStart(clientes.back(), cards,
                                                     is_server_connected);
    }
    threads.join();
}

serverAcceptConnectionsThread::~serverAcceptConnectionsThread() {}
