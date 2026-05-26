#ifndef PUENTE_H
#define PUENTE_H

#include <string>

using namespace std;

int iniciarServidor(int puerto);
int recibirEvento();

int getCapacidad();
int getLibres();
int getOcupadas();

string getUltimoEvento();
string obtenerCeldasCSV();
string obtenerHistorialCSV();

void reiniciarParqueadero();
void cerrarServidor();

#endif
