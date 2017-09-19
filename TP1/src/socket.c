#include "socket.h"

void socketConnect(socket_t* self, char *host, char *port) {
    self->sock = 0;
    int sock = 0;
    struct addrinfo *result, *ptr;
    struct addrinfo hints;
    bool are_we_connected = false;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int s = getaddrinfo(host, port, &hints, &result);
    if (s != 0) {
        return;
    }

    for (ptr = result; ptr != NULL &&
                       are_we_connected == false; ptr = ptr->ai_next) {
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock != -1) {
            s = connect(sock, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1)
                close(sock);
            are_we_connected = (s != -1);
        }
    }
    freeaddrinfo(result);
    self->sock = sock;
}

void socketAccept(socket_t *self, char* port) {
    self->sock = 0;
    self->peersock = 0;
    int s = 0, sock, peersock;

    struct addrinfo hints;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, port, &hints, &ptr);

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

    sock = accept(peersock, NULL, NULL);
    if (sock == -1) {
        return;
    }

    self->sock = sock;
    self->peersock = peersock;
}

bool isConnected(socket_t *self) {
    return self->sock != 0;
}

void socketShutdown(socket_t* self) {
    shutdown(self->sock, SHUT_RDWR);
    close(self->sock);
}
