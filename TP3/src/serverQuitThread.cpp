#include <string>
#include <iostream>
#include "serverQuitThread.h"

serverQuitThread::serverQuitThread(serverConnectionData &is_server_connected,
        commonSocket &connection) : is_server_connected(is_server_connected),
                                connection(connection) {}

void serverQuitThread::run() {
    std::string input_str;
    while (input_str != "q") {
        std::cin >> input_str;
    }
    is_server_connected.setConnected(false);
    connection.shutdown();
}

serverQuitThread::~serverQuitThread() = default;
