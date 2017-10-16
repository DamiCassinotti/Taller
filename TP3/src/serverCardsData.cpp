#include "serverCardsData.h"
#include <string>

serverCardsData::serverCardsData() = default;
serverCardsData::~serverCardsData() = default;

int serverCardsData::addAmmountAndGetBalanceIfCardExists(std::string card,
                                                         int ammount) {
    std::lock_guard<std::mutex> lock(mtx);
    // Si la tarjeta no existe, lanzo excepcion
    if (!cards.count(card))
        throw serverProcessingCardException(ERROR_TARJETA_INEXISTENTE);
    // Si estoy descontando y el monto me queda menor a cero, lanzo excepcion
    if (ammount < 0 && cards[card] + ammount < 0)
        throw serverProcessingCardException(ERROR_MONTO_INVALIDO);
    // Si no, le sumo el monto a agregar
    cards[card] += ammount;
    return cards[card];
}

int serverCardsData::forceAddAmmountAndGetBalanceIfCardsExists(std::string card,
                                                               int ammount) {
    std::lock_guard<std::mutex> lock(mtx);
    // Si la tarjeta no existe, lanzo excepcion
    if (!cards.count(card))
        throw serverProcessingCardException(ERROR_TARJETA_INEXISTENTE);
    // Si no, actualizo el monto
    cards[card] += ammount;
    return cards[card];
}

int serverCardsData::getBalanceIfCardExists(std::string card) {
    std::lock_guard<std::mutex> lock(mtx);
    // Si la tarjeta no existe, lanzo excepcion
    if (!cards.count(card))
        throw serverProcessingCardException(ERROR_TARJETA_INEXISTENTE);
    return cards[card];
}

void serverCardsData::registerCardIfDoesntExist(std::string card) {
    std::lock_guard<std::mutex> lock(mtx);
    // Si la tarjeta existe, lanzo excepcion
    if (cards.count(card))
        throw serverProcessingCardException(ERROR_TARJETA_EXISTENTE);
    cards[card] = 0;
}

void serverCardsData::setBalanceIfCardExists(std::string card, int balance) {
    std::lock_guard<std::mutex> lock(mtx);
    // Si la tarjeta no existe, lanzo excepcion
    if (!cards.count(card))
        throw serverProcessingCardException(ERROR_TARJETA_INEXISTENTE);
    cards[card] = balance;
}
