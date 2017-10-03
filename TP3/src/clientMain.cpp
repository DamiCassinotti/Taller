#include <string>
#include <iostream>
#include <bitset>
#include "commonSocket.h"
#include "commonFile.h"
#include "clientBinaryFile.h"

#define OK 0;
#define HOST_POSITION 1
#define PORT_POSITION 2
#define FILE_POSITION 3
#define METADATA_SIZE 16
#define PADDING_SIZE 3
#define OPCODE_SIZE 3
#define MONTO_CHECKSUM_SIZE 5
#define CARD_CHEKSUM_SIZE 5

int main(int argc, char* argv[]) {
    if (argc != 4)
        return OK;
    //std::string host(argv[HOST_POSITION]);
    //std::string port(argv[PORT_POSITION]);
    //commonSocket sock;
    //sock.connect(host, port);

    clientBinaryFile input(argv[FILE_POSITION]);
    if (!input.isOpen())
        return OK;
    File output(stdout);

    //while (!input.eof()) {
    std::bitset<METADATA_SIZE> metadata = input.getTwoBytes();
    std::cout << "La metadata es " << metadata << "\n";
    metadata >>= PADDING_SIZE; //Elimino el padding
    std::bitset<OPCODE_SIZE> opcode(metadata.to_ulong());
    metadata >>= OPCODE_SIZE; //Elimino el opcode
    std::bitset<MONTO_CHECKSUM_SIZE> monto_checksum(metadata.to_ulong());
    metadata >>= MONTO_CHECKSUM_SIZE; //Elimino el checksum del monto
    std::bitset<CARD_CHEKSUM_SIZE> card_checksum(metadata.to_ulong());
    std::bitset<32> card = input.getFourBytes();
    std::cout << "El numero de tarjeta es: " << card.to_ulong() << " (" <<
              card << ")\n";
    std::cout << "El checksum de la tarjeta es: " << card_checksum.to_ulong()
              << " (" << card_checksum << ")\n";
    std::cout << "El opcode es: " << opcode.to_ulong() << "\n";
    std::cout << "El checksum del monto es: " << monto_checksum.to_ulong() <<
                                                                           " "
                                                                                   "(" << monto_checksum << ")\n";
    //}

    //sock.shutdown();
    return 0;
}
