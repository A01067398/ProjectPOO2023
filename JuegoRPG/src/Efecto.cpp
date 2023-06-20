#include "Efecto.h"

Efecto::Efecto()
{
    //ctor
}

Efecto::~Efecto()
{
    //dtor
}

string Efecto::getNombre()
{
    return this->nombre;
}

void Efecto::setNombre(string nombre)
{
    this->nombre = nombre;
}

int Efecto::getTurnos()
{
    return this->turnos;
}

void Efecto::setTurnos(int turnos)
{
    this->turnos = turnos;
}

int Efecto::getEfecto()
{
    return this->efecto;
}

void Efecto::setEfecto(int efecto)
{
    this->efecto = efecto;
}

string Efecto::informacion(){
    return NULL;
}
