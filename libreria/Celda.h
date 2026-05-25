#ifndef CELDA_H
#define CELDA_H

#include <string>

using namespace std;

class Celda{

    private:
        int numero;
        bool ocupada;
        string placa;
        string fecha;
        string hora;

    public:
        Celda();
        Celda(int numero_);

        void ocupar(string placa_, string fecha_, string hora_);
        void liberar();

        int getNumero();
        bool estaOcupada();
        string getPlaca();
        string getFecha();
        string getHora();

        void mostrar();

};

#endif
