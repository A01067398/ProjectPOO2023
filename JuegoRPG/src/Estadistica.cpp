#include "Estadistica.h"

Estadistica::Estadistica()
{
    this->ganador = 0;
    strcpy(this->nombrePersonajeGanador, "");
    strcpy(this->nombrePersonajePerdedor, "");
}

Estadistica::~Estadistica()
{
    //dtor
}

Estadistica::Estadistica(int ganador, const char* nombrePersonajeGanador, const char* nombrePersonajePerdedor)
{
    this->ganador = ganador;
    strcpy(this->nombrePersonajeGanador, nombrePersonajeGanador);
    strcpy(this->nombrePersonajePerdedor, nombrePersonajePerdedor);
}

int Estadistica::contarVictorias(vector<Estadistica> data, int numeroJugador)
{
    int i, cont = 0, n = data.size();
    for(i = 0; i < n; i++)
    {
        if(data.at(i).ganador == numeroJugador)
        {
            cont++;
        }
    }
    return cont;
}

int Estadistica::contarVictoriasPersonaje(vector<Estadistica> data, string nombrePersonaje)
{
    int i, cont = 0, n = data.size();
    for(i = 0; i < n; i++)
    {
        if(nombrePersonaje.compare(data.at(i).nombrePersonajeGanador) == 0)
        {
            cont++;
        }
    }
    return cont;
}

void Estadistica::generarEstadistica(vector<Estadistica> data)
{
    int registros = data.size();
    int victoria_j1 = contarVictorias(data, 1);
    int victoria_j2 = contarVictorias(data, 2);
    float porc_v1 =  100.0 * victoria_j1 / registros;
    float porc_v2 =  100.0 * victoria_j2 / registros;

    cout << " --- ESTADISTICAS ---" << endl
         << " Total partidas jugadas: " << registros << endl << endl
         << " Victorias Jugador 1: " << victoria_j1 << endl
         << " % de vitoria Jugador 1: " << porc_v1 << "%" << endl << endl
         << " Victorias Jugador 2: " << victoria_j2 << endl
         << " % de vitoria Jugador 2: " << porc_v2 << "%" << endl << endl;

    cout << " --- ESTADISTICAS POR PERSONAJE ---" << endl
         << " Humano -> victorias( " << contarVictoriasPersonaje(data, "Humano") << " )" << endl
         << " Ogro -> victorias( " << contarVictoriasPersonaje(data, "Ogro") << " )" << endl
         << " Goblin -> victorias( " << contarVictoriasPersonaje(data, "Goblin") << " )" << endl;

}
