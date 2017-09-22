#include <iostream>
#include <regex>
#include "File.h"
#include "LineProcessor.h"
#include "EchoProcessor.h"
#include "MatchProcessor.h"
#include "ReplaceProcessor.h"
#include "Processors.h"

using namespace std;

int main(int argc, char *argv[]) {
    File input(stdin);
    File output(stdout);
    Processors processors;
    string input_inicial;
    string* input_str = &input_inicial;
    string output_inicial;
    string* output_str = &output_inicial;
    for (int i = 1; i < argc; i++) {
        string param(argv[i]);
        if (param == "--input") {
            input = File(argv[i + 1], "r");
        } else if (param == "--output") {
            output = File(argv[i + 1], "w");
        } else if (param == "echo") {
            LineProcessor* echo = new EchoProcessor(*input_str, *output_str);
            processors.append(echo);
        } else if (param == "match") {
            regex reg(argv[i + 1]);
            LineProcessor* match = new MatchProcessor(*input_str, *output_str, reg);
            processors.append(match);
        } else if (param == "replace") {
            regex reg(argv[i + 1]);
            string replacement(argv[i + 2]);
            LineProcessor* replace = new ReplaceProcessor(*input_str, *output_str, reg, replacement);
            processors.append(replace);
        }
        string siguiente_output;
        input_str = output_str;
        *output_str = siguiente_output;
    }
    input_inicial = input.readLine();
    while (input.onEof() == 0) {
        for (LineProcessor* processor : processors) {
            processor->run();
        }
        output.writeLine(processors.back()->getOutput());
        input_inicial = input.readLine();
    }
    return 0;
}