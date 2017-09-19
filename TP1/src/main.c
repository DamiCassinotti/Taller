#include <string.h>
#include "client.h"
#include "server.h"

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 5)
        return -1;
    if (strcmp(argv[1], "server") == 0)
        return mainServer(argc, argv);
    if (strcmp(argv[1], "client") == 0)
        return mainClient(argc, argv);
    return -1;
}

