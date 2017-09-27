#ifndef TP2_REPLACEPROCESSOR_H
#define TP2_REPLACEPROCESSOR_H

#include <regex>
#include "LineProcessor.h"
using namespace std;

class ReplaceProcessor : public LineProcessor {
private:
    regex rgx;
    string replacement;
public:
    ReplaceProcessor(string name, string &input, string &output, regex rgx, string replacement);
    void run() override;
    ~ReplaceProcessor();
};

#endif //TP2_REPLACEPROCESSOR_H
