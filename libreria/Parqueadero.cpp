#include "Parqueadero.h"
#include <iostream>
#include <sstream>

using namespace std;

Parqueadero::Parqueadero(){

    capacidad = 20;
    ultimoEvento = "Sin eventos registrados";

    for(int i = 1; i <= capacidad; i++){

        Celda celdaTemporal(i);
        celdas.push_back(celdaTemporal);

    }

}

Parqueadero::Parqueadero(int capacidad_){

    capacidad = capacidad_;
    ultimoEvento = "Sin eventos registrados";

    for(int i = 1; i <= capacidad; i++){

        Celda celdaTemporal(i);
        celdas.push_back(celdaTemporal);

    }

}

string Parqueadero::limpiarMensaje(string mensaje){

    while(mensaje.size() > 0 && (mensaje[mensaje.size() - 1] == '\n' || mensaje[mensaje.size() - 1] == '\r')){

        mensaje.erase(mensaje.size() - 1);

    }

    return mensaje;

}

vector<string> Parqueadero::separar(string texto, char separador){

    vector<string> partes;
    string parte;
    stringstream ss(texto);

    while(getline(ss, parte, separador)){

        partes.push_back(parte);

    }

    return partes;

}

int Parqueadero::buscarCeldaPorPlaca(string placa){

    for(int i = 0; i < capacidad; i++){

        if(celdas[i].estaOcupada() && celdas[i].getPlaca() == placa){

            return i;

        }

    }

    return -1;

}

void Parqueadero::registrarEvento(string tipo, string placa, string fecha, string hora, int celda, string descripcion){

    stringstream ss;

    ss << tipo << ","
       << placa << ","
       << fecha << ","
       << hora << ","
       << celda << ","
       << descripcion;

    historial.push_back(ss.str());

    ultimoEvento = tipo + " - Placa: " + placa + " - Celda: " + to_string(celda) + " - " + descripcion;

}

void Parqueadero::procesarEvento(string mensaje){

    mensaje = limpiarMensaje(mensaje);

    vector<string> partes = separar(mensaje, ';');

    if(partes.size() != 4){

        registrarEvento("ERROR", "-", "-", "-", 0, "Formato de mensaje invalido");
        return;

    }

    string placa = partes[0];
    string fecha = partes[1];
    string hora = partes[2];
    int numeroCelda = 0;

    try{

        numeroCelda = stoi(partes[3]);

    }catch(...){

        registrarEvento("ERROR", placa, fecha, hora, 0, "Numero de celda invalido");
        return;

    }

    int indicePlaca = buscarCeldaPorPlaca(placa);

    if(indicePlaca != -1){

        int celdaLiberada = celdas[indicePlaca].getNumero();

        celdas[indicePlaca].liberar();

        registrarEvento("SALIDA", placa, fecha, hora, celdaLiberada, "Vehiculo salio y se libero la celda");
        return;

    }

    if(numeroCelda < 1 || numeroCelda > capacidad){

        registrarEvento("ERROR", placa, fecha, hora, numeroCelda, "La celda no existe en el parqueadero");
        return;

    }

    int indiceCelda = numeroCelda - 1;

    if(celdas[indiceCelda].estaOcupada()){

        string placaActual = celdas[indiceCelda].getPlaca();

        registrarEvento("ERROR", placa, fecha, hora, numeroCelda, "Celda ocupada por " + placaActual);
        return;

    }

    celdas[indiceCelda].ocupar(placa, fecha, hora);

    registrarEvento("ENTRADA", placa, fecha, hora, numeroCelda, "Vehiculo ingreso al parqueadero");

}

int Parqueadero::getCapacidad(){

    return capacidad;

}

int Parqueadero::contarLibres(){

    int libres = 0;

    for(int i = 0; i < capacidad; i++){

        if(!celdas[i].estaOcupada()){

            libres++;

        }

    }

    return libres;

}

int Parqueadero::contarOcupadas(){

    int ocupadas = 0;

    for(int i = 0; i < capacidad; i++){

        if(celdas[i].estaOcupada()){

            ocupadas++;

        }

    }

    return ocupadas;

}

string Parqueadero::getUltimoEvento(){

    return ultimoEvento;

}

string Parqueadero::obtenerCeldasCSV(){

    stringstream ss;

    ss << "numero,estado,placa,fecha,hora\n";

    for(int i = 0; i < capacidad; i++){

        ss << celdas[i].getNumero() << ",";

        if(celdas[i].estaOcupada()){

            ss << "Ocupada,"
               << celdas[i].getPlaca() << ","
               << celdas[i].getFecha() << ","
               << celdas[i].getHora() << "\n";

        }else{

            ss << "Libre,,,\n";

        }

    }

    return ss.str();

}

string Parqueadero::obtenerHistorialCSV(){

    stringstream ss;

    ss << "tipo,placa,fecha,hora,celda,descripcion\n";

    for(size_t i = 0; i < historial.size(); i++){

        ss << historial[i] << "\n";

    }

    return ss.str();

}

void Parqueadero::mostrar(){

    cout << "==============================" << endl;
    cout << "Estado del parqueadero" << endl;
    cout << "Capacidad: " << capacidad << endl;
    cout << "Libres: " << contarLibres() << endl;
    cout << "Ocupadas: " << contarOcupadas() << endl;
    cout << "Ultimo evento: " << ultimoEvento << endl;
    cout << "==============================" << endl;

    for(int i = 0; i < capacidad; i++){

        celdas[i].mostrar();

    }

    cout << endl;

}


