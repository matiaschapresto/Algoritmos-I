#include "ministerio.h"
#include "limits.h"

#include <sstream>
#include <fstream>

Ministerio::Ministerio() {
}
Ministerio::Ministerio(const Lista<Provincia>& ps) {
    this->_provincias = ps;
}
Lista<Provincia> Ministerio::secretarias() const {
    return this->_provincias;
}
Lista<Hotel> Ministerio::registro(const Provincia p) const {

    Lista<Hotel> result;

    int i = 0;
    while (i<this->_registro.longitud()){

        pair<Provincia, Hotel> parProvinciaHotel = this->_registro.iesimo(i);

        if(parProvinciaHotel.first == p)
            result.agregar(parProvinciaHotel.second);
        i++;
    }

    return result;
}

Lista<Lista<Hotel> > Ministerio::cadenasDeHoteles() const {

    Lista<Lista<Hotel> > result;

    //creo copia del registro
    Lista<pair<Provincia, Hotel> > registro = this->_registro;

    //mientras que la copia no esté vacía, tomo la cabeza
    //agrego todos los hoteles de esa cadena a una lista,
    //eliminandolos de la copia del registro
    while( registro.longitud() > 0 ) {

        Hotel hotel = registro.cabeza().second;
        Cadena cadena = hotel.cadena();
        Lista<Hotel> listaDeCadena;

        int i = 0;
        while( i < registro.longitud() ) {

            Hotel otroHotel = registro.iesimo(i).second;

            if( otroHotel.cadena() == cadena ){
                registro.eliminarPosicion(i--);
                listaDeCadena.agregar( otroHotel );
            }
            i++;
        }
        result.agregar(listaDeCadena);
    }
    return result;
}

void Ministerio::agregarHotel(const Hotel& h, const Provincia p) {

    pair<Provincia, Hotel> ph = pair<Provincia, Hotel>(p, h);
    this->_registro.agregar(ph);
}

Lista<pair<Cadena,Lista<Provincia> > > Ministerio::provinciasPorCadena() const {

    Lista<pair<Cadena,Lista<Provincia> > > result;
    int i = 0;
    while( i < this->_registro.longitud() )
    {
        Provincia provincia = this->_registro.iesimo(i).first;
        Cadena cadena = this->_registro.iesimo(i).second.cadena();

        bool cadenaExiste = false;
        int j = 0;
        while( j < result.longitud() && cadenaExiste == false )
        {
            Cadena cadenaEnResult = result.iesimo(j).first;
            Lista<Provincia> provinciasEnResult = result.iesimo(j).second;
            if( cadenaEnResult == cadena )
            {
                cadenaExiste = true;
                if( provinciasEnResult.cantidadDeApariciones(provincia) == 0 )
                {
                    provinciasEnResult.agregar(provincia);
                    result.eliminarPosicion(j);
                    result.agregar(pair<Cadena,Lista<Provincia> >(cadena,provinciasEnResult));
                }
            }
            j++;
        }
        if(cadenaExiste == false)
        {
            Lista<Provincia> listaProvincias;
            listaProvincias.agregar(provincia);
            result.agregar(pair<Cadena,Lista<Provincia> >(cadena, listaProvincias));
        }
        i++;
    }

    return result;
}

Lista<Cadena> Ministerio::cadenasAmarretas() const {

    Lista<pair<Cadena,Lista<Provincia> > > provinciasPorCadena = this->provinciasPorCadena();

    Lista<Cadena> result;
    int minHastaAhora = INT_MAX;
    int i = 0;
    while( i < provinciasPorCadena.longitud() )
    {
        Cadena cadena = provinciasPorCadena.iesimo(i).first;
        Lista<Provincia> provincias = provinciasPorCadena.iesimo(i).second;
        if(result.longitud() == 0)
        {
            result.agregar(cadena);
            minHastaAhora = provincias.longitud();
        } else {
            int cantidadDeProvincias = provincias.longitud();
            if( cantidadDeProvincias < minHastaAhora )
            {
                Lista<Cadena> nuevoRes;
                nuevoRes.agregar(cadena);
                result = nuevoRes;
                minHastaAhora = cantidadDeProvincias;
            } else if (cantidadDeProvincias == minHastaAhora) {
                result.agregar(cadena);
            }
        }
        i++;
    }

    return result;
}
void Ministerio::fusionAutorizada(const Cadena c1, const Cadena c2) {

    int i = 0;
    while( i < this->_registro.longitud() )
    {
        Provincia provincia = this->_registro.iesimo(i).first;
        Hotel hotel = this->_registro.iesimo(i).second;
        if( hotel.cadena() == c2 )
        {
            hotel.vender(c1);
            this->_registro.eliminarPosicion(i--);
            this->_registro.agregar(pair<Provincia, Hotel>(provincia, hotel));
        }
        i++;
    }
}
bool Ministerio::operator==(const Ministerio& m) const {
    bool mismasProvincias = mismos(this->_provincias,m._provincias);
    bool mismosRegistros = mismos(this->_registro,m._registro);
    return mismasProvincias && mismosRegistros;
}

void Ministerio::mostrar(std::ostream& os) const {
    os << "Secretarias: " << this->stringifySecretarias() << endl;
    os << "Cadenas: " << this->stringifyCadenas() << endl;
    os << "Registro: " << this->stringifyRegistro() << endl;
}

string Ministerio::stringifySecretarias() const{
    ostringstream os;
    os.clear();
    int i = 0;
    os << "[";
    Lista<Provincia> secretarias = this->secretarias();
    if(secretarias.longitud()>0){
        while(i<secretarias.longitud()-1){
            os << "|";
            os << secretarias.iesimo(i);
            os << "|, ";
            i++;
        }
        os << "|";
        os << secretarias.iesimo(secretarias.longitud()-1);
        os << "|";
    }
    os << "]";
    return os.str();
}

string Ministerio::stringifyCadenas() const{
    ostringstream os;
    os.clear();
    int i = 0;
    os << "[";
    Lista<Lista<Hotel> > cadenasDeHoteles = this->cadenasDeHoteles();
    if(cadenasDeHoteles.longitud()>0){
        while(i<cadenasDeHoteles.longitud()-1){
            os << "|";
            os << cadenasDeHoteles.iesimo(i).iesimo(0).cadena();
            os << "|, ";
            i++;
        }
        os << "|";
        os << cadenasDeHoteles.iesimo(cadenasDeHoteles.longitud()-1).iesimo(0).cadena();
        os << "|";
    }
    os << "]";
    return os.str();
}

void Ministerio::cargar (std::istream& is) {

    if( is.peek() == Ministerio::ENCABEZADO_ARCHIVO )
        is.ignore();
    Lista<pair<Provincia,Lista<Hotel> > > listados;
    tomarRegistroYProvincias(is, listados);

    int i = 0;
    while( i < listados.longitud() )
    {
        Provincia p = listados.iesimo(i).first;
        Lista<Hotel> hoteles = listados.iesimo(i).second;
        if( this->_provincias.cantidadDeApariciones(p) == 0 )
            this->_provincias.agregarAtras(p);
        int j = 0;
        while( j < hoteles.longitud() )
        {
            this->_registro.agregar(pair<Provincia,Hotel>(p,hoteles.iesimo(j)));
            j++;
        }
        i++;
    }
}
std::ostream & operator<<(std::ostream & os,const Ministerio & m) {
    m.mostrar(os);
    return os;
}

void Ministerio::borrarEspacios(istream& is) const
{
    while( is.peek() == ' ' )
        is.ignore();
}

istream& Ministerio::tomarTexto(istream& is, string & s) const
{
    borrarEspacios(is);

    is.ignore();  //evito primer pipe
    char c;
    do{
        is >> noskipws >> c;
        s.append(1,c);
    } while (is.peek() != '|' );
    is.ignore(); //evito ultimo pipe

    return is;
}

Lista<string> Ministerio::parsearLista(istream& is) const
{
    borrarEspacios(is);

    Lista<string> elementos;
    string elemento = "";
    int corchetes = 0, parentesis = 0;

    char c;
    do{
        is >> noskipws >> c;
        elemento.append(1,c);
        switch(c)
        {
            case '[':
                corchetes++;
                break;
            case ']':
                corchetes--;
                break;
            case '(':
                if( parentesis == 0 )
                    elemento = "(";
                parentesis++;
                break;
            case ')':
                if( parentesis == 1 )
                    elementos.agregar(elemento);
                parentesis--;
                break;
            default:
                break;
        }
    } while( corchetes > 0 );
    return elementos;
}

void Ministerio::parsearTupla(istream& is, string& first, string& second) const
{
    borrarEspacios(is);

    first = "";
    second = "";
    int llenandoElemento = 0;  //0 para first, 1 para second
    int corchetes = 0, parentesis = 0;

    char c;
    while( is.peek() != -1 ) {
        is >> noskipws >> c;
        switch(c)
        {
            case '[':
                corchetes++;
                break;
            case ']':
                corchetes--;
                break;
            case '(':
                parentesis++;
                break;
            case ')':
                parentesis--;
                break;
            case ',':
                //comienzo segundo elemento
                if(corchetes == 0 && parentesis == 0)
                {
                    llenandoElemento = 1;
                    //borro espacios
                    while( is.peek() == ' ' )
                        is.ignore();
                    is >> noskipws >> c;
                }
                break;
            default:
                break;
        }
        if( llenandoElemento == 0 )
            first.append(1,c);
        else
            second.append(1,c);
    }
    //permitir tuplas con y sin parentesis
    if( first.at(0) == '(' && first.at(first.size()-1) == ')')
        first = first.substr(1,first.size()-2);
    if( second.at(0) == '(' && second.at(second.size()-1) == ')')
        second = second.substr(1,second.size()-2);
}

istream& Ministerio::tomarRegistroYProvincias (istream& is,
    Lista<pair<Provincia,Lista<Hotel> > > & listados) const
{

    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
        //cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        pair<Provincia,Lista<Hotel> > phs;
        tomarProvinciaListaHoteles(stream, phs);
        listados.agregar(phs);
        i++;
    }

    return is;
}

istream& Ministerio::tomarProvinciaListaHoteles (istream& is,
    pair<Provincia,Lista<Hotel> > & phs) const
{
    string first,second;
    parsearTupla(is,first,second);

    stringstream streamFirst(first);
    stringstream streamSecond(second);
    tomarTexto (streamFirst, phs.first);
    tomarListaHoteles(streamSecond, phs.second);

    return is;
}

istream& Ministerio::tomarListaHoteles (istream& is, Lista<Hotel> & hoteles) const
{
    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
        //cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        Hotel h;
        h.cargar(stream);
        hoteles.agregar(h);
        i++;
    }

    return is;
}

void Ministerio::guardar(std::ostream& os) const {
    os << (char)this->ENCABEZADO_ARCHIVO << " ";
    os << stringifyRegistro();
}

template <typename T1, typename T2>
string Ministerio::stringifyPair(const pair<T1, T2> par, bool lastElement) const
{
    ostringstream buffer;
    buffer.clear();
    buffer << "(|";
    buffer << par.first;
    buffer << "|, [";
    int j = 0;
    Lista<Hotel> registro = par.second;
    if(registro.longitud()>0){
        while(j<registro.longitud()-1){
            buffer << "(";
            registro.iesimo(j).guardar(buffer);
            buffer << "), ";
            j++;
        }
        buffer << "(";
        registro.iesimo(registro.longitud()-1).guardar(buffer);
        buffer << ")";
    }
    if(lastElement){
        buffer << "])";
    }else{
        buffer << "]), ";
    }
    return buffer.str();
}

string Ministerio::stringifyRegistro() const{
    ostringstream buffer;
    buffer.clear();
    buffer << "[";
    int i = 0;
    if(this->_provincias.longitud()>0){
        while(i < this->_provincias.longitud()-1 ){
            Provincia prov = this->_provincias.iesimo(i);
            Lista <Hotel> registro = this->registro(prov);
            pair<Provincia, Lista<Hotel> > elemento = make_pair(prov, this->registro(prov));
            buffer << this->stringifyPair(elemento, false);
            i++;
        }
        Provincia prov = this->_provincias.iesimo(this->_provincias.longitud()-1);
        pair<Provincia, Lista<Hotel> > elemento = make_pair(prov, this->registro(prov));
        buffer << this->stringifyPair(elemento, true);
    }
    buffer << "]";
    return buffer.str();
}
