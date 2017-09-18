#ifndef TP1_LECTURA_H
#define TP1_LECTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

// Funcion auxiliar para ingreso de texto por teclado/archivo
// Pre: -
// Post: Devuelve un puntero a una porcion de memoria con el texto indicado.
// En caso de fallar, devuelve NULL
// Recordar: La memoria es reservada dentro de la funcion, el usuario deberia
// de liberarla.
char* leerLineaArchivo(FILE* file);

#endif //TP1_LECTURA_H
