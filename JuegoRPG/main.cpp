#include <iostream>
#include <time.h>
#include <vector>

#include "Personaje.h"
#include "Estadistica.h"

#define MAX_PERSONAJE 3

using namespace std;

vector<Estadistica> estadisticas;

void pausar()
{
    cout << endl << endl;
    system("pause");
}

void pausarLimpiar()
{
    cout << endl << endl;
    system("pause");
    system("cls");
}

void limpiar()
{
    system("cls");
}

vector<Estadistica> leerEstadisticas()
{
    vector<Estadistica> data;

    FILE *archivo;
    archivo = fopen("Estadisticas.dat", "rb");
    if(archivo != NULL)
    {
        Estadistica e;
        fread(&e, sizeof(Estadistica), 1, archivo);
        while(!feof(archivo))
        {
            data.push_back(e);
            fread(&e, sizeof(Estadistica), 1, archivo);
        }
        fclose(archivo);
    }

    return data;
}

void guardarEstadistica(Personaje* ganador, Personaje* perdedor, int turno)
{
    FILE *archivo;
    archivo = fopen("Estadisticas.dat", "ab");
    if(archivo == NULL)
    {
        archivo = fopen("Estadisticas.dat", "wb");
    }
    Estadistica e(turno, ganador->getNombre().c_str(), perdedor->getNombre().c_str());
    estadisticas.push_back(e);
    fwrite(&e, sizeof(Estadistica), 1, archivo);
    fclose(archivo);
}

void mostrarEstadisticas()
{
    Estadistica e;
    e.generarEstadistica(estadisticas);
}

Personaje** crearPersonajes()
{
    Personaje* p1 = new Personaje("Humano", 100, 10, 25, 10, 5);
    Personaje* p2 = new Personaje("Ogro", 100, 20, 15, 12, 5);
    Personaje* p3 = new Personaje("Goblin", 100, 15, 10, 20, 5);

    Personaje** personajes = (Personaje**) calloc(MAX_PERSONAJE, sizeof(Personaje));
    personajes[0] = p1;
    personajes[1] = p2;
    personajes[2] = p3;

    return personajes;
}

void mostrarPersonajes(Personaje** personajes)
{
    int i;
    cout << "\tPERSONAJES" << endl;
    for(i = 0; i < MAX_PERSONAJE; i++)
    {
        cout << " [" << (i+1) << "] " << personajes[i] << endl;
    }
}

int getPersonaje(int numero)
{
    int opcion;
    do
    {
        cout << " Personaje del Jugador " << numero << ": ";
        cin >> opcion;
    }
    while(opcion < 1 || opcion > MAX_PERSONAJE);
    return opcion - 1;
}

Personaje* obtenerGanador(Personaje* p1, Personaje* p2)
{
    if(p1->estaMuerto())
    {
        return p2;
    }
    if(p2->estaMuerto())
    {
        return p1;
    }
    return NULL;
}

void accionPersonaje(Personaje* p1, Personaje* p2, int turno)
{
    int opcion = -1;
    p1->reiniciarPA();

    while(opcion != 0)
    {
        limpiar();
        cout << "Oponente " << p2 << endl;
        cout << "VS." << endl;
        cout << "Turno " << p1 << endl;
        if(obtenerGanador(p1, p2) != NULL)
        {
            return;
        }
        cout << " Turno Jugador " << turno << endl;
        cout << " Que haras? (0 para terminar) >> ";
        cin >> opcion;

        cout << endl;
        switch(opcion)
        {
        case 0:
            cout << " [" << p1->getNombre() << "] finaliza su turno" << endl;
            return;
        case 1:
            p1->atacar(p2);
            break;
        case 2:
            p1->curarse();
            break;
        case 3:
            p1->aplicarBuff();
            break;
        default:
            cout << "Opcion no valida!" << endl;
            break;
        }

        pausarLimpiar();
    }
}

void jugar()
{
    system("cls");

    Personaje** personajes = crearPersonajes();
    mostrarPersonajes(personajes);

    cout << " Selecciona los personajes" << endl;
    Personaje* p1 = personajes[getPersonaje(1)];
    Personaje* p2 = personajes[getPersonaje(2)];

    cout << endl << (p1[0] == p2[0]? " Vaya, tienen los mismos gustos 0.0" : " Personajes diferente, a la batalla!") << endl;
    cout << endl << " EL JUEGO ESTA POR EMPEZAR" << endl << endl;
    pausarLimpiar();

    int turno = 1;
    Personaje* ganador = NULL;
    Personaje* perdedor = NULL;

    while(ganador == NULL)
    {
        turno = 1;
        accionPersonaje(p1, p2, turno);
        p1->aplicarEfectoBuff(p2);
        p1->quitarEfectoBuff();
        pausar();

        ganador = obtenerGanador(p1, p2);
        if(ganador != NULL)
        {
            break;
        }

        turno = 2;
        accionPersonaje(p2, p1, turno);
        p2->aplicarEfectoBuff(p1);
        p2->quitarEfectoBuff();
        pausar();

        ganador = obtenerGanador(p1, p2);
        if(ganador != NULL)
        {
            break;
        }

        p1->aplicarEfectoDebuff();
        p2->aplicarEfectoDebuff();

        ganador = obtenerGanador(p1, p2);
    }

    cout << endl << " TENEMOS UN GANADOR" << endl;
    pausarLimpiar();
    cout << " **** GANADOR [ JUGADOR " << turno << "] ****" << endl << ganador << endl;

    perdedor = (ganador == p1 ? p2 : p1);
    guardarEstadistica(ganador, perdedor, turno);
}

int main()
{
    srand(time(NULL));

    int opcion = 0;
    estadisticas = leerEstadisticas();

    while(opcion != 3)
    {
        cout << " JUEGO RPG" << endl
             << "--------------------------------------" << endl
             << " 1. Jugar" << endl
             << " 2. Mostrar estadisticas" << endl
             << " 3. Salir" << endl
             << " Tu opcion >> ";
        cin >> opcion;

        cout << endl;

        switch(opcion)
        {
        case 1:
            jugar();
            break;
        case 2:
            mostrarEstadisticas();
            break;
        case 3:
            cout << "Hasta la proxima!" << endl;
            break;
        default:
            cout << "Opcion no valida!" << endl;
            break;
        }

        pausarLimpiar();
    }

    return 0;
}
