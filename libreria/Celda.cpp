#include "Celda.h"
#include <iostream>

using namespace std;

Celda::Celda(){

    numero = 0;
    ocupada = false;
    placa = "";
    fecha = "";
    hora = "";

}

Celda::Celda(int numero_){

    numero = numero_;
    ocupada = false;
    placa = "";
    fecha = "";
    hora = "";

}

void Celda::ocupar(string placa_, string fecha_, string hora_){

    ocupada = true;
    placa = placa_;
    fecha = fecha_;
    hora = hora_;

}

void Celda::liberar(){

    ocupada = false;
    placa = "";
    fecha = "";
    hora = "";

}

int Celda::getNumero(){

    return numero;

}

bool Celda::estaOcupada(){

    return ocupada;

}

string Celda::getPlaca(){

    return placa;

}

string Celda::getFecha(){

    return fecha;

}

string Celda::getHora(){

    return hora;

}

void Celda::mostrar(){

    cout << "Celda " << numero << ": ";

    if(ocupada){

        cout << "Ocupada por " << placa;
        cout << " | Fecha: " << fecha;
        cout << " | Hora: " << hora << endl;

    }else{

        cout << "Libre" << endl;

    }

}
