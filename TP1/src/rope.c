#include "rope.h"

void ropeCreate(rope_t *self, char *cadena_inicial) {
    self->izquierda = NULL;
    self->derecha = NULL;
    nodo_t *raiz = malloc(sizeof(nodo_t));
    nodoHojaCreate(raiz, cadena_inicial);
    self->raiz = raiz;
}

void ropeDestroy(rope_t *self) {
    if (isHoja(self->raiz) == no_hoja) {
        ropeDestroy(self->izquierda);
        if (self->derecha != NULL)
            ropeDestroy(self->derecha);
    }
    nodoDestroy(self->raiz);
    free(self->raiz);
    free(self);
}

char *getString(const rope_t *self) {
    if (isHoja(self->raiz) == hoja) {
        const int len = (strlen(self->raiz->cadena) + 1) * sizeof(char);
        char *str = malloc(len);
        snprintf(str, len, "%s", self->raiz->cadena);
        return str;
    }
    char *cadena_izq = getString(self->izquierda);
    char *cadena_der = self->derecha != NULL ? getString(self->derecha) : "";
    const int len = (strlen(cadena_izq) + strlen(cadena_der) + 1)
                    * sizeof(char);
    char *str = malloc(len);
    snprintf(str, len, "%s%s", cadena_izq, cadena_der);
    free(cadena_izq);
    if (self->derecha != NULL)
        free(cadena_der);
    return str;
}

int getLongitud(const rope_t *self) {
    if (isHoja(self->raiz) == hoja)
        return strlen(self->raiz->cadena);
    return self->raiz->longitud +
            (self->derecha != NULL ? getLongitud(self->derecha) : 0);
}


void join(rope_t *rope1, rope_t *rope2, rope_t *dest) {
    dest->izquierda = rope1;
    dest->derecha = rope2;

    nodo_t *raiz = malloc(sizeof(nodo_t));
    nodoNoHojaCreate(raiz, getLongitud(dest->izquierda));
    dest->raiz = raiz;
}

void split(int pos, rope_t *original, rope_t *splitted) {
    if (original->raiz->tipo_nodo == hoja) {
        nodo_t *nodo_inicial = malloc(sizeof(nodo_t));
        char *cadena_inicial = malloc(sizeof(char) * (pos + 1));
        memset(cadena_inicial, '\0', pos + 1);
        strncpy(cadena_inicial, original->raiz->cadena, pos);
        nodoHojaCreate(nodo_inicial, cadena_inicial);
        free(cadena_inicial);

        nodo_t *nodo_final = malloc(sizeof(nodo_t));
        const int len = sizeof(char) *
                (strlen(original->raiz->cadena) - pos + 1);
        char *cadena_final = malloc(len);
        snprintf(cadena_final, len, "%s", &original->raiz->cadena[pos]);
        nodoHojaCreate(nodo_final, cadena_final);
        free(cadena_final);

        nodoDestroy(original->raiz);
        free(original->raiz);
        original->raiz = nodo_inicial;
        splitted->raiz = nodo_final;
        return;
    }

    if (original->raiz->longitud < pos) {
        split(pos - original->raiz->longitud, original->derecha, splitted);
    } else {
        original->raiz->longitud = pos;
        split(pos, original->izquierda, splitted);
        rope_t *last_splitted = malloc(sizeof(rope_t));
        *last_splitted = *splitted;
        join(last_splitted, original->derecha, splitted);
        original->derecha = NULL;
    }
}

void insert(rope_t *self, int pos, char *str, rope_t *dest) {
    if (pos < 0)
        pos = getLongitud(self) + pos + 1;
    rope_t *splitted = malloc(sizeof(rope_t));
    split(pos, self, splitted);
    rope_t *inserted = malloc(sizeof(rope_t));
    ropeCreate(inserted, str);
    rope_t *full = malloc(sizeof(rope_t));
    join(self, inserted, full);
    join(full, splitted, dest);
}

void delete(rope_t *beggining, int pos_ini, int pos_fin, rope_t *full) {
    if (pos_ini < 0)
        pos_ini = getLongitud(beggining) + pos_ini + 1;
    if (pos_fin < 0)
        pos_fin = getLongitud(beggining) + pos_fin + 1;
    rope_t *ending = malloc(sizeof(rope_t));
    split(pos_fin, beggining, ending);
    rope_t *mid = malloc(sizeof(rope_t));
    split(pos_ini, beggining, mid);
    ropeDestroy(mid);
    join(beggining, ending, full);
}
