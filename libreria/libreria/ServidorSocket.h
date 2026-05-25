#ifndef SERVIDORSOCKET_H
#define SERVIDORSOCKET_H

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

class ServidorSocket{

    private:
        int puerto;
        bool iniciado;

        WSADATA wsaData;
        SOCKET servidorSocket;
        SOCKET clienteSocket;
        struct sockaddr_in direccion;

    public:
        ServidorSocket();
        ServidorSocket(int puerto_);

        bool iniciar();
        string recibirMensaje();
        void cerrar();
        bool estaIniciado();

};

#endif

