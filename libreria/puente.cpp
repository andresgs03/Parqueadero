#include "puente.h"
#include "Parqueadero.h"
#include "ServidorSocket.h"

using namespace std;

static Parqueadero parqueadero(20);
static ServidorSocket* servidor = NULL;
static bool servidorIniciado = false;

bool iniciarServidor(int puerto){

    if(servidorIniciado){

        return true;

    }

    if(servidor != NULL){

        delete servidor;
        servidor = NULL;

    }

    servidor = new ServidorSocket(puerto);

    servidorIniciado = servidor->iniciar();

    return servidorIniciado;

}

string recibirEvento(){

    if(!servidorIniciado || servidor == NULL){

        return "";

    }

    string mensaje = servidor->recibirMensaje();

    if(mensaje != ""){

        parqueadero.procesarEvento(mensaje);

    }

    return mensaje;

}

int getCapacidad(){

    return parqueadero.getCapacidad();

}

int getLibres(){

    return parqueadero.contarLibres();

}

int getOcupadas(){

    return parqueadero.contarOcupadas();

}

string getUltimoEvento(){

    return parqueadero.getUltimoEvento();

}

string obtenerCeldasCSV(){

    return parqueadero.obtenerCeldasCSV();

}

string obtenerHistorialCSV(){

    return parqueadero.obtenerHistorialCSV();

}

void reiniciarParqueadero(){

    parqueadero = Parqueadero(20);

}

void cerrarServidor(){

    if(servidor != NULL){

        servidor->cerrar();

        delete servidor;
        servidor = NULL;

    }

    servidorIniciado = false;

}
