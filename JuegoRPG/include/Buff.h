#ifndef BUFF_H
#define BUFF_H

#include "Efecto.h"

class Buff: public Efecto
{
protected:
    int turnos_max;
    int puntos_accion;
    bool usando;

public:
    Buff();

    int getTurnosMax();
    int getPuntosAccion();
    bool isUsando();

    void setBuffFuerza();
    void setBuffArtefacto();
    void setBuffDefensa();
    void setBuffEspinas();

    bool es(string nombre);

    void activar();
    bool estaActivo();
    void reducirTurno();

    string informacion();

    virtual ~Buff();

protected:

private:
};

#endif // BUFF_H
