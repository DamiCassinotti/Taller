#ifndef TP3_SERVERCONNECTIONDATA_H
#define TP3_SERVERCONNECTIONDATA_H


#include <mutex>

class serverConnectionData {
private:
    std::mutex mtx;
    bool is_server_connected;
public:
    serverConnectionData();
    void setConnected(bool connected);
    bool getConnected();
    ~serverConnectionData();
};


#endif //TP3_SERVERCONNECTIONDATA_H
