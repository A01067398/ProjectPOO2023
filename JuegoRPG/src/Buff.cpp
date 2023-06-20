#include "Buff.h"

Buff::Buff()
{
    this->nombre = "No definido";
    this->turnos = 0;
    this->turnos_max = turnos;
    this->puntos_accion = 0;
    this->efecto = 0;
    this->usando = false;
}

Buff::~Buff()
{
    //dtor
}

int Buff::getTurnosMax(){
return this->turnos_max;
}

    int Buff::getPuntosAccion(){
    return this->puntos_accion;
    }

    bool Buff::isUsando(){
    return this->usando;
    }

void Buff::setBuffFuerza()
{
    this->nombre = "Fuerza";
    this->turnos = 2;
    this->turnos_max = turnos;
    this->puntos_accion = 2;
    this->efecto = 5;
}

void Buff::setBuffArtefacto()
{
    this->nombre = "Artefacto";
    this->turnos = 1;
    this->turnos_max = turnos;
    this->puntos_accion = 2;
}

void Buff::setBuffDefensa()
{
    this->nombre = "Defensa";
    this->turnos = 2;
    this->turnos_max = turnos;
    this->puntos_accion = 1;
    this->efecto = 5;
}
void Buff::setBuffEspinas()
{
    this->nombre = "Espinas";
    this->turnos = 2;
    this->turnos_max = turnos;
    this->puntos_accion = 2;
    this->efecto = 5;
}

bool Buff::es(string nombre){
    return this->nombre.compare(nombre) == 0;
}

void Buff::activar(){
    this->usando = true;
}

bool Buff::estaActivo(){
    return turnos > 0;
}

void Buff::reducirTurno(){
    this->turnos -= 1;
}

string Buff::informacion(){
    return to_string(puntos_accion) + "PA Aplicar " + nombre + " (" + to_string(efecto) + ")";
}
