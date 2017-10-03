#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include "commonSocket.h"
#include "commonFile.h"

#define OK 0;
#define PORT_POSITION 1
#define COMMAND_LENGTH 1
#define CARD_LENGTH 10
#define AMMOUNT_LENGTH 10
#define ERROR_TARJETA_INEXISTENTE "E00002"
#define ERROR_MONTO_INVALIDO "E00003"
#define ERROR_TARJETA_EXISTENTE "E00004"
#define ERROR_MSG_LENGTH 6
#define SUCCESS_MSG_LENGTH_BASIC 11 // Para los registros (envio sin monto)
#define SUCCESS_MSG_LENGTH_FULL 21 //Para los demás comandos (envío con monto)

void printErrMsg(std::string& command, std::string& card, std::string& ammount,
                 std::string& output){
    std::cerr << command << card << ammount << " -> " << output << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2)
        return OK;
    std::string port(argv[PORT_POSITION]);
    commonSocket sock;
    sock.accept(port);
    bool are_we_connected = true;
    std::map<std::string, int> cards;
    while (are_we_connected) {
        std::string command;
        std::string card;
        std::string ammount;
        std::string response;
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
        if (!cards.count(card) && command != "R") {
            // Si la tarjeta no existe, devuelvo error
            // Pero solo si no quiero registrarla
            response = ERROR_TARJETA_INEXISTENTE;
            printErrMsg(command, card, ammount, response);
            sock.send(response, ERROR_MSG_LENGTH);
            continue;
        }
        if (command == "A") {
            if (cards[card] + monto < 0) {
                response = ERROR_TARJETA_INEXISTENTE;
                printErrMsg(command, card, ammount, response);
                sock.send(response, ERROR_MSG_LENGTH);
                continue;
            }
            cards[card] += monto;
        } else if (command == "F") {
            cards[card] += monto;
        } else if (command == "P") {
            //response = ()
        } else if (command == "R") {
            if (cards.count(card)) {
                response = ERROR_TARJETA_EXISTENTE;
                printErrMsg(command, card, ammount, response);
                sock.send(response, ERROR_MSG_LENGTH);
                continue;
            }
            cards[card] = 0;
            response = command + card;
        } else if (command == "S") {
            cards[card] = monto;
        }

        std::stringstream stream;
        stream << command;
        stream << std::setfill('0') << std::setw(10) << card;
        int msg_length = SUCCESS_MSG_LENGTH_BASIC;
        if (command != "R") {
            // Si registré la tarjeta no tengo que devolver el saldo
            stream << std::setfill('0') << std::setw(10) << cards[card];
            msg_length = SUCCESS_MSG_LENGTH_FULL;
        }

        std::cout << command << card << ammount << " -> " <<stream.str()<<"\n";
        sock.send(stream.str(), msg_length);

    }
    return 0;
}

