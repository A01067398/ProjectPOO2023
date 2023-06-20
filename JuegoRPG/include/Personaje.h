
#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <iostream>
#include <string>
#include "Debuff.h"
#include "Buff.h"


using namespace std;

class Personaje
{
protected:
    int vida;
    int vida_max;
    int defensa;
    int ataque;
    int pa_ataque;
    int curacion;
    int pa_curacion;
    string nombre;
    int puntos_accion;
    int puntos_accion_max;
    Debuff* debuff;
    Buff* buff;

public:
    Personaje();
    Personaje(string nombre, int vida, int defensa, int ataque, int curacion, int puntos_accion_max);

    int getVida();
    void setVida(int vida);
    int getPuntosAccion();
    void setPuntosAccion(int puntos_accion);
    string getNombre();
    int aleatorio(int min, int max);

    Debuff* generarDebuff();
    Buff* generarBuff();

    void reiniciarPA();
    bool estaMuerto();
    void atacar(Personaje* p);
    void curarse();
    bool aplicarBuff();
    void aplicarEfectoBuff(Personaje* p);
    void quitarEfectoBuff();
    void cambiarDebuff();
    void aplicarEfectoDebuff();
    bool esta(string nombre_debuff);

    bool operator==(Personaje &);
    friend ostream & operator<< (ostream &, Personaje* &);

    virtual ~Personaje();

protected:

private:
};

#endif // PERSONAJE_H
