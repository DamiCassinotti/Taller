#include <iostream>
#include "EchoProcessor.h"
using namespace std;

int main(int argc, char *argv[]) {
    string input("Hola");
    string output("Chau");
    LineProcessor* echoP = new EchoProcessor(&input, &output);
    echoP->run();
    cout << "El output del echo es " << echoP->getOutput() << "\n";
    delete echoP;
}