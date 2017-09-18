#include <iostream>
#include "File.h"
using namespace std;

int main(int argc, char *argv[]) {
    File input("test.txt", "r");
    while (input.onEof() == 0) {
        cout << "Linea: " << input.leerLinea() << "\n";
    }
}