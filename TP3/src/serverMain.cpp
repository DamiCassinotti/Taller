#include <string>
#include <iostream>
#include "commonSocket.h"
#include "commonFile.h"

#define OK 0;
#define PORT_POSITION 1

int main(int argc, char* argv[]) {
    if (argc != 2)
        return OK;
    std::string port(argv[PORT_POSITION]);
    commonSocket sock;
    sock.accept(port);
    sock.send("Chau", 4);
    std::string buf;
    sock.recv(buf, 4);
    std::cout << buf << "\n";
    sock.shutdown();
    return 0;
}

