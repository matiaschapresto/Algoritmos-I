#include <sstream>

#include "habitacion.h"

Habitacion::Habitacion() {
}

Habitacion::Habitacion(const int n, const TipoHabitacion t, const Lista<Accesorio>& as) {
    this->_numero = n;
    this->_tipo = t;
    this->_accesorios = as;
}

int Habitacion::numero() const {
    return this->_numero;
}

TipoHabitacion Habitacion::tipo() const {
    return this->_tipo;
}

Lista<Accesorio> Habitacion::accesorios() const {
    return this->_accesorios;
}

bool Habitacion::operator==(const Habitacion& a) const {
    bool mismoTipo = this->_tipo == a._tipo;
    bool mismosAccesorios = this->_accesorios == a._accesorios;
    bool mismoNumero = this->_numero == a._numero;
    return mismoTipo && mismosAccesorios && mismoNumero;
}

void Habitacion::mostrar(std::ostream& os) const {
    os << "Numero: " << this->_numero << "\t";
    os << "Tipo: " << this->stringifyTipoHabitacion(this->_tipo) << "\t";
    os << "Accesorios: " << this->stringifyListaAccesorios(this->_accesorios) << endl;
}
void Habitacion::guardar(std::ostream& os) const {

    os << (char)this->ENCABEZADO_ARCHIVO << " " << this->_numero << " |" << this->stringifyTipoHabitacion(this->_tipo) << "| " << this->stringifyListaAccesorios(this->_accesorios);

}

void Habitacion::cargar (std::istream& is) {

    if( is.peek() == Habitacion::ENCABEZADO_ARCHIVO )
        is.ignore();

    is >> this->_numero;
    tomarTipoHabitacion( is, this->_tipo);
    tomarAccesorios( is, this->_accesorios);
}

int contarAccesorios(const Lista<Accesorio>& as, const Habitacion & hb)
{
    int cantidadDeAccesorios  = 0;
    int i = 0;
    while ( i < as.longitud() )
    {
        Accesorio accesorio = as.iesimo(i);
        if( hb.accesorios().pertenece(accesorio) )
            cantidadDeAccesorios++;
        i++;
    }
    return cantidadDeAccesorios;
}

Lista<Habitacion> pretensionesDePopStar(const Lista<Accesorio>& as, const Lista<Habitacion>& hs) {

    Lista<Habitacion> result;
    int maxCantAccesorios = -1;
    int i = 0;
    while( i < hs.longitud() )
    {
        Habitacion hb = hs.iesimo(i);
        if( result.longitud() == 0 ) {
            result.agregar(hb);
            maxCantAccesorios = contarAccesorios(as, hb);
        }
        else {
            int accesoriosHb = contarAccesorios(as, hb);
            if( accesoriosHb > maxCantAccesorios ) {
                Lista<Habitacion> nuevoRes;
                nuevoRes.agregar(hb);
                maxCantAccesorios = accesoriosHb;
                result = nuevoRes;
            } else if (accesoriosHb == maxCantAccesorios)
                result.agregar(hb);
        }
        i++;
    }
    return result;
}

std::ostream & operator<<(std::ostream & os,const Habitacion & a) {
    a.mostrar(os);
    return os;
}


/// auxiliares de IO

string Habitacion::stringifyTipoHabitacion(const TipoHabitacion& tipo) const{
    string tipoStr;
    switch(tipo){
        case Simple: tipoStr = "Simple";break;
        case Doble: tipoStr = "Doble";break;
        case Triple: tipoStr = "Triple";break;
        case Cuadruple: tipoStr = "Cuadruple";break;
    }
    return tipoStr;
}

string Habitacion::stringifyListaAccesorios(const Lista<Accesorio>& lista) const{

    int i = 0;
    ostringstream buffer;
    buffer.clear();
    if(lista.longitud()>0){
        buffer << "[";
        while(i<lista.longitud()-1){
            buffer << "(|" << stringifyAccesorio(lista.iesimo(i)) << "|), ";
            i++;
        }
        //agrego el ultimo hardcodeado por el ),
        buffer << "(|" << stringifyAccesorio(lista.iesimo(lista.longitud()-1)) << "|)";
        buffer << "]";
    }else{
        buffer << "[]";
    }
    return buffer.str();
}

string Habitacion::stringifyAccesorio(const Accesorio& accesorio) const{

    string accesorioStr;
    switch(accesorio){
        case Jacuzzi: accesorioStr="Jacuzzi";break;
        case LCD: accesorioStr="LCD";break;
        case PS3: accesorioStr="PS3";break;
        case DVD: accesorioStr="DVD";break;
        case Pelotero: accesorioStr="Pelotero";break;
        case Inflable: accesorioStr="Inflable";break;
    }
    return accesorioStr;
}

void Habitacion::borrarEspacios(istream& is) const
{
    while( is.peek() == ' ' )
        is.ignore();
}

Lista<string> Habitacion::parsearLista(istream& is) const
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
                    elementos.agregarAtras(elemento);
                parentesis--;
                break;
            default:
                break;
        }
    } while( corchetes > 0 );
    return elementos;
}

istream& Habitacion::tomarTipoHabitacion (istream& is, TipoHabitacion & th) const
{
    borrarEspacios(is);

    string tipo;
    is >> tipo;
    tipo = tipo.substr(1,tipo.size()-2);
    if( tipo == "Simple")
        th = Simple;
    else if( tipo == "Doble")
        th = Doble;
    else if( tipo == "Triple")
        th = Triple;
    else if( tipo == "Cuadruple")
        th = Cuadruple;
    else
        cerr << "Error en función 'istream& Habitacion::tomarTipoHabitacion (istream& is, TipoHabitacion & th)': tipo no reconocido." << endl;
    return is;
}

istream& Habitacion::tomarAccesorio (istream& is, Accesorio & ac) const
{
    borrarEspacios(is);

    string accesorio;
    is >> accesorio;
    borrarEspacios(is);
    accesorio = accesorio.substr(1,accesorio.size()-2);
    if( accesorio == "Jacuzzi" )
        ac = Jacuzzi;
    else if( accesorio == "LCD" )
        ac = LCD;
    else if( accesorio == "PS3" )
        ac = PS3;
    else if( accesorio == "DVD" )
        ac = DVD;
    else if( accesorio == "Pelotero" )
        ac = Pelotero;
    else if( accesorio == "Inflable" )
        ac = Inflable;
    else
        cerr << "Error en función 'istream& Habitacion::tomarAccesorio (istream& is, Accesorio & ac)': accesorio no reconocido." << endl;
    return is;
}

istream& Habitacion::tomarAccesorios (istream& is, Lista<Accesorio> & ls) const
{
    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
        //cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        Accesorio acc;
        tomarAccesorio(stream, acc);
        ls.agregarAtras(acc);
        i++;
    }

    return is;
}
