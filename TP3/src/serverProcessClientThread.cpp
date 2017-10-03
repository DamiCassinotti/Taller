#include <iostream>
#include <iomanip>
#include <sstream>
#include "serverProcessClientThread.h"

serverProcessClientThread::serverProcessClientThread(commonSocket &sock,
                                                     serverCardsData &cards,
                                     serverConnectionData &is_server_connected):
        sock(sock), cards(cards), is_server_connected(is_server_connected) {
    are_we_connected = true;
}

void serverProcessClientThread::run() {
    while (are_we_connected && is_server_connected.getConnected()) {
        std::string command;
        std::string card;
        std::string ammount;
        int monto = 0;
        int res = sock.recv(command, COMMAND_LENGTH);
        if (res <= 0) {
            are_we_connected = false;
            continue;
        }
        res = sock.recv(card, CARD_LENGTH);
        if (res <= 0) {
            are_we_connected = false;
            continue;
        }
        if (command == "A" || command == "F" || command == "S") {
            // Para estos comandos tengo que pedir el monto
            res = sock.recv(ammount, AMMOUNT_LENGTH);
            if (res <= 0) {
                are_we_connected = false;
                continue;
            }
            monto = std::stoi(ammount);
        }
        int monto_final = 0;
        try {
            if (command == "A") {
                monto_final = cards.addAmmountAndGetBalanceIfCardExists(card,
                                                                        monto);
            } else if (command == "F") {
                monto_final = cards.forceAddAmmountAndGetBalanceIfCardsExists
                        (card, monto);
            } else if (command == "S") {
                monto_final = cards.getBalanceIfCardExists(card);
            } else if (command == "R") {
                cards.registerCardIfDoesntExist(card);
            } else if (command == "S") {
                cards.setBalanceIfCardExists(card, monto);
                monto_final = monto;
            }
        } catch (const serverProcessingCardException& e) {
            std::cerr << command << card << ammount << " -> " << e.what()<<"\n";
            sock.send(e.what(), ERROR_MSG_LENGTH);
            continue;
        }

        std::stringstream stream;
        stream << command;
        stream << std::setfill('0') << std::setw(10) << card;
        int msg_length = SUCCESS_MSG_LENGTH_BASIC;
        if (command != "R") {
            // Si registré la tarjeta no tengo que devolver el saldo
            stream << std::setfill('0') << std::setw(10) << monto_final;
            msg_length = SUCCESS_MSG_LENGTH_FULL;
        }

        std::cout << command << card << ammount << " -> " <<stream.str()<<"\n";
        sock.send(stream.str(), msg_length);

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    }
}

serverProcessClientThread::~serverProcessClientThread() {}
