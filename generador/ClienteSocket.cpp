#include "ClienteSocket.h"
#include <iostream>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

ClienteSocket::ClienteSocket(){

    ipServidor = "127.0.0.1";
    puerto = 8080;

}

ClienteSocket::ClienteSocket(string ipServidor_, int puerto_){

    ipServidor = ipServidor_;
    puerto = puerto_;

}

bool ClienteSocket::enviarMensaje(string mensaje){

    WSADATA wsaData;
    SOCKET socketCliente = INVALID_SOCKET;
    struct sockaddr_in direccionServidor;
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){

        cout << "Error al inicializar Winsock" << endl;
        return false;

    }

    socketCliente = socket(AF_INET, SOCK_STREAM, 0);

    if(socketCliente == INVALID_SOCKET){

        cout << "Error al crear el socket cliente" << endl;
        WSACleanup();
        return false;

    }

    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(puerto);
    direccionServidor.sin_addr.s_addr = inet_addr(ipServidor.c_str());

    if(direccionServidor.sin_addr.s_addr == INADDR_NONE){

        cout << "Direccion IP invalida: " << ipServidor << endl;
        closesocket(socketCliente);
        WSACleanup();
        return false;

    }

    if(connect(socketCliente, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor)) == SOCKET_ERROR){

        cout << "Error al conectar con el servidor " << ipServidor << ":" << puerto << endl;
        closesocket(socketCliente);
        WSACleanup();
        return false;

    }

    int enviados = send(socketCliente, mensaje.c_str(), mensaje.length(), 0);

    if(enviados == SOCKET_ERROR){

        cout << "Error al enviar el mensaje" << endl;
        closesocket(socketCliente);
        WSACleanup();
        return false;

    }

    int recibidos = recv(socketCliente, buffer, sizeof(buffer) - 1, 0);

    if(recibidos > 0){

        buffer[recibidos] = '\0';
        cout << "Respuesta del servidor: " << buffer << endl;

    }

    closesocket(socketCliente);
    WSACleanup();

    return true;

}

void ClienteSocket::setIpServidor(string ipServidor_){

    ipServidor = ipServidor_;

}

void ClienteSocket::setPuerto(int puerto_){

    puerto = puerto_;

}

string ClienteSocket::getIpServidor(){

    return ipServidor;

}

int ClienteSocket::getPuerto(){

    return puerto;

}
