#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include "Celda.h"
#include <vector>
#include <string>

using namespace std;

class Parqueadero{

    private:
        vector<Celda> celdas;
        vector<string> historial;
        string ultimoEvento;
        int capacidad;

        vector<string> separar(string texto, char separador);
        string limpiarMensaje(string mensaje);
        int buscarCeldaPorPlaca(string placa);
        void registrarEvento(string tipo, string placa, string fecha, string hora, int celda, string descripcion);

    public:
        Parqueadero();
        Parqueadero(int capacidad_);

        void procesarEvento(string mensaje);

        int getCapacidad();
        int contarLibres();
        int contarOcupadas();

        string getUltimoEvento();
        string obtenerCeldasCSV();
        string obtenerHistorialCSV();

        void mostrar();

};

#endif
