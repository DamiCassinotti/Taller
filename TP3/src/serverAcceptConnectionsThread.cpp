#include <iostream>
#include "serverAcceptConnectionsThread.h"

serverAcceptConnectionsThread::serverAcceptConnectionsThread(std::string port,
        bool &is_server_connected) : port(port),
                                     is_server_connected(is_server_connected) {}

void serverAcceptConnectionsThread::run() {
    commonSocket sock;
    //while (is_server_connected) {
        sock.accept(port);
        //this->sockets.push_back(sock);
        this->threads.addProcessClientThreadAndStart(sock, cards,
                                                     is_server_connected);
        //sock = commonSocket();
    //}
    threads.join();
}

serverAcceptConnectionsThread::~serverAcceptConnectionsThread() {}
