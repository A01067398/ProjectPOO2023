#ifndef DEBUFF_H
#define DEBUFF_H
#include "Efecto.h"

class Debuff: public Efecto
{
protected:

public:
    Debuff();

    void setNombre(string nombre);
    void setDebuffDebil();
    void setDebuffVulnerable();
    void setDebuffEnvenenado();
    void setDebuffConfuso();
    bool estaActivo();
    void reducirTurno();

    string informacion();

    virtual ~Debuff();

protected:

private:
};

#endif // DEBUFF_H
