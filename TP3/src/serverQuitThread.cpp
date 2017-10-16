#include <string>
#include "serverQuitThread.h"

serverQuitThread::serverQuitThread(serverConnectionData &is_server_connected,
        commonSocket &connection) : is_server_connected(is_server_connected),
                                input(File(stdin)), connection(connection) {}

void serverQuitThread::run() {
    std::string input_str;
    while (input_str != "q") {
        input_str = input.readLine();
    }
    is_server_connected.setConnected(false);
    connection.shutdown();
}

serverQuitThread::~serverQuitThread() = default;
