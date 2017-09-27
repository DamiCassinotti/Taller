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
            input.changeFile(argv[i + 1], "r");
        } else if (param == "--output") {
            output.changeFile(argv[i + 1], "w");
        } else if (param == "echo") {
            string echoname("echo");
            LineProcessor* echo = new EchoProcessor(echoname, *input_str, *output_str);
            processors.append(echo);
            if (i + 1 < argc && string(argv[i + 1]) != "::")
                return 0;
        } else if (param == "match") {
            string matchName("echo");
            regex reg(argv[i + 1]);
            LineProcessor* match = new MatchProcessor(matchName, *input_str, *output_str, reg);
            processors.append(match);
            if (i + 2 < argc && string(argv[i + 2]) != "::")
                return 0;
        } else if (param == "replace") {
            string replaceName("replace");
            regex reg(argv[i + 1]);
            string replacement(argv[i + 2]);
            LineProcessor* replace = new ReplaceProcessor(replaceName, *input_str, *output_str, reg, replacement);
            processors.append(replace);
            if (i + 3 < argc && string(argv[i + 3]) != "::") {
                return 0;
            }
        }
        string siguiente_output;
        input_str = output_str;
        *output_str = siguiente_output;
    }
    input_inicial = input.readLine();
    while (input.onEof() == 0) {
        cout << input_inicial << "\n";
        for (LineProcessor* processor : processors) {
            processor->run();
        }
        output.writeLine(processors.back()->getOutput());
        input_inicial = input.readLine();
    }
    return 0;
}