#include "commonSocket.h"
#include "serverConnectionData.h"
#include <string>
#include <condition_variable>

commonSocket::commonSocket() {
    this->sock = 0;
}

commonSocket::~commonSocket(){
    shutdown();
}

void commonSocket::connect(std::string host, std::string port) {
    int sock = 0;
    struct addrinfo *result, *ptr;
    struct addrinfo hints;
    bool are_we_connected = false;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
    if (s != 0)
        return;

    for (ptr = result; ptr != NULL &&
                       !are_we_connected; ptr = ptr->ai_next) {
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock != -1) {
            s = ::connect(sock, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1)
                close(sock);
            are_we_connected = (s != -1);
        }
    }
    freeaddrinfo(result);
    this->sock = sock;
}

void commonSocket::bindAndListen(std::string port) {
    int s = 0, peersock;

    struct addrinfo hints;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, port.c_str(), &hints, &ptr);

    if (s != 0) return;

    peersock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (peersock == -1) {
        freeaddrinfo(ptr);
        return;
    }

    s = bind(peersock, ptr->ai_addr, ptr->ai_addrlen);
    if (s == -1) {
        close(peersock);
        freeaddrinfo(ptr);
        return;
    }

    freeaddrinfo(ptr);

    s = listen(peersock, 0);
    if (s == -1) {
        close(peersock);
        return;
    }

    this->sock = peersock;
}

void commonSocket::accept(commonSocket& peersock) {
    int sock = ::accept(peersock.getFileDescriptor(), NULL, NULL);
    if (sock == -1)
        return;
    this->sock = sock;
}

int commonSocket::getFileDescriptor() {
    return this->sock;
}

void commonSocket::shutdown() {
    ::shutdown(this->sock, SHUT_RDWR);
    close(this->sock);
}

int commonSocket::send(std::string msg, int size) {
    int sent = 0;
    int s = 0;
    bool is_the_socket_valid = true;
    while (sent < size && is_the_socket_valid) {
        s = ::send(this->sock, &(msg.c_str())[sent], size - sent, MSG_NOSIGNAL);
        if (s <= 0) {
            is_the_socket_valid = false;
        } else {
            sent += s;
        }
    }
    return s;
}

int commonSocket::recv(std::string &buf, int size) {
    int received = 0;
    int s = 0;
    bool is_the_socket_valid = true;
    buf.resize(size);
    while (received < size && is_the_socket_valid) {
        s = ::recv(this->sock, &buf.at(received), size - received,
                  MSG_NOSIGNAL);
        if (s <= 0) {
            is_the_socket_valid = false;
        } else {
            received += s;
        }
    }
    return s;
}
