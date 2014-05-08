#ifndef HABITACION_H
#define HABITACION_H

#include "tipos.h"
#include "lista.h"

class Habitacion
{
    public:
        Habitacion();
        Habitacion(const int n, const TipoHabitacion t, const Lista<Accesorio>& as);

        int numero() const;
        TipoHabitacion tipo() const;
        Lista<Accesorio> accesorios() const;

        bool operator==(const Habitacion& a) const;

        void mostrar(std::ostream& os) const;
        void guardar(std::ostream& os) const;
        void cargar (std::istream& is);

    private:
        int _numero;
        TipoHabitacion _tipo;
        Lista<Accesorio> _accesorios;

        enum {ENCABEZADO_ARCHIVO = 'A'};

        //encoding
        string stringifyAccesorio(const Accesorio&) const;
        string stringifyListaAccesorios(const Lista<Accesorio>& lista) const;
        string stringifyTipoHabitacion(const TipoHabitacion& tipo) const;

        //parsing
        void borrarEspacios(istream& is) const;
        Lista<string> parsearLista(istream& is) const;
        istream& tomarTipoHabitacion (istream& is, TipoHabitacion & th) const;
        istream& tomarAccesorios (istream& is, Lista<Accesorio> & ls) const;
        istream& tomarAccesorio (istream& is, Accesorio & ac) const;
};

int contarAccesorios(const Lista<Accesorio>& as, const Habitacion & hb);
Lista<Habitacion> pretensionesDePopStar(const Lista<Accesorio>& as, const Lista<Habitacion>& hs);
std::ostream & operator<<(std::ostream & os,const Habitacion & a);

#endif // HABITACION_H
