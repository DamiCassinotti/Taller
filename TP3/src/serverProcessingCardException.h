#ifndef TP3_SERVERPROCESSINGCARDEXCEPTION_H
#define TP3_SERVERPROCESSINGCARDEXCEPTION_H

#include <exception>
#include <string>

class serverProcessingCardException {
private:
    std::string errcode;
public:
    explicit serverProcessingCardException(std::string errcode);
    std::string what() const;
    ~serverProcessingCardException();
};


#endif //TP3_SERVERPROCESSINGCARDEXCEPTION_H
