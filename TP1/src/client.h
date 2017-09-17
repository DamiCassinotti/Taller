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

int mainClient(int argc, char *argv[]);

int sendInsertMsg(int sock, int pos, char *mensaje);

int sendDeleteMsg(int sock, int ini, int fin);

int sendSpaceMsg(int sock, int pos);

int sendNewLineMsg(int sock, int pos);

int readPrintMsgClient(int sock);

int sendPrintMsgClient(int sock);

#endif //TP1_CLIENT_H
