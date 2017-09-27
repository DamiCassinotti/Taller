#include <iostream>
#include <regex>
#include "File.h"
#include "LineProcessor.h"
#include "EchoProcessor.h"
#include "MatchProcessor.h"
#include "ReplaceProcessor.h"
#include "Processors.h"

using namespace std;

#define INPUT_NAME "--input"
#define OUTPUT_NAME "--output"
#define DEBUG_NAME "--debug"
#define ECHO_NAME "echo"
#define MATCH_NAME "match"
#define REPLACE_NAME "replace"

int main(int argc, char *argv[]) {
    File input(stdin);
    File output(stdout);
    Processors processors;
    list<string> inputs;
    inputs.emplace_back();
    map<string, int> processors_type_count = {{ECHO_NAME, 0}, {MATCH_NAME, 0}, {REPLACE_NAME, 0}};
    for (int i = 1; i < argc; i++) {
        string param(argv[i]);
        if (param == INPUT_NAME) {
            input.changeFile(argv[i + 1], "r");
        } else if (param == OUTPUT_NAME) {
            output.changeFile(argv[i + 1], "w");
        } else if (param == DEBUG_NAME) {

        } else if (param == ECHO_NAME) {
            processors_type_count[ECHO_NAME]++;
            string echoname(ECHO_NAME + std::to_string(processors_type_count[ECHO_NAME]));
            string& last_input = inputs.back();
            inputs.emplace_back();
            LineProcessor* echo = new EchoProcessor(echoname, last_input, inputs.back());
            processors.append(echo);
            if (i + 1 < argc && string(argv[i + 1]) != "::")
                return 0;
        } else if (param == MATCH_NAME) {
            processors_type_count[MATCH_NAME]++;
            string matchName(MATCH_NAME + std::to_string(processors_type_count[MATCH_NAME]));
            regex reg(argv[i + 1]);
            string& last_input = inputs.back();
            inputs.emplace_back();
            LineProcessor* match = new MatchProcessor(matchName, last_input, inputs.back(), reg);
            processors.append(match);
            if (i + 2 < argc && string(argv[i + 2]) != "::")
                return 0;
        } else if (param == REPLACE_NAME) {
            processors_type_count[REPLACE_NAME]++;
            string replaceName(REPLACE_NAME + std::to_string(processors_type_count[REPLACE_NAME]));
            regex reg(argv[i + 1]);
            string replacement(argv[i + 2]);
            string& last_input = inputs.back();
            inputs.emplace_back();
            LineProcessor* replace = new ReplaceProcessor(replaceName, last_input, inputs.back(), reg, replacement);
            processors.append(replace);
            if (i + 3 < argc && string(argv[i + 3]) != "::") {
                return 0;
            }
        }
    }
    inputs.front() = input.readLine();
    while (input.onEof() == 0) {
        for (LineProcessor* processor : processors) {
            processor->run();
        }
        output.writeLine(inputs.back());
        inputs.front() = input.readLine();
    }
    return 0;
}