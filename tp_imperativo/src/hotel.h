#ifndef HOTEL_H
#define HOTEL_H

#include "reserva.h"
#include "habitacion.h"

class Hotel
{
    public:
        Hotel();
        Hotel(const Nombre n, const Cadena c, const Lista<Habitacion>& hs,
              const Lista<pair<TipoHabitacion, Dinero> > thxd, const Lista<pair<Accesorio, Dinero> > pa);

        Nombre nombre() const;
        Cadena cadena() const;
        Lista<DNI> huespedes() const;
        Lista<Habitacion> habitaciones() const;
        Lista<pair<CheckIn,Habitacion> > ingresos() const;
        Lista<CheckOut> salidas() const;
        Lista<Reserva> reservas() const;
        Dinero tarifaXDia(const TipoHabitacion t) const;
        Dinero precioAccesorio(const Accesorio a) const;

        void vender(const Cadena c);
        void hacerReserva(const Reserva& r);
        bool sobreReservado(const Fecha f) const;
        void registrarHuesped(const DNI d, const Fecha f, const Habitacion& a);
        void desRegistrarHuesped(const DNI d, const Fecha f);
        Lista<DNI> huespedesConPalabra() const;
        Dinero calcularCuenta(const CheckIn i, const CheckOut o, const Habitacion& hb) const;
        bool reservasSolapadas(const DNI d) const;
        bool operator==(const Hotel& ht) const;

        void mostrar(std::ostream& os) const;
        void guardar(std::ostream& os) const;
        void cargar (std::istream& is);

    private:
        Nombre _nombre;
        Cadena _cadena;
        Lista<Habitacion> _habitaciones;
        Lista<pair<TipoHabitacion, Dinero> > _tarifaXDia;
        Lista<pair<Accesorio, Dinero> > _precioAccesorio;
        Lista<pair<CheckIn,Habitacion> > _ingresos;
        Lista<CheckOut> _salidas;
        Lista<Reserva> _reservas;

        enum {ENCABEZADO_ARCHIVO = 'H'};

        int capacidad() const;
        bool esReservaValida(const Habitacion &hab, const Reserva &reserva, const CheckIn &checkIn, const CheckOut &checkOut) const;

        bool hayReserva(const pair<CheckIn, Habitacion>& in, const CheckOut& co) const;
        Lista<DNI> sacarRepetidos(const Lista<DNI>& dnis) const;
        Lista<DNI> procesarIesimoIngreso( int i ) const;
        bool noHaySalidaEnElMedio(const CheckIn& ci, const CheckOut& co) const;

        //encoding
        string stringifyIngresos(const Lista<pair<CheckIn,Habitacion> > & ingresos) const;
        string stringifySalidas(const Lista<CheckOut> & salidas) const;
        string stringifyReservas(const Lista<Reserva> reservas) const;
        string stringifyHabitaciones(const Lista<Habitacion> habitaciones) const;

        //parsing
        void borrarEspacios(istream& is) const;
        Lista<string> parsearLista(istream& is) const;
        void parsearTupla(istream& is, string& first, string& second) const;
        istream& tomarTexto(istream& is, string & s) const;
        istream& tomarTipoHabitacion (istream& is, TipoHabitacion & th) const;
        istream& tomarAccesorio (istream& is, Accesorio & ac) const;

        istream& tomarHabitaciones (istream& is, Lista<Habitacion> & ls) const;
        bool hallarHabitacionPorNumero(int numero, Habitacion &target) const;
        istream& tomarCheckIn (istream& is, CheckIn & checkIn) const;
        istream& tomarCheckOut (istream& is, CheckOut & checkOut) const;
        istream& tomarIngreso (istream& is, pair<CheckIn,Habitacion> & ingreso) const;
        istream& tomarIngresos (istream& is, Lista<pair<CheckIn,Habitacion> > & ingresos) const;
        istream& tomarSalidas (istream& is, Lista<CheckOut> & salidas) const;
        istream& tomarReservas (istream& is, Lista<Reserva> & reservas) const;
        istream& tomarTarifas (istream& is, Lista<pair<TipoHabitacion, Dinero> > & tarifas) const;
        istream& tomarTarifa (istream& is, pair<TipoHabitacion, Dinero> & thd) const;
        istream& tomarPrecioAccesorios (istream& is, Lista<pair<Accesorio, Dinero> > & precios) const;
        istream& tomarPrecioAccesorio (istream& is, pair<Accesorio, Dinero> & precio) const;
};

std::ostream & operator<<(std::ostream & os,const Hotel & h);

#endif // HOTEL_H
