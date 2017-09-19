#ifndef TP1_SERVER_H
#define TP1_SERVER_H
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
#include "rope.h"
#include "socket.h"

int mainServer(int argc, char *argv[]);

int readDeleteMsg(socket_t *peersock, rope_t *rope, rope_t *rope2);

int readSpaceMsg(socket_t *peersock, rope_t *rope, rope_t *rope2);

int readNewlineMsg(socket_t *peersock, rope_t *rope, rope_t *rope2);

int sendPrintMsg(socket_t *peersock, rope_t *rope);

int readInsertMsg(socket_t *peersock, rope_t *rope, rope_t *rope2);

#endif //TP1_SERVER_H
