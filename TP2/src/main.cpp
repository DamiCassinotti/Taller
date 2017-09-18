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
    string input_str;
    string output_str;
    for (int i = 1; i < argc; i++) {
        string param(argv[i]);
        if (param == "--input") {
            input = File(argv[i + 1], "r");
        } else if (param == "--output") {
            output = File(argv[i + 1], "w");
        } else if (param == "echo") {
            LineProcessor* echo = new EchoProcessor(input_str, output_str);
            processors.append(echo);
        } else if (param == "match") {
            regex reg(argv[i + 1]);
            LineProcessor* match = new MatchProcessor(input_str, output_str, reg);
            processors.append(match);
        } else if (param == "replace") {
            regex reg(argv[i + 1]);
            string replacement(argv[i + 2]);
            LineProcessor* replace = new ReplaceProcessor(input_str, output_str, reg, replacement);
            processors.append(replace);
        }
    }
    while (input.onEof() == 0) {
        input_str = input.readLine();
        for (LineProcessor* processor : processors) {
            processor->run();
        }
        output.writeLine(processors.back()->getOutput());
    }
    return 0;
}