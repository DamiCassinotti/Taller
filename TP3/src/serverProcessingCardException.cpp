#include "serverProcessingCardException.h"

serverProcessingCardException::serverProcessingCardException(
        std::string errcode) : errcode(errcode) {}

std::string serverProcessingCardException::what() const {
    return errcode;
}

serverProcessingCardException::~serverProcessingCardException() {}
