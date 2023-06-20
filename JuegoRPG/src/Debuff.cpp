#include "Debuff.h"

Debuff::Debuff()
{
    this->nombre = "";
    this->efecto = 0;
    this->turnos = 0;
}

Debuff::~Debuff()
{
    //dtor
}

void Debuff::setNombre(string nombre)
{
    this->nombre = nombre;
}

void Debuff::setDebuffDebil()
{
    this->nombre = "Debil";
    this->turnos = 1;
}

void Debuff::setDebuffVulnerable()
{
    this->nombre = "Vulnerable";
    this->turnos = 1;
}

void Debuff::setDebuffEnvenenado()
{
    this->nombre = "Envenenado";
    this->turnos = 1;
    this->efecto = 5;
}

void Debuff::setDebuffConfuso()
{
    this->nombre = "Confuso";
    this->turnos = 1;
}

bool Debuff::estaActivo(){
    return turnos > 0;
}

void Debuff::reducirTurno(){
    this->turnos -= 1;
}

string Debuff::informacion(){
    return nombre + " por " + to_string(turnos) + " turnos - efecto(" + to_string(efecto) + ")";
}
