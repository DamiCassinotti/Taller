#include "commons.h"

/*int recv_message(int skt, char *buf, int size) {
    int received = 0;
    int s = 0;
    bool is_the_socket_valid = true;

    while (received < size && is_the_socket_valid) {
        s = recv(skt, &buf[received], size - received, MSG_NOSIGNAL);
        if (s <= 0) {
            is_the_socket_valid = false;
        } else {
            received += s;
        }
    }

    return s;
}*/

int send_message(int skt, char *buf, int size) {
    int sent = 0;
    int s = 0;
    bool is_the_socket_valid = true;

    while (sent < size && is_the_socket_valid) {
        s = send(skt, &buf[sent], size - sent, MSG_NOSIGNAL);
        if (s <= 0) {
            is_the_socket_valid = false;
        } else {
            sent += s;
        }
    }

    return s;
}

int getIntFromBytes(char *bytes) {
    int n;
    memcpy(&n, bytes, sizeof(int));
    return n;
}

short getShortFromBytes(char *bytes) {
    short n = bytes[0];
    n |= bytes[1] >> 8;
    return n;
}
