#ifndef TP1_CLIENT_H
#define TP1_CLIENT_H
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "commons.h"
#include "lectura.h"
#include "socket.h"

int mainClient(int argc, char *argv[]);

int sendInsertMsg(socket_t* sock, int pos, char *mensaje);

int sendDeleteMsg(socket_t* sock, int ini, int fin);

int sendSpaceMsg(socket_t* sock, int pos);

int sendNewLineMsg(socket_t* sock, int pos);

int readPrintMsgClient(socket_t* sock);

int sendPrintMsgClient(socket_t* sock);

#endif //TP1_CLIENT_H
