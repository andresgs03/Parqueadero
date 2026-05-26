#ifndef PUENTE_H
#define PUENTE_H

#include <string>

using namespace std;

bool iniciarServidor(int puerto);
string recibirEvento();

int getCapacidad();
int getLibres();
int getOcupadas();

string getUltimoEvento();
string obtenerCeldasCSV();
string obtenerHistorialCSV();

void reiniciarParqueadero();
void cerrarServidor();

#endif
