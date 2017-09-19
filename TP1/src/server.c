#include "server.h"

int mainServer(int argc, char *argv[]) {
    if (argc != 3)
        return -1;

    char* port = argv[2];
    socket_t* sock = malloc(sizeof(socket_t));
    socketAccept(sock, port);
    bool continue_running = isConnected(sock);

    int len = 0;
    rope_t *rope = malloc(sizeof(rope_t));
    ropeCreate(rope, "");
    while (continue_running) {
        char opcode_bytes[sizeof(int)];
        int res = 1;
        len = recv_message(sock, opcode_bytes, sizeof(int));
        if (len <= 0) {
            continue_running = false;
        } else {
            int opcode = getIntFromBytes(opcode_bytes);
            if (opcode == 1) {
                rope_t *rope2 = malloc(sizeof(rope_t));
                res = readInsertMsg(sock, rope, rope2);
                rope = rope2;
            } else if (opcode == 2) {
                rope_t *rope2 = malloc(sizeof(rope_t));
                res = readDeleteMsg(sock, rope, rope2);
                rope = rope2;
            } else if (opcode == 3) {
                rope_t *rope2 = malloc(sizeof(rope_t));
                res = readSpaceMsg(sock, rope, rope2);
                rope = rope2;
            } else if (opcode == 4) {
                rope_t *rope2 = malloc(sizeof(rope_t));
                res = readNewlineMsg(sock, rope, rope2);
                rope = rope2;
            } else if (opcode == 5) {
                res = sendPrintMsg(sock, rope);
            } else {
                continue_running = false;
            }
        }
        if (res <= 0) {
            continue_running = false;
        }
    }
    ropeDestroy(rope);
    socketShutdown(sock);
    free(sock);

    return 0;
}

int readDeleteMsg(socket_t *sock, rope_t *rope, rope_t *rope2) {
    int res;
    char ini_bytes[4];
    res = recv_message(sock, ini_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int ini = getIntFromBytes(ini_bytes);

    char fin_bytes[4];
    res = recv_message(sock, fin_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int fin = getIntFromBytes(fin_bytes);

    delete(rope, ini, fin, rope2);
    return 1;
}

int readSpaceMsg(socket_t *sock, rope_t *rope, rope_t *rope2) {
    int res;
    char pos_bytes[4];
    res = recv_message(sock, pos_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int pos = getIntFromBytes(pos_bytes);

    insert(rope, pos, " ", rope2);
    return 1;
}

int readNewlineMsg(socket_t *sock, rope_t *rope, rope_t *rope2) {
    int res;
    char pos_bytes[4];
    res = recv_message(sock, pos_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int pos = getIntFromBytes(pos_bytes);

    insert(rope, pos, "\n", rope2);
    return 1;
}

int sendPrintMsg(socket_t *sock, rope_t *rope) {
    int msg_len = getLongitud(rope);
    char *cadena = getString(rope);

    char *len_bytes = (char *) &msg_len;
    int res = send_message(sock->sock, len_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    res = send_message(sock->sock, cadena, msg_len);
    free(cadena);
    if (res <= 0)
        return -1;
    return 1;
}

int readInsertMsg(socket_t *sock, rope_t *rope, rope_t *rope2) {
    int res;
    char pos_bytes[sizeof(int)];
    res = recv_message(sock, pos_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int pos = getIntFromBytes(pos_bytes);

    char len_bytes[sizeof(short)];
    res = recv_message(sock, len_bytes, sizeof(short));
    if (res <= 0)
        return -1;
    const int kLen = getShortFromBytes(len_bytes);

    char mensaje[kLen + 1];
    res = recv_message(sock, mensaje, kLen);
    if (res <= 0)
        return -1;
    mensaje[kLen] = '\0';

    insert(rope, pos, mensaje, rope2);
    return 1;
}
