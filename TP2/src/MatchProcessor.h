#ifndef TP2_MATCHPROCESSOR_H
#define TP2_MATCHPROCESSOR_H

#include <regex>
#include "LineProcessor.h"
using namespace std;

class MatchProcessor : public LineProcessor {
private:
    regex rgx;
public:
    MatchProcessor(string name, string &input, string &output, regex rgx);
    void run() override;
    ~MatchProcessor();
};

#endif //TP2_MATCHPROCESSOR_H
