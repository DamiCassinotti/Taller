#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rope.h"

void doTest(char *test_name, int actual_value, int expected) {
    char *result = actual_value == expected ? "OK" : "ERROR";
    printf("%s: %s\n", test_name, result);
}

int main_test() {
    rope_t *rope1 = malloc(sizeof(rope_t));
    ropeCreate(rope1, "");
    char *result_str1 = getString(rope1);
    doTest("TEST - creo rope con cadena vacia", strcmp("", result_str1), 0);
    doTest("TEST - La longitud de un arbol 'vacio' es 0", getLongitud(rope1), 0);

    rope_t *rope2 = malloc(sizeof(rope_t));
    ropeCreate(rope2, "Hello, World!");
    char *result_str2 = getString(rope2);
    doTest("TEST - creo rope con cadena no vacia", strcmp("Hello, World!", result_str2), 0);
    doTest("TEST - La longitud de un arbol con 'Hello, World!' es 13", getLongitud(rope2), 13);

    rope_t *rope3 = malloc(sizeof(rope_t));
    ropeCreate(rope3, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
            "eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad "
            "minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid "
            "ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit "
            "esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat "
            "cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    char *result_str3 = getString(rope3);
    doTest("TEST - creo rope con Lorem Ipsum",
           strcmp("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
                          "eiusmod tempor incidunt ut labore et dolore magna aliqua. "
                          "Ut enim ad minim veniam, quis nostrud exercitation ullamco "
                          "laboris nisi ut aliquid ex ea commodi consequat. Quis aute "
                          "iure reprehenderit in voluptate velit esse cillum dolore eu "
                          "fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non "
                          "proident, sunt in culpa qui officia deserunt mollit anim id "
                          "est laborum.", result_str3), 0);

    rope_t *rope4 = malloc(sizeof(rope_t));
    ropeCreate(rope4, "Hola");
    char *result_str4 = getString(rope4);
    doTest("TEST - creo rope con cadena 'Hola'", strcmp("Hola", result_str4), 0);
    doTest("TEST - La longitud de un arbol con 'Hola' es 4", getLongitud(rope4), 4);

    rope_t *rope5 = malloc(sizeof(rope_t));
    ropeCreate(rope5, "Mundo");
    char *result_str5 = getString(rope5);
    doTest("TEST - creo rope con cadena 'Mundo'", strcmp("Mundo", result_str5), 0);
    doTest("TEST - La longitud de un arbol con 'Mundo' es 5", getLongitud(rope5), 5);

    rope_t *joined = malloc(sizeof(rope_t));
    join(rope4, rope5, joined);
    char *result_joined = getString(joined);
    doTest("TEST - Join de 'Hola' con 'Mundo'", strcmp("HolaMundo", result_joined), 0);
    doTest("TEST - La longitud de un arbol con 'HolaMundo' es 9", getLongitud(joined), 9);

    rope_t *rope7 = malloc(sizeof(rope_t));
    split(7, rope2, rope7);
    char *result_str_split = getString(rope2);
    doTest("TEST - split 'Hello, World!' en pos 7", strcmp("Hello, ", result_str_split), 0);
    doTest("TEST - La longitud de un arbol con 'Hello, ' es 7", getLongitud(rope2), 7);
    char *result_str7 = getString(rope7);
    doTest("TEST - split 'Hello, World!' en pos 7 (fin)", strcmp("World!", result_str7), 0);
    doTest("TEST - La longitud de un arbol con 'World!' es 6", getLongitud(rope7), 6);

    rope_t *rope8 = malloc(sizeof(rope_t));
    ropeCreate(rope8, "Hola");
    rope_t *rope9 = malloc(sizeof(rope_t));
    ropeCreate(rope9, "Mundo");
    rope_t *rope10 = malloc(sizeof(rope_t));
    join(rope8, rope9, rope10);
    rope_t *rope11 = malloc(sizeof(rope_t));
    split(7, rope10, rope11);
    char *result_str10 = getString(rope10);
    doTest("TEST - split 'HolaMundo' en pos 7 - Se splittea el nodo de la derecha", strcmp("HolaMun", result_str10), 0);
    doTest("TEST - La longitud de un arbol con 'HolaMun' es 7", getLongitud(rope10), 7);
    char *result_str11 = getString(rope11);
    doTest("TEST - split 'HolaMundo' en pos 7 - Se splittea el nodo de la derecha (fin)", strcmp("do", result_str11),
           0);
    doTest("TEST - La longitud de un arbol con 'do' es 2", getLongitud(rope11), 2);

    rope_t *rope12 = malloc(sizeof(rope_t));
    ropeCreate(rope12, "Hola");
    rope_t *rope13 = malloc(sizeof(rope_t));
    ropeCreate(rope13, "Mundo");
    rope_t *rope14 = malloc(sizeof(rope_t));
    join(rope12, rope13, rope14);
    rope_t *rope15 = malloc(sizeof(rope_t));
    split(4, rope14, rope15);
    char *result_str14 = getString(rope14);
    doTest("TEST - split 'HolaMundo' en pos 4 - Se splittea al final del nodo izquierdo", strcmp("Hola", result_str14),
           0);
    doTest("TEST - La longitud de un arbol con 'Hola' es 4", getLongitud(rope14), 4);
    char *result_str15 = getString(rope15);
    doTest("TEST - split 'HolaMundo' en pos 4 - Se splittea al final del nodo izquierdo (fin)",
           strcmp("Mundo", result_str15), 0);
    doTest("TEST - La longitud de un arbol con 'Mundo' es 5", getLongitud(rope15), 5);

    rope_t *rope16 = malloc(sizeof(rope_t));
    ropeCreate(rope16, "Hola");
    rope_t *rope17 = malloc(sizeof(rope_t));
    ropeCreate(rope17, "Mundo");
    rope_t *rope18 = malloc(sizeof(rope_t));
    join(rope16, rope17, rope18);
    rope_t *rope19 = malloc(sizeof(rope_t));
    split(3, rope18, rope19);
    char *result_str18 = getString(rope18);
    doTest("TEST - split 'HolaMundo' en pos 3 - Se splittea a la mitad del nodo izquierdo", strcmp("Hol", result_str18),
           0);
    doTest("TEST - La longitud de un arbol con 'Hol' es 3", getLongitud(rope18), 3);
    char *result_str19 = getString(rope19);
    doTest("TEST - split 'HolaMundo' en pos 3 - Se splittea a la mitad del nodo izquierdo (fin)",
           strcmp("aMundo", result_str19), 0);
    doTest("TEST - La longitud de un arbol con 'aMundo' es 6", getLongitud(rope19), 6);


    // Tests de insert y delete
    rope_t *rope20 = malloc(sizeof(rope_t));
    ropeCreate(rope20, "Hodo");
    rope_t *rope21 = malloc(sizeof(rope_t));
    insert(rope20, 2, "la, Mun", rope21);
    char *result_str21 = getString(rope21);
    doTest("TEST - insert 'la, Mun' en pos 2 de 'Hodo' es 'Hola, Mundo", strcmp("Hola, Mundo", result_str21), 0);
    doTest("TEST - La longitud de un arbol con 'Hola, Mundo' es 11", getLongitud(rope21), 11);
    rope_t *rope22 = malloc(sizeof(rope_t));
    insert(rope21, -1, "!", rope22);
    char *result_str22 = getString(rope22);
    doTest("TEST - insert '!' en pos -1 de 'Hola, Mundo' es 'Hola, Mundo!", strcmp("Hola, Mundo!", result_str22), 0);
    doTest("TEST - La longitud de un arbol con 'Hola, Mundo!' es 12", getLongitud(rope22), 12);
    rope_t* rope23 = malloc(sizeof(rope_t));
    delete(rope22, 4, 6, rope23);
    char* result_str23 = getString(rope23);
    doTest("TEST - delete desde 4 a 6 de 'Hola, Mundo' es 'HolaMundo!", strcmp("HolaMundo!", result_str23), 0);
    doTest("TEST - La longitud de un arbol con 'HolaMundo!' es 10", getLongitud(rope23), 10);

    // Casos de prueba de uno de los archivos del SERCOM
    rope_t* rope24 = malloc(sizeof(rope_t));
    ropeCreate(rope24, "I-will-tell-you-three-things");
    rope_t* rope25 = malloc(sizeof(rope_t));
    insert(rope24, -1, "\n", rope25);
    rope_t* rope26 = malloc(sizeof(rope_t));
    insert(rope25, -1, "If-I-tell-them-to-you-and-they-come-true,", rope26);
    rope_t* rope27 = malloc(sizeof(rope_t));
    insert(rope26, -1, "\n", rope27);
    rope_t* rope28 = malloc(sizeof(rope_t));
    insert(rope27, -1, "then-will-you-believe-me?", rope28);
    rope_t* rope29 = malloc(sizeof(rope_t));
    insert(rope28, -1, "\n", rope29);
    rope_t* rope30 = malloc(sizeof(rope_t));
    insert(rope29, -1, "\n", rope30);
    char* result_sercom_test = getString(rope30);
    doTest("TEST - SERCOM", strcmp("I-will-tell-you-three-things\nIf-I-tell-them-to-you-and-they-come-true,\nthen-will-you-believe-me?\n\n", result_sercom_test), 0);
    rope_t* rope31 = malloc(sizeof(rope_t));
    delete(rope30, 0, -1, rope31);
    char* result_sercom_test_empty = getString(rope30);
    doTest("TEST - Se vacia lo del SERCOM", strcmp("", result_sercom_test_empty), 0);


    free(result_str1);
    ropeDestroy(rope1);

    free(result_str2);
    ropeDestroy(rope2);

    free(result_str3);
    ropeDestroy(rope3);

    free(result_joined);
    ropeDestroy(joined);

    free(result_str4);

    free(result_str5);

    free(result_str_split);
    free(result_str7);
    ropeDestroy(rope7);

    free(result_str10);
    free(result_str11);
    ropeDestroy(rope10);
    ropeDestroy(rope11);

    free(result_str14);
    free(result_str15);
    ropeDestroy(rope14);
    ropeDestroy(rope15);

    free(result_str18);
    free(result_str19);
    ropeDestroy(rope18);
    ropeDestroy(rope19);

    free(result_str21);
    free(result_str22);
    free(result_str23);
    ropeDestroy(rope23);

    free(result_sercom_test);
    free(result_sercom_test_empty);
    ropeDestroy(rope31);

    return 0;
}
