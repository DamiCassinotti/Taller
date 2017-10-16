#include <string>
#include <iostream>
#include <bitset>
#include <sstream>
#include <iomanip>
#include "commonSocket.h"
#include "commonFile.h"
#include "clientBinaryFile.h"
#include "clientOperations.h"
#include "clientNoMoreToReadException.h"

#define OK 0;
#define HOST_POSITION 1
#define PORT_POSITION 2
#define FILE_POSITION 3
#define METADATA_SIZE 16
#define PADDING_SIZE 3
#define OPCODE_SIZE 3
#define MONTO_CHECKSUM_SIZE 5
#define CARD_CHEKSUM_SIZE 5
#define CHECKSUM_ERROR "E00001";
#define SERVER_MSG_BASIC 11 //Mensaje sin monto
#define SERVER_MSG_FULL 21 //Mensaje con monto
#define COMMAND_LENGTH_FROM_SERVER 1
#define CARD_LENGTH_FROM_SERVER 10
#define AMMOUNT_LENGTH_FROM_SERVER 10
#define ERRCODE_LENGTH_FROM_SERVER 5

std::string getMessageWithoutAmmount(const std::string& command,
                                     unsigned int card);
std::string getMessageWithAmmount(const std::string& command,
                                  unsigned int card, int ammount);
void showChecksumErrorWithAmmount(const std::string& command,
                                         unsigned int card, int ammount);
void showChecksumErrorWithoutAmmount(const std::string& command,
                                            unsigned int card);
bool validateCheacksum(std::bitset<32> metadata, std::bitset<5> checksum);

int main(int argc, char* argv[]) {
    if (argc != 4)
        return OK;
    std::string host(argv[HOST_POSITION]);
    std::string port(argv[PORT_POSITION]);
    commonSocket sock;
    sock.connect(host, port);

    clientBinaryFile input(argv[FILE_POSITION]);
    if (!input.isOpen())
        return OK;
    File output(stdout);

    while (!input.eof()) {
        std::bitset<METADATA_SIZE> metadata;
        try {
            metadata = input.getTwoBytes();
        } catch (clientNoMoreToReadException& e) {
            break;
        }
        metadata >>= PADDING_SIZE; //Elimino el padding
        std::bitset<OPCODE_SIZE> opcode(metadata.to_ulong());
        metadata >>= OPCODE_SIZE; //Elimino el opcode
        std::bitset<MONTO_CHECKSUM_SIZE> monto_checksum(metadata.to_ulong());
        metadata >>= MONTO_CHECKSUM_SIZE; //Elimino el checksum del monto
        std::bitset<CARD_CHEKSUM_SIZE> card_checksum(metadata.to_ulong());
        std::bitset<32> card;
        try {
            card = input.getFourBytes();
        } catch (clientNoMoreToReadException& e) {
            break;
        }
        bool should_have_ammount = false;
        std::string command;
        switch (opcode.to_ulong()) {
            case AGREGAR_SALDO:
                command = "A";
                should_have_ammount = true;
                break;
            case FORZAR_AGREGAR_SALDO:
                command = "F";
                should_have_ammount = true;
                break;
            case PREGUNTAR_SALDO:
                command = "P";
                break;
            case REGISTRAR_TARJETA:
                command = "R";
                break;
            case SETEAR_SALDO:
                command = "S";
                should_have_ammount = true;
                break;
            default:
                break;
        }
        std::string msg;
        std::bitset<32> monto;
        if (should_have_ammount) {
            try {
                monto = input.getFourBytes();
            } catch (clientNoMoreToReadException& e) {
                break;
            }
            msg = getMessageWithAmmount(command, card.to_ulong(),
                                        monto.to_ulong());
        } else {
            msg = getMessageWithoutAmmount(command, card.to_ulong());
        }
        // Si falla el checksum de la tarjeta o el monto, imprimo por
        // pantalla y salteo la linea
        if (!validateCheacksum(card, card_checksum) ||
                !validateCheacksum(monto, monto_checksum)) {
            if (should_have_ammount)
                showChecksumErrorWithAmmount(command, card.to_ulong(),
                                             monto.to_ulong());
            else
                showChecksumErrorWithoutAmmount(command, card.to_ulong());
            continue;
        }
        int res = sock.send(msg, should_have_ammount ? SERVER_MSG_FULL :
                       SERVER_MSG_BASIC);
        if (res <= 0)
            break;
        std::string recv_command;
        std::string recv_errcode;
        std::string recv_card;
        std::string recv_ammount;
        res = sock.recv(recv_command, COMMAND_LENGTH_FROM_SERVER);
        if (recv_command == "E") {
            // El servidor me devolvió error
            sock.recv(recv_errcode, ERRCODE_LENGTH_FROM_SERVER);
            if (res <= 0)
                break;
            std::cout << recv_command << recv_errcode << "\n";
        } else {
            res = sock.recv(recv_card, CARD_LENGTH_FROM_SERVER);
            if (res <= 0)
                break;
            if (command != "R") {
                // Si no realicé un registro, me tiene que llegar el saldo
                res = sock.recv(recv_ammount, AMMOUNT_LENGTH_FROM_SERVER);
                if (res <= 0)
                    break;
            }
            std::cout << recv_command << recv_card << recv_ammount << "\n";
        }
    }

    return OK;
}

std::string getMessageWithoutAmmount(const std::string& command,
                                     const unsigned int card) {
    std::stringstream stream;
    stream << command;
    stream << std::setfill('0') << std::setw(10);
    stream << card;
    return stream.str();
}

std::string getMessageWithAmmount(const std::string& command,
                                  const unsigned int card, const int ammount) {
    std::stringstream stream;
    stream << getMessageWithoutAmmount(command, card);
    stream << std::setfill('0') << std::setw(10) << std::internal;
    stream << ammount;
    return stream.str();
}

void showChecksumErrorWithAmmount(const std::string& command,
                                         const unsigned int card,
                                         const int ammount) {
    std::string msg = getMessageWithAmmount(command, card, ammount);
    std::cout << msg << " -> " << CHECKSUM_ERROR
    std::cout << "\n";
}

void showChecksumErrorWithoutAmmount(const std::string& command,
                                            const unsigned int card) {
    std::string msg = getMessageWithoutAmmount(command, card);
    std::cout << msg << " -> " << CHECKSUM_ERROR
    std::cout << "\n";
}

bool validateCheacksum(std::bitset<32> metadata, std::bitset<5> checksum) {
    return metadata.count() == checksum.to_ulong() ||
            (metadata.count() == 32 && checksum == 0);
}
