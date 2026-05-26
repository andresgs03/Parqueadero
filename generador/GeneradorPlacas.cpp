#include "GeneradorPlacas.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

GeneradorPlacas::GeneradorPlacas(){

    capacidad = 20;
    srand(time(NULL));

}

GeneradorPlacas::GeneradorPlacas(int capacidad_){

    capacidad = capacidad_;
    srand(time(NULL));

}

string GeneradorPlacas::generarPlacaAleatoria(){

    string placa = "";

    for(int i = 0; i < 3; i++){

        char letra = 'A' + rand() % 26;
        placa += letra;

    }

    for(int i = 0; i < 3; i++){

        char numero = '0' + rand() % 10;
        placa += numero;

    }

    return placa;

}

string GeneradorPlacas::obtenerFechaActual(){

    time_t ahora = time(NULL);
    tm* tiempoLocal = localtime(&ahora);

    stringstream ss;

    ss << (1900 + tiempoLocal->tm_year) << "-";

    if((tiempoLocal->tm_mon + 1) < 10){
        ss << "0";
    }

    ss << (tiempoLocal->tm_mon + 1) << "-";

    if(tiempoLocal->tm_mday < 10){
        ss << "0";
    }

    ss << tiempoLocal->tm_mday;

    return ss.str();

}

string GeneradorPlacas::obtenerHoraActual(){

    time_t ahora = time(NULL);
    tm* tiempoLocal = localtime(&ahora);

    stringstream ss;

    if(tiempoLocal->tm_hour < 10){
        ss << "0";
    }

    ss << tiempoLocal->tm_hour << ":";

    if(tiempoLocal->tm_min < 10){
        ss << "0";
    }

    ss << tiempoLocal->tm_min << ":";

    if(tiempoLocal->tm_sec < 10){
        ss << "0";
    }

    ss << tiempoLocal->tm_sec;

    return ss.str();

}

bool GeneradorPlacas::placaExiste(string placa){

    for(size_t i = 0; i < placasActivas.size(); i++){

        if(placasActivas[i] == placa){

            return true;

        }

    }

    return false;

}

bool GeneradorPlacas::celdaOcupada(int celda){

    for(size_t i = 0; i < celdasActivas.size(); i++){

        if(celdasActivas[i] == celda){

            return true;

        }

    }

    return false;

}

int GeneradorPlacas::obtenerCeldaLibre(){

    if((int)celdasActivas.size() >= capacidad){

        return -1;

    }

    int celda = 1 + rand() % capacidad;

    while(celdaOcupada(celda)){

        celda = 1 + rand() % capacidad;

    }

    return celda;

}

string GeneradorPlacas::generarEntrada(){

    string placa = generarPlacaAleatoria();

    while(placaExiste(placa)){

        placa = generarPlacaAleatoria();

    }

    int celda = obtenerCeldaLibre();

    if(celda == -1){

        return generarSalida();

    }

    string fecha = obtenerFechaActual();
    string hora = obtenerHoraActual();

    placasActivas.push_back(placa);
    celdasActivas.push_back(celda);

    stringstream ss;

    ss << placa << ";"
       << fecha << ";"
       << hora << ";"
       << celda;

    return ss.str();

}

string GeneradorPlacas::generarSalida(){

    if(placasActivas.size() == 0){

        return generarEntrada();

    }

    int indice = rand() % placasActivas.size();

    string placa = placasActivas[indice];
    int celda = celdasActivas[indice];
    string fecha = obtenerFechaActual();
    string hora = obtenerHoraActual();

    placasActivas.erase(placasActivas.begin() + indice);
    celdasActivas.erase(celdasActivas.begin() + indice);

    stringstream ss;

    ss << placa << ";"
       << fecha << ";"
       << hora << ";"
       << celda;

    return ss.str();

}

string GeneradorPlacas::generarEvento(){

    if(placasActivas.size() == 0){

        return generarEntrada();

    }

    if((int)placasActivas.size() >= capacidad){

        return generarSalida();

    }

    int decision = rand() % 100;

    if(decision < 40){

        return generarSalida();

    }else{

        return generarEntrada();

    }

}
