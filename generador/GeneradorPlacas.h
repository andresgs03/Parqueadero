#ifndef GENERADORPLACAS_H
#define GENERADORPLACAS_H

#include <string>
#include <vector>

using namespace std;

class GeneradorPlacas{

    private:
        int capacidad;
        vector<string> placasActivas;
        vector<int> celdasActivas;

        string generarPlacaAleatoria();
        string obtenerFechaActual();
        string obtenerHoraActual();

        bool placaExiste(string placa);
        bool celdaOcupada(int celda);
        int obtenerCeldaLibre();

        string generarEntrada();
        string generarSalida();

    public:
        GeneradorPlacas();
        GeneradorPlacas(int capacidad_);

        string generarEvento();

};

#endif
