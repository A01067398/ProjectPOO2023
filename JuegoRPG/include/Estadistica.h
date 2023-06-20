#ifndef ESTADISTICA_H
#define ESTADISTICA_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

class Estadistica
{
protected:
    int ganador;
    char nombrePersonajeGanador[100];
    char nombrePersonajePerdedor[100];
    public:
        Estadistica();
        Estadistica(int ganador, const char* nombrePersonajeGanador, const char* nombrePersonajePerdedor);
        virtual ~Estadistica();

        int contarVictorias(vector<Estadistica> data, int numeroJugador);
        int contarVictoriasPersonaje(vector<Estadistica> data, string nombrePersonaje);
        void generarEstadistica(vector<Estadistica> data);

    protected:

    private:
};

#endif // ESTADISTICA_H
