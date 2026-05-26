#include "ServidorSocket.h"
#include <iostream>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

ServidorSocket::ServidorSocket(){

    puerto = 8080;
    iniciado = false;
    servidorSocket = INVALID_SOCKET;
    clienteSocket = INVALID_SOCKET;

}

ServidorSocket::ServidorSocket(int puerto_){

    puerto = puerto_;
    iniciado = false;
    servidorSocket = INVALID_SOCKET;
    clienteSocket = INVALID_SOCKET;

}

bool ServidorSocket::iniciar(){

    if(iniciado){

        return true;

    }

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){

        cout << "Error al inicializar Winsock" << endl;
        return false;

    }

    servidorSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(servidorSocket == INVALID_SOCKET){

        cout << "Error al crear el socket servidor" << endl;
        WSACleanup();
        return false;

    }

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(puerto);

    if(bind(servidorSocket, (struct sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR){

        cout << "Error en bind. No se pudo asociar el puerto " << puerto << endl;
        closesocket(servidorSocket);
        WSACleanup();
        return false;

    }

    if(listen(servidorSocket, 3) == SOCKET_ERROR){

        cout << "Error en listen" << endl;
        closesocket(servidorSocket);
        WSACleanup();
        return false;

    }

    u_long modoNoBloqueante = 1;

    if(ioctlsocket(servidorSocket, FIONBIO, &modoNoBloqueante) != 0){

        cout << "Error al poner el servidor en modo no bloqueante" << endl;
        closesocket(servidorSocket);
        WSACleanup();
        return false;

    }

    iniciado = true;

    cout << "Servidor socket iniciado en el puerto " << puerto << endl;

    return true;

}

string ServidorSocket::recibirMensaje(){

    if(!iniciado){

        return "";

    }

    if(clienteSocket == INVALID_SOCKET){

        struct sockaddr_in clienteDireccion;
        int tamanoCliente = sizeof(clienteDireccion);

        clienteSocket = accept(servidorSocket, (struct sockaddr*)&clienteDireccion, &tamanoCliente);

        if(clienteSocket == INVALID_SOCKET){

            int error = WSAGetLastError();

            if(error == WSAEWOULDBLOCK){

                return "";

            }

            cout << "Error en accept" << endl;
            return "";

        }

        u_long modoNoBloqueante = 1;
        ioctlsocket(clienteSocket, FIONBIO, &modoNoBloqueante);

    }

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytesRecibidos = recv(clienteSocket, buffer, sizeof(buffer) - 1, 0);

    if(bytesRecibidos > 0){

        buffer[bytesRecibidos] = '\0';

        string mensaje = buffer;

        const char* respuesta = "Evento recibido";
        send(clienteSocket, respuesta, strlen(respuesta), 0);

        closesocket(clienteSocket);
        clienteSocket = INVALID_SOCKET;

        return mensaje;

    }

    if(bytesRecibidos == 0){

        closesocket(clienteSocket);
        clienteSocket = INVALID_SOCKET;
        return "";

    }

    int error = WSAGetLastError();

    if(error == WSAEWOULDBLOCK){

        return "";

    }

    closesocket(clienteSocket);
    clienteSocket = INVALID_SOCKET;

    return "";

}

void ServidorSocket::cerrar(){

    if(clienteSocket != INVALID_SOCKET){

        closesocket(clienteSocket);
        clienteSocket = INVALID_SOCKET;

    }

    if(servidorSocket != INVALID_SOCKET){

        closesocket(servidorSocket);
        servidorSocket = INVALID_SOCKET;

    }

    if(iniciado){

        WSACleanup();

    }

    iniciado = false;

}

bool ServidorSocket::estaIniciado(){

    return iniciado;

}

