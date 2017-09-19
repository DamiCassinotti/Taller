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
    int peersock;
} socket_t;

void socketConnect(socket_t *self, char *host, char *port);

void socketAccept(socket_t *self, char* port);

bool isConnected(socket_t *self);

int recv_message(socket_t *self, char *buf, int size);

void socketShutdown(socket_t* self);

#endif //TP1_SOCKET_H
