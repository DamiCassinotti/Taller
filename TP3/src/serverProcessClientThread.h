#ifndef TP3_SERVERPROCESSCLIENTTHREAD_H
#define TP3_SERVERPROCESSCLIENTTHREAD_H

#include "serverThread.h"
#include "commonSocket.h"
#include "serverCardsData.h"
#include "serverConnectionData.h"

#define COMMAND_LENGTH 1
#define CARD_LENGTH 10
#define AMMOUNT_LENGTH 10
#define ERROR_MSG_LENGTH 6
#define SUCCESS_MSG_LENGTH_BASIC 11 // Para los registros (envio sin monto)
#define SUCCESS_MSG_LENGTH_FULL 21 //Para los demás comandos (envío con monto)

class serverProcessClientThread : public Thread {
private:
    commonSocket &sock;
    serverCardsData &cards;
    serverConnectionData &is_server_connected;
    bool are_we_connected;
public:
    serverProcessClientThread(commonSocket &sock, serverCardsData &cards,
                              serverConnectionData &is_server_connected);
    void run() override;
    ~serverProcessClientThread();

};


#endif //TP3_SERVERPROCESSCLIENTTHREAD_H
