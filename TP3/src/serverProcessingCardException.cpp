#include "serverProcessingCardException.h"
#include <string>

serverProcessingCardException::serverProcessingCardException(
        const std::string &errcode) : errcode(errcode) {}

std::string serverProcessingCardException::what() const {
    return errcode;
}

serverProcessingCardException::~serverProcessingCardException() = default;
