#include "serverConnectionData.h"

serverConnectionData::serverConnectionData() : is_server_connected(true) {}

void serverConnectionData::setConnected(bool connected) {
    std::lock_guard<std::mutex> lock(mtx);
    this->is_server_connected = connected;
}

bool serverConnectionData::getConnected() {
    std::lock_guard<std::mutex> lock(mtx);
    return this->is_server_connected;
}

serverConnectionData::~serverConnectionData() {}
