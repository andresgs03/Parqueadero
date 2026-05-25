#include "Celda.h"
#include <iostream>

using namespace std;

int main(){

    Celda celdaUno(1);

    cout << "Estado inicial:" << endl;
    celdaUno.mostrar();

    cout << endl << "Ocupando celda..." << endl;
    celdaUno.ocupar("ABC123", "2026-05-25", "14:30:15");
    celdaUno.mostrar();

    cout << endl << "Datos consultados con getters:" << endl;
    cout << "Numero: " << celdaUno.getNumero() << endl;
    cout << "Placa: " << celdaUno.getPlaca() << endl;
    cout << "Fecha: " << celdaUno.getFecha() << endl;
    cout << "Hora: " << celdaUno.getHora() << endl;

    cout << endl << "Liberando celda..." << endl;
    celdaUno.liberar();
    celdaUno.mostrar();

    return 0;
}

