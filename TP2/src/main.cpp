#include <iostream>
#include <regex>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include "File.h"
#include "LineProcessor.h"
#include "EchoProcessor.h"
#include "MatchProcessor.h"
#include "ReplaceProcessor.h"
#include "Processors.h"

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
    Processors processors;
    std::list<std::string> inputs;
    inputs.emplace_back();
    Logger logger;
    bool should_log = false;
    std::map<std::string, int> processors_type_count = {{ECHO_NAME, 0},
                                                        {MATCH_NAME, 0},
                                                        {REPLACE_NAME, 0}};
    for (int i = 1; i < argc; i++) {
        std::string param(argv[i]);
        if (param == INPUT_NAME) {
            std::ifstream f(argv[i + 1]);
            if (!f.good())
                return ERROR;
            input.changeFile(argv[i + 1], "r");
        } else if (param == OUTPUT_NAME) {
            output.changeFile(argv[i + 1], "w");
        } else if (param == DEBUG_NAME) {
            should_log = true;
        } else if (param == ECHO_NAME) {
            processors_type_count[ECHO_NAME]++;
            std::string echoname(ECHO_NAME +
                         std::to_string(processors_type_count[ECHO_NAME]));
            std::string& last_input = inputs.back();
            inputs.emplace_back();
            LineProcessor* echo = new EchoProcessor(echoname, last_input,
                                                    inputs.back(), logger);
            processors.append(echo);
            if (i + 1 < argc && std::string(argv[i + 1]) != "::")
                return ERROR;
        } else if (param == MATCH_NAME) {
            processors_type_count[MATCH_NAME]++;
            std::string matchName(MATCH_NAME +
                         std::to_string(processors_type_count[MATCH_NAME]));
            std::regex reg(argv[i + 1]);
            std::string& last_input = inputs.back();
            inputs.emplace_back();
            LineProcessor* match = new MatchProcessor(matchName, last_input,
                                                  inputs.back(), reg, logger);
            processors.append(match);
            if (i + 2 < argc && std::string(argv[i + 2]) != "::")
                return ERROR;
        } else if (param == REPLACE_NAME) {
            processors_type_count[REPLACE_NAME]++;
            std::string replaceName(REPLACE_NAME +
                        std::to_string(processors_type_count[REPLACE_NAME]));
            std::regex reg(argv[i + 1]);
            std::string replacement(argv[i + 2]);
            std::string& last_input = inputs.back();
            inputs.emplace_back();
            LineProcessor* replace = new ReplaceProcessor(replaceName,
                          last_input, inputs.back(), reg, replacement, logger);
            processors.append(replace);
            if (i + 3 < argc && std::string(argv[i + 3]) != "::") {
                return ERROR;
            }
        }
    }
    inputs.front() = input.readLine();
    while (input.onEof() == 0) {
        for (LineProcessor* processor : processors) {
            processor->run();
        }
        if (inputs.back() != "")
            output.writeLine(inputs.back());
        inputs.front() = input.readLine();
    }
    if (should_log)
        logger.finnishLogging();
    return OK;
}
