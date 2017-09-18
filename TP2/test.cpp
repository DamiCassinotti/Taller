#include <iostream>
#include <algorithm>
#include "EchoProcessor.h"
#include "MatchProcessor.h"
#include "ReplaceProcessor.h"

void doTest(string test_name, string actual_value, string expected) {
    string result = actual_value == expected ? "OK" : ("ERROR - actual: " + actual_value);
    cout << "TEST - " << test_name << ": " << result << "\n";
}

int main2(int argc, char *argv[]) {
    string input("Hola");
    string output = "Chau";
    regex reg_match("(tra)(.*)");
    regex reg_replace("\\b(e)");
    string replace("tuvieja");
    EchoProcessor echoP(input, output);
    MatchProcessor matchP(input, output, reg_match);
    ReplaceProcessor replaceP(input, output, reg_replace, replace);

    // Tests de enunciado
    // Test de Echo
    echoP.run();
    doTest("Echo devuelve lo mismo que le mandé", echoP.getOutput(), "Hola");
    matchP.run();
    doTest("Match devuelve vacio porque no matchea", matchP.getOutput(), "");
    replaceP.run();
    doTest("Replace no reemplaza nada", replaceP.getOutput(), "Hola");

    // Test de Echo
    input = "trabajo práctico";
    echoP.run();
    doTest("Echo devuelve lo mismo que le mandé", echoP.getOutput(), "trabajo práctico");
    matchP.run();
    doTest("Match no devuelve vacio porque matchea", matchP.getOutput(), "trabajo práctico");
    replaceP.run();
    doTest("Replace no reemplaza nada", replaceP.getOutput(), "trabajo práctico");
    input = "pipeline";
    echoP.run();
    doTest("Echo devuelve lo mismo que le mandé", echoP.getOutput(), "pipeline");
    matchP.run();
    doTest("Match devuelve vacio porque no matchea", matchP.getOutput(), "");
    replaceP.run();
    doTest("Replace no reemplaza nada", replaceP.getOutput(), "pipeline");

    // Tests de replace
    input = "hola";
    echoP.run();
    doTest("Echo devuelve lo mismo que le mandé", echoP.getOutput(), "hola");
    matchP.run();
    doTest("Match devuelve vacio porque no matchea", matchP.getOutput(), "");
    replaceP.run();
    doTest("Replace no reemplaza nada", replaceP.getOutput(), "hola");
    input = "ejemplo de entrada";
    echoP.run();
    doTest("Echo devuelve lo mismo que le mandé", echoP.getOutput(), "ejemplo de entrada");
    matchP.run();
    doTest("Match devuelve vacio porque no matchea", matchP.getOutput(), "");
    replaceP.run();
    doTest("Replace reemplaza nada", replaceP.getOutput(), "tuviejajemplo de tuviejantrada");

    return 0;
}