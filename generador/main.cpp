#include "GeneradorPlacas.h"
#include "ClienteSocket.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]){

    string ipServidor = "127.0.0.1";
    int puerto = 8080;

    if(argc >= 2){

        ipServidor = argv[1];

    }

    if(argc >= 3){

        puerto = atoi(argv[2]);

    }

    cout << "======================================" << endl;
    cout << "Generador de placas - Parqueadero" << endl;
    cout << "Servidor destino: " << ipServidor << ":" << puerto << endl;
    cout << "======================================" << endl;

    GeneradorPlacas generador(20);
    ClienteSocket cliente(ipServidor, puerto);

    while(true){

        string evento = generador.generarEvento();

        cout << "Evento generado: " << evento << endl;

        bool enviado = cliente.enviarMensaje(evento);

        if(enviado){

            cout << "Evento enviado correctamente" << endl;

        }else{

            cout << "No se pudo enviar el evento" << endl;

        }

        int espera = 2 + rand() % 4;

        cout << "Esperando " << espera << " segundos..." << endl << endl;

        Sleep(espera * 1000);

    }

    return 0;

}
