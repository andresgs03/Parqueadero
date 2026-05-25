#ifndef CLIENTESOCKET_H
#define CLIENTESOCKET_H

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

class ClienteSocket{

    private:
        string ipServidor;
        int puerto;

    public:
        ClienteSocket();
        ClienteSocket(string ipServidor_, int puerto_);

        bool enviarMensaje(string mensaje);

        void setIpServidor(string ipServidor_);
        void setPuerto(int puerto_);

        string getIpServidor();
        int getPuerto();

};

#endif

