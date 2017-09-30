#ifndef TP2_MATCHPROCESSOR_H
#define TP2_MATCHPROCESSOR_H

#include <regex>
#include <string>
#include "LineProcessor.h"

class MatchProcessor : public LineProcessor {
private:
    std::regex rgx;
public:
    MatchProcessor(std::string name, BlockingString &input, BlockingString
                    &output, std::regex rgx, Logger &logger);
    void run() override;
    ~MatchProcessor();
};

#endif //TP2_MATCHPROCESSOR_H
