#ifndef TP1_ROPE_H
#define TP1_ROPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"

typedef struct rope_t rope_t;

struct rope_t {
    nodo_t *raiz;
    rope_t *derecha;
    rope_t *izquierda;
};

// Initializa la instancia self para ser utilizada
// Pre: self apunta un sector válido de memoria
void ropeCreate(rope_t *self, char *cadena_inicial);

// Destruye la instancia self liberando sus recursos.
// Pre: self fue inicializado mediante rope_create
void ropeDestroy(rope_t *self);

char *getString(const rope_t *self);

int getLongitud(const rope_t *self);

void join(rope_t *rope1, rope_t *rope2, rope_t *dest);

void split(int pos, rope_t *original, rope_t *splitted);

void insert(rope_t *self, int pos, char *str, rope_t *dest);

void delete(rope_t *self, int pos_ini, int pos_fin, rope_t *full);

#endif //TP1_ROPE_H
