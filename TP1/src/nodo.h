#ifndef TP1_NODO_H
#define TP1_NODO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enumerables.h"

typedef struct {
    tipoNodo tipo_nodo;
    int longitud;
    char* cadena;
} nodo_t;

// Initializa la instancia self para ser utilizada
// Pre: self apunta un sector válido de memoria.
//      cadena debe poder ser liberado en cualquier momento
void nodoHojaCreate(nodo_t* self, char* cadena);

// Initializa la instancia self para ser utilizada
// Pre: self apunta un sector válido de memoria.
void nodoNoHojaCreate(nodo_t* self, int longitud);

// Destruye la instancia self liberando sus recursos.
// Pre: self fue inicializado mediante nodo_create
void nodoDestroy(nodo_t* self);

// Devuelve 1 si es hoja, 0 si no (corresponde al enum)
enum tipoNodo isHoja(nodo_t* self);

#endif //TP1_NODO_H
