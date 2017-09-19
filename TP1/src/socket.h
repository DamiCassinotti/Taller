#ifndef TP1_SOCKET_H
#define TP1_SOCKET_H
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>


typedef struct {
    int sock;
} socket_t;

void socketConnect(socket_t *socket, char *host, char *port);

bool isConnected(socket_t *socket);

#endif //TP1_SOCKET_H
