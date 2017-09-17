#ifndef TP1_COMMONS_H
#define TP1_COMMONS_H

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int recv_message(int skt, char *buf, int size);

int send_message(int skt, char *buf, int size);

int getIntFromBytes(char *bytes);

short getShortFromBytes(char *bytes);

#endif //TP1_COMMONS_H
