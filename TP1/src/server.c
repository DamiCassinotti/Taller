#include "server.h"

int mainServer(int argc, char *argv[]) {
    if (argc != 3)
        return -1;

    char* port = argv[2];
    socket_t* sock = malloc(sizeof(socket_t));
    socketAccept(sock, port);
    /*int s = 0, sock, peersock;
    bool continue_running = true;

    struct addrinfo hints;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, argv[2], &hints, &ptr);

    if (s != 0) return 0;

    sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (sock == -1) {
        freeaddrinfo(ptr);
        return 0;
    }

    s = bind(sock, ptr->ai_addr, ptr->ai_addrlen);
    if (s == -1) {
        close(sock);
        freeaddrinfo(ptr);
        return 0;
    }

    freeaddrinfo(ptr);

    s = listen(sock, 0);
    if (s == -1) {
        close(sock);
        return 0;
    }

    peersock = accept(sock, NULL, NULL);
    if (peersock == -1) {
        continue_running = false;
    }*/

    bool continue_running = isConnected(sock);

    int len = 0;
    rope_t *rope = malloc(sizeof(rope_t));
    ropeCreate(rope, "");
    while (continue_running) {
        char opcode_bytes[sizeof(int)];
        int res = 1;
        len = recv_message(sock->sock, opcode_bytes, sizeof(int));
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
    shutdown(sock->sock, SHUT_RDWR);
    close(sock->sock);

    shutdown(sock->peersock, SHUT_RDWR);
    close(sock->peersock);

    return 0;
}

int readDeleteMsg(socket_t *peersock, rope_t *rope, rope_t *rope2) {
    int res;
    char ini_bytes[4];
    res = recv_message(peersock->sock, ini_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int ini = getIntFromBytes(ini_bytes);

    char fin_bytes[4];
    res = recv_message(peersock->sock, fin_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int fin = getIntFromBytes(fin_bytes);

    delete(rope, ini, fin, rope2);
    return 1;
}

int readSpaceMsg(socket_t *peersock, rope_t *rope, rope_t *rope2) {
    int res;
    char pos_bytes[4];
    res = recv_message(peersock->sock, pos_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int pos = getIntFromBytes(pos_bytes);

    insert(rope, pos, " ", rope2);
    return 1;
}

int readNewlineMsg(socket_t *peersock, rope_t *rope, rope_t *rope2) {
    int res;
    char pos_bytes[4];
    res = recv_message(peersock->sock, pos_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int pos = getIntFromBytes(pos_bytes);

    insert(rope, pos, "\n", rope2);
    return 1;
}

int sendPrintMsg(socket_t *peersock, rope_t *rope) {
    int msg_len = getLongitud(rope);
    char *cadena = getString(rope);

    char *len_bytes = (char *) &msg_len;
    int res = send_message(peersock->sock, len_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    res = send_message(peersock->sock, cadena, msg_len);
    free(cadena);
    if (res <= 0)
        return -1;
    return 1;
}

int readInsertMsg(socket_t *peersock, rope_t *rope, rope_t *rope2) {
    int res;
    char pos_bytes[sizeof(int)];
    res = recv_message(peersock->sock, pos_bytes, sizeof(int));
    if (res <= 0)
        return -1;
    int pos = getIntFromBytes(pos_bytes);

    char len_bytes[sizeof(short)];
    res = recv_message(peersock->sock, len_bytes, sizeof(short));
    if (res <= 0)
        return -1;
    const int kLen = getShortFromBytes(len_bytes);

    char mensaje[kLen + 1];
    res = recv_message(peersock->sock, mensaje, kLen);
    if (res <= 0)
        return -1;
    mensaje[kLen] = '\0';

    insert(rope, pos, mensaje, rope2);
    return 1;
}
