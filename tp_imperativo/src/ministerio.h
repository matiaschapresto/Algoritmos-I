#ifndef MINISTERIO_H
#define MINISTERIO_H

#include "hotel.h"

class Ministerio
{
    public:
        Ministerio();
        Ministerio(const Lista<Provincia>& ps);

        Lista<Provincia> secretarias() const;
        Lista<Hotel> registro(const Provincia p) const;
        Lista<Lista<Hotel> > cadenasDeHoteles() const;

        void agregarHotel(const Hotel& h, const Provincia p);
        Lista<Cadena> cadenasAmarretas() const;
        void fusionAutorizada(const Cadena c1, const Cadena c2);
        bool operator==(const Ministerio& m) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

    private:
        Lista<Provincia> _provincias;
        Lista<pair<Provincia, Hotel> > _registro;

        Lista<pair<Cadena,Lista<Provincia> > > provinciasPorCadena() const;

        enum {ENCABEZADO_ARCHIVO = 'M'};

        void borrarEspacios(istream& is) const;
        istream& tomarTexto(istream& is, string & s) const;
        Lista<string> parsearLista(istream& is) const;
        void parsearTupla(istream& is, string& first, string& second) const;
        istream& tomarRegistroYProvincias (istream& is,
            Lista<pair<Provincia,Lista<Hotel> > > & listados) const;
        istream& tomarProvinciaListaHoteles (istream& is,
            pair<Provincia,Lista<Hotel> > & phs) const;
        istream& tomarListaHoteles (istream& is, Lista<Hotel> & hoteles) const;
        string stringifyRegistro() const;
        template <typename T1, typename T2>
        string stringifyPair(const pair<T1, T2> par, bool lastElement) const;
        string stringifySecretarias() const;
        string stringifyCadenas() const;
};

std::ostream & operator<<(std::ostream & os,const Ministerio & m);

#endif // MINISTERIO_H
