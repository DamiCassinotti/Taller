#include "commons.h"

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
