#ifndef TP3_SOCKET_H
#define TP3_SOCKET_H
//#define _POSIX_C_SOURCE 200112L

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include "serverConnectionData.h"

class commonSocket {
private:
    int sock;
    void shutdown();
public:
    commonSocket();
    ~commonSocket();
    void connect(std::string host, std::string port);
    void bindAndListen(std::string port);
    void accept(commonSocket& peersock);
    int getFileDescriptor();
    int send(std::string msg, int size);
    int recv(std::string& buf, int size);
};


#endif //TP3_SOCKET_H
