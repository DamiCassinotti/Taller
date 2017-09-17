#include "nodo.h"

void nodoHojaCreate(nodo_t* self, char* cadena){
    const int len = (strlen(cadena) + 1 ) * sizeof(char);
    char* str = malloc(len);
    snprintf(str, len, "%s", cadena);
    //strcpy(str, cadena);
    self -> cadena = str;
    self -> tipo_nodo = hoja;
}

void nodoNoHojaCreate(nodo_t* self, int longitud) {
    self -> longitud = longitud;
    self -> tipo_nodo = no_hoja;
}

void nodoDestroy(nodo_t* self) {
    if (self -> tipo_nodo == hoja)
        free(self -> cadena);
}

enum tipoNodo isHoja(nodo_t* self) {
    return self -> tipo_nodo;
}
