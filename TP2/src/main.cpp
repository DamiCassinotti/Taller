#include <iostream>
#include <regex>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <unistd.h>
#include "File.h"
#include "Threads.h"
#include "BlockingString.h"

#define INPUT_NAME "--input"
#define OUTPUT_NAME "--output"
#define DEBUG_NAME "--debug"
#define ECHO_NAME "echo"
#define MATCH_NAME "match"
#define REPLACE_NAME "replace"
#define ERROR 1
#define OK 0

int main(int argc, char *argv[]) {
    if (argc < 2)
        return ERROR;
    File input(stdin);
    File output(stdout);
    Threads threads;
    std::list<BlockingString> inputs;
    // Agrego un BlockingString nuevo a la lista
    inputs.emplace_back();
    Logger logger;
    std::map<std::string, int> processors_type_count = {{ECHO_NAME, 0},
                                                        {MATCH_NAME, 0},
                                                        {REPLACE_NAME, 0}};
    for (int i = 1; i < argc; i++) {
        std::string param(argv[i]);
        if (param == INPUT_NAME) {
            // Si tengo el parámetro '--input', cambio el archivo de entrada
            std::ifstream f(argv[i + 1]);
            if (!f.good())
                return ERROR;
            input.changeFile(argv[i + 1], "r");
        } else if (param == OUTPUT_NAME) {
            // Si tengo el parámetro '--output', cambio el archivo de salida
            output.changeFile(argv[i + 1], "w");
        } else if (param == DEBUG_NAME) {
            // Si tengo el parámetro 'debug', el logger debe guardar las salidas
            logger.setShouldLog(true);
        } else if (param == ECHO_NAME) {
            // Genero un comando echo
            processors_type_count[ECHO_NAME]++;
            std::string echoname(ECHO_NAME +
                         std::to_string(processors_type_count[ECHO_NAME]));
            BlockingString& last_input = inputs.back();
            inputs.emplace_back();
            threads.addEchoThread(echoname, last_input, inputs.back(), logger);
            // Si luego no está el separador de comandos, salgo
            if (i + 1 < argc && std::string(argv[i + 1]) != "::")
                return ERROR;
        } else if (param == MATCH_NAME) {
            // Genero un comando match
            processors_type_count[MATCH_NAME]++;
            std::string matchName(MATCH_NAME +
                         std::to_string(processors_type_count[MATCH_NAME]));
            std::regex reg(argv[i + 1]);
            BlockingString& last_input = inputs.back();
            inputs.emplace_back();
            threads.addMatchThread(matchName, last_input, inputs.back(),
                                      reg, logger);
            // Si luego no está el separador de comandos, salgo
            if (i + 2 < argc && std::string(argv[i + 2]) != "::")
                return ERROR;
        } else if (param == REPLACE_NAME) {
            // Genero un comando replace
            processors_type_count[REPLACE_NAME]++;
            std::string replaceName(REPLACE_NAME +
                        std::to_string(processors_type_count[REPLACE_NAME]));
            std::regex reg(argv[i + 1]);
            std::string replacement(argv[i + 2]);
            BlockingString& last_input = inputs.back();
            inputs.emplace_back();
            threads.addReplaceThread(replaceName, last_input, inputs.back(),
                                        reg, replacement, logger);
            // Si luego no está el separador de comandos, salgo
            if (i + 3 < argc && std::string(argv[i + 3]) != "::")
                return ERROR;
        }
    }
    // Agrego los thread de lectura y escritura
    threads.addReaderThread(input, inputs.front());
    threads.addWriterThread(output, inputs.back());
    threads.start();
    threads.join();
    logger.finnishLogging();
    return OK;
}
