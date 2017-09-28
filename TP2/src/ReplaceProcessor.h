#ifndef TP2_REPLACEPROCESSOR_H
#define TP2_REPLACEPROCESSOR_H

#include <regex>
#include <string>
#include "LineProcessor.h"

class ReplaceProcessor : public LineProcessor {
private:
    std::regex rgx;
    std::string replacement;
public:
    ReplaceProcessor(std::string name, std::string &input, std::string &output,
                     std::regex rgx, std::string replacement, Logger &logger);
    void run() override;
    ~ReplaceProcessor();
};

#endif //TP2_REPLACEPROCESSOR_H
