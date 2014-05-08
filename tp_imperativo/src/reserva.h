#ifndef RESERVA_H
#define RESERVA_H

#include "tipos.h"
#include "lista.h"

class Reserva
{
    public:
        Reserva();
        Reserva(const DNI documento, const Fecha fechaDesde, const Fecha fechaHasta,
                const TipoHabitacion tipo);

        DNI documento() const;
        Fecha fechaDesde() const;
        Fecha fechaHasta() const;
        TipoHabitacion tipo() const;
        bool confirmada() const;

        void confirmar();
        bool operator==(const Reserva& r) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

    private:
        DNI _documento;
        Fecha _fechaDesde;
        Fecha _fechaHasta;
        TipoHabitacion _tipo;
        bool _confirmada;

        enum {ENCABEZADO_ARCHIVO = 'R'};

        //parsing
        istream& tomarTipoHabitacion(istream& is, TipoHabitacion & th) const;
        istream& tomarConfirmada (istream& is, bool & val) const;
};

std::ostream & operator<<(std::ostream & os,const Reserva & r);

#endif // RESERVA_H
