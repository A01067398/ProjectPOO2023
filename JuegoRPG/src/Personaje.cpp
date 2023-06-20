#include "Personaje.h"

Personaje::Personaje()
{
    this->vida = 100;
    this->vida_max = vida;
    this->defensa = 20;
    this->ataque = 20;
    this->pa_ataque = 2;
    this->curacion = 10;
    this->pa_curacion = 1;
    this->nombre = "Default";
    this->puntos_accion_max = 5;
    this->puntos_accion = puntos_accion_max;

    this->debuff = new Debuff();
    this->buff = new Buff();

    this->debuff = generarDebuff();
    this->buff = generarBuff();
}

Personaje::Personaje(string nombre, int vida, int defensa, int ataque, int curacion, int puntos_accion_max)
{
    this->vida = vida;
    this->vida_max = vida;
    this->defensa = defensa;
    this->ataque = ataque;
    this->pa_ataque = 2;
    this->curacion = curacion;
    this->pa_curacion = 1;
    this->nombre = nombre;
    this->puntos_accion_max = puntos_accion_max;
    this->puntos_accion = puntos_accion_max;

    this->debuff = new Debuff();
    this->buff = new Buff();

    this->debuff = generarDebuff();
    this->buff = generarBuff();
}

Personaje::~Personaje()
{
    //dtor
}

int Personaje::getVida()
{
    return vida;
}

void Personaje::setVida(int vida)
{
    this->vida = vida;
}

int Personaje::getPuntosAccion()
{
    return puntos_accion;
}

void Personaje::setPuntosAccion(int puntos_accion)
{
    this->puntos_accion = puntos_accion;
}

string Personaje::getNombre(){
    return this->nombre;
}

int Personaje::aleatorio(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

Debuff* Personaje::generarDebuff()
{
    if(!debuff->estaActivo())
    {
        Debuff* nuevo = new Debuff();
        switch (aleatorio(1, 4))
        {
        case 1:
            nuevo->setDebuffDebil();
            break;
        case 2:
            nuevo->setDebuffVulnerable();
            break;
        case 3:
            nuevo->setDebuffEnvenenado();
            break;
        case 4:
            nuevo->setDebuffConfuso();
            break;
        }
        return nuevo;
    }
    return debuff;
}

Buff* Personaje::generarBuff()
{
    if(!buff->estaActivo())
    {
        Buff* nuevo = new Buff();
        switch (aleatorio(1, 4))
        {
        case 1:
            nuevo->setBuffFuerza();
            break;
        case 2:
            nuevo->setBuffArtefacto();
            break;
        case 3:
            nuevo->setBuffDefensa();
            break;
        case 4:
            nuevo->setBuffEspinas();
            break;
        }
        return nuevo;
    }
    return buff;
}

void Personaje::reiniciarPA()
{
    this->puntos_accion = puntos_accion_max;
}

bool Personaje::estaMuerto()
{
    if(vida <= 0)
    {
        this->vida = 0;
        return true;
    }
    return false;
}

void Personaje::atacar(Personaje* p)
{
    if(puntos_accion >= pa_ataque)
    {
        int damage = ataque;
        puntos_accion -= pa_ataque;
        if(esta("Debil"))
        {
            damage = damage * 0.75;
        }
        else if(esta("Confundido"))
        {
            if(aleatorio(0, 1) == 1)
            {
                damage = (damage - (damage * defensa / 100));
                vida -= damage;
                if(vida < 0)
                {
                    vida = 0;
                }
                cout << " [" << nombre << "] se ataca asi mismo con " << damage << " de danio" << endl;
                return;
            }
        }

        if(p->esta("Vulnerable"))
        {
            damage = damage * 1.5;
        }

        damage = (damage - (damage * p->defensa / 100));
        p->vida -= damage;
        if(p->vida < 0)
        {
            p->vida = 0;
        }
        cout << " [" << p->nombre << "] recibe " << damage << " de danio" << endl;
    }
    else
    {
        cout << " No tienes sufientes PA" << endl;
    }

}

void Personaje::curarse()
{
    if(puntos_accion >= pa_curacion)
    {
        this->vida += curacion;
        if(vida > vida_max)
        {
            vida = vida_max;
        }
        this->puntos_accion -= pa_curacion;
        cout << " Curacion exitosa" << endl;
    }
    else
    {
        cout << " No tienes suficientes PA" << endl;
    }
}

bool Personaje::aplicarBuff()
{
    if(buff != NULL)
    {
        if(buff->estaActivo() && !buff->isUsando())
        {
            if(puntos_accion >= buff->getPuntosAccion())
            {
                buff->activar();
                this->puntos_accion -= buff->getPuntosAccion();
                if(buff->es("Fuerza"))
                {
                    ataque += buff->getEfecto();
                    buff->reducirTurno();
                    cout << " [" << nombre << "] recibe " << buff->getEfecto() << " de ataque por Buff " << buff->getNombre() << endl;
                }
                else if(buff->es("Artefacto"))
                {
                    this->debuff = new Debuff();
                    buff->reducirTurno();
                    cout << " [" << nombre << "] quita Debuff  Buff " << buff->getNombre() << endl;
                }

                cout << " Buff activado" << endl;
                return true;
            }
            cout << " No tienes suficientes PA" << endl;
            return false;
        }
    }
    cout << " No tienes buff o ya lo tienes activado" << endl;
    return false;
}

void Personaje::aplicarEfectoBuff(Personaje* p)
{
    if(buff->estaActivo() && buff->isUsando())
    {
        if(buff->es("Defensa"))
        {
            this->defensa += buff->getEfecto();
            cout << " [" << nombre << "] recibe " << buff->getEfecto() << " de escudo por Buff " << buff->getNombre() << endl;
        }
        else if(buff->es("Espinas"))
        {
            p->vida -= buff->getEfecto();
            cout << " [" << p->nombre << "] recibe " << buff->getEfecto() << " de danio por Buff " << buff->getNombre() << endl;
        }
    }
}

void Personaje::quitarEfectoBuff()
{
    if(!buff->estaActivo() && buff->isUsando())
    {
        if(buff->es("Fuerza"))
        {
            this->ataque -= buff->getEfecto();
        }
        else if(buff->es("Defensa"))
        {
            this->defensa -= buff->getEfecto() * buff->getTurnosMax();
        }
        this->buff = generarBuff();
    }
    else if(buff->estaActivo() && buff->isUsando())
    {
        buff->reducirTurno();
    }
}

void Personaje::cambiarDebuff()
{
    if(!debuff->estaActivo())
    {
        this->debuff = generarDebuff();
    }
    else
    {
        this->debuff->reducirTurno();
    }
}

void Personaje::aplicarEfectoDebuff()
{
    if(debuff->estaActivo())
    {
        if(esta("Envenenado"))
        {
            this->vida -= debuff->getEfecto();
            cout << " [" << nombre << "] recibe " << debuff->getEfecto() << " de danio por Debuff " << debuff->getNombre() << endl;
            this->debuff->setEfecto(this->debuff->getEfecto() - 1);
            cout << endl << endl;
            system("pause");
        }
        this->debuff->reducirTurno();
    }
    else
    {
        this->debuff = generarDebuff();
    }
}

bool Personaje::esta(string nombre_debuff)
{
    return debuff->getNombre().compare(nombre_debuff) == 0;
}

bool Personaje::operator== (Personaje & p)
{
    return nombre.compare(p.nombre) == 0;
}

ostream & operator<< (ostream & salida, Personaje* & p)
{
    salida<< " [" << p->nombre << "]" << endl
          << " Vida: " << p->vida << endl
          << " Defensa: " << p->defensa << endl
          << " Puntos de accion: " << p->puntos_accion << endl
          << " 1 - " << p->pa_ataque << "PA Ataque (" << p->ataque << ")" << endl
          << " 2 - " << p->pa_curacion << "PA Curacion (" << p->curacion << ")" << endl
          << (p->buff->estaActivo() && !p->buff->isUsando()? " 3 - " + p->buff->informacion() : "-") << endl
          << " Debuff >> " << (p->debuff != NULL? p->debuff->getNombre(): "-") << endl
          << " Buff >> " << (p->buff->estaActivo() && !p->buff->isUsando()? p->buff->getNombre(): "-") << endl;
    return (salida);
}
