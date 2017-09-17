#include "client.h"

int mainClient(int argc, char *argv[]) {
    if (argc < 4 || argc > 5)
        return -1;
    char *host = argv[2];
    char *port = argv[3];

    bool are_we_connected = false;
    int sock = 0;
    struct addrinfo *result, *ptr;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int s = getaddrinfo(host, port, &hints, &result);
    if (s != 0) {
        return 0;
    }

    for (ptr = result; ptr != NULL &&
            are_we_connected == false; ptr = ptr->ai_next) {
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock == -1) {
        } else {
            s = connect(sock, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1) {
                close(sock);
            }
            are_we_connected = (s != -1);
        }
    }
    freeaddrinfo(result);

    FILE *input;
    if (argc == 5) {
        const char *file_path = argv[4];
        input = fopen(file_path, "r");
        if (input == NULL) {
            return 0;
        }
    } else {
        input = stdin;
    }
    char *line = leerLineaArchivo(input);
    int res = 1;
    while (!feof(input) && are_we_connected) {
        char* saveptr = "line";
        strtok_r(line, " ", &saveptr);
        if (strcmp(line, "insert") == 0) {
            int pos = atoi(strtok_r(NULL, " ", &saveptr));
            char *str_to_insert = strtok_r(NULL, " ", &saveptr);
            res = sendInsertMsg(sock, pos, str_to_insert);
        } else if (strcmp(line, "delete") == 0) {
            int pos_ini = atoi(strtok_r(NULL, " ", &saveptr));
            int pos_fin = atoi(strtok_r(NULL, " ", &saveptr));
            res = sendDeleteMsg(sock, pos_ini, pos_fin);
        } else if (strcmp(line, "space") == 0) {
            int pos = atoi(strtok_r(NULL, " ", &saveptr));
            res = sendSpaceMsg(sock, pos);
        } else if (strcmp(line, "newline") == 0) {
            int pos = atoi(strtok_r(NULL, " ", &saveptr));
            res = sendNewLineMsg(sock, pos);
        } else if (strcmp(line, "print") == 0) {
            res = sendPrintMsgClient(sock);
            res = readPrintMsgClient(sock);
        }
        free(line);
        line = leerLineaArchivo(input);
        if (res <= 0) {
            are_we_connected = false;
        }
    }
    free(line);
    fclose(input);

    shutdown(sock, SHUT_RDWR);
    close(sock);
    return 0;
}

int sendInsertMsg(int sock, int pos, char *mensaje) {
    int res, opcode = 1;
    char *opcode_bytes = (char *) &opcode;
    res = send_message(sock, opcode_bytes, sizeof(int));
    if (res <= 0)
        return -1;

    char *pos_bytes = (char *) &pos;
    res = send_message(sock, pos_bytes, sizeof(int));
    if (res <= 0)
        return -1;

    short len = strlen(mensaje);
    char *len_bytes = (char *) &len;
    res = send_message(sock, len_bytes, sizeof(short));
    if (res <= 0)
        return -1;

    res = send_message(sock, mensaje, strlen(mensaje));
    if (res <= 0)
        return -1;
    return 1;
}

int sendDeleteMsg(int sock, int ini, int fin) {
    int opcode = 2;
    char *opcode_bytes = (char *) &opcode;
    int res = send_message(sock, opcode_bytes, sizeof(int));
    if (res <= 0)
        return -1;

    char *ini_bytes = (char *) &ini;
    res = send_message(sock, ini_bytes, sizeof(int));
    if (res <= 0)
        return -1;

    char *fin_bytes = (char *) &fin;
    return send_message(sock, fin_bytes, sizeof(int));
}

int sendSpaceMsg(int sock, int pos) {
    int opcode = 3;
    char *opcode_bytes = (char *) &opcode;
    int res = send_message(sock, opcode_bytes, sizeof(int));
    if (res <= 0)
        return -1;

    char *pos_bytes = (char *) &pos;
    return send_message(sock, pos_bytes, sizeof(int));
}

int sendNewLineMsg(int sock, int pos) {
    int opcode = 4;
    char *opcode_bytes = (char *) &opcode;
    int res = send_message(sock, opcode_bytes, sizeof(int));
    if (res <= 0)
        return -1;

    char *pos_bytes = (char *) &pos;
    return send_message(sock, pos_bytes, sizeof(int));
}

int readPrintMsgClient(int sock) {
    int res;
    char msg_len_bytes[4];
    res = recv_message(sock, msg_len_bytes, 4);
    if (res <= 0)
        return -1;
    int kMsgLen = getIntFromBytes(msg_len_bytes);

    char msg[kMsgLen + 1];
    res = recv_message(sock, msg, kMsgLen);
    if (res <= 0)
        return -1;
    msg[kMsgLen] = '\0';
    printf("%s", msg);
    return 1;
}

int sendPrintMsgClient(int sock) {
    int opcode = 5;
    char *opcode_bytes = (char *) &opcode;
    return send_message(sock, opcode_bytes, sizeof(int));
}
