#include "lectura.h"
#define TAMANIO_INICIAL_BUFFER 10
#define FIN_LINEA '\n'
#define FIN_STRING '\0'

char* leerLinea(){
    char c;
    size_t tam = TAMANIO_INICIAL_BUFFER;
    int i;

    char* buffer = malloc(sizeof(char)*(tam));
    if (!buffer) return NULL;

    for (i = 0; (c = getchar()) != FIN_LINEA && c != EOF; i++) {
        if (i + 1 == tam) { // si llego al tamanio de mi cadena
            tam += tam;  // la forma de modificar tam es arbitraria
            char* aux = realloc(buffer, tam * sizeof(char));
            if (!aux) break;  // si falla realloc, termino aca
            buffer = aux;
        }
        buffer[i] = c;
    }
    buffer[i] = FIN_STRING; // es necesario cerrar el string
    return buffer;
}

char* leerLineaArchivo(FILE* file) {
    char c;
    size_t tam = TAMANIO_INICIAL_BUFFER;
    int i;

    char* buffer = malloc(sizeof(char)*(tam));
    if (!buffer) return NULL;

    for (i = 0; (c = fgetc(file)) != FIN_LINEA && c != EOF; i++) {
        if (i + 1 == tam) { // si llego al tamanio de mi cadena
            tam += tam;  // la forma de modificar tam es arbitraria
            char* aux = realloc(buffer, tam * sizeof(char));
            if (!aux) break;  // si falla realloc, termino aca
            buffer = aux;
        }
        buffer[i] = c;
    }
    buffer[i] = FIN_STRING; // es necesario cerrar el string
    return buffer;
}
