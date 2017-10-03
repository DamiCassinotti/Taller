#ifndef TP3_SOCKET_H
#define TP3_SOCKET_H
//#define _POSIX_C_SOURCE 200112L

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

class commonSocket {
private:
    int sock;
    int peersock;
    void shutdown();
public:
    commonSocket();
    ~commonSocket();
    void connect(std::string host, std::string port);
    void accept(std::string port);
    bool isConnected();
    int send(std::string msg, int size);
    int recv(std::string& buf, int size);
};


#endif //TP3_SOCKET_H
