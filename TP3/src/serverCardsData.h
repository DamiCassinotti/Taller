#ifndef TP3_SERVERCARDSDATA_H
#define TP3_SERVERCARDSDATA_H

#include <mutex>
#include <map>
#include <string>
#include "serverProcessingCardException.h"

#define ERROR_TARJETA_INEXISTENTE "E00002"
#define ERROR_MONTO_INVALIDO "E00003"
#define ERROR_TARJETA_EXISTENTE "E00004"

class serverCardsData {
private:
    std::mutex mtx;
    std::map<std::string, int> cards;
public:
    serverCardsData();
    ~serverCardsData();
    int addAmmountAndGetBalanceIfCardExists(std::string card, int ammount);
    int forceAddAmmountAndGetBalanceIfCardsExists(std::string card,
                                                  int ammount);
    int getBalanceIfCardExists(std::string card);
    void registerCardIfDoesntExist(std::string card);
    void setBalanceIfCardExists(std::string card, int balance);
};


#endif //TP3_SERVERCARDSDATA_H
