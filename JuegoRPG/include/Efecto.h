#ifndef EFECTO_H
#define EFECTO_H

#include <string>

using namespace std;

class Efecto
{
    protected:
        string nombre;
        int turnos;
        int efecto;

    public:
        Efecto();
        string getNombre();
        void setNombre(string nombre);
        int getTurnos();
        void setTurnos(int turnos);
        int getEfecto();
        void setEfecto(int efecto);
        virtual ~Efecto();

        virtual string informacion();

    private:
};

#endif // EFECTO_H
