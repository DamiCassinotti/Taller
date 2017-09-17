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

int mainServer(int argc, char *argv[]);

int readDeleteMsg(int peersock, rope_t *rope, rope_t *rope2);

int readSpaceMsg(int peersock, rope_t *rope, rope_t *rope2);

int readNewlineMsg(int peersock, rope_t *rope, rope_t *rope2);

int sendPrintMsg(int peersock, rope_t *rope);

int readInsertMsg(int peersock, rope_t *rope, rope_t *rope2);

#endif //TP1_SERVER_H
