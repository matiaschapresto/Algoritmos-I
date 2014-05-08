#include <istream>

#include "reserva.h"

Reserva::Reserva() {}

Reserva::Reserva(const DNI documento, const Fecha fechaDesde, const Fecha fechaHasta,
        const TipoHabitacion tipo) {
    this->_confirmada = false;
    this->_documento = documento;
    this->_fechaDesde = fechaDesde;
    this->_fechaHasta = fechaHasta;
    this->_tipo = tipo;
}

DNI Reserva::documento() const {
    return this->_documento;
}

Fecha Reserva::fechaDesde() const {
    return this->_fechaDesde;
}

Fecha Reserva::fechaHasta() const {
    return this->_fechaHasta;
}

TipoHabitacion Reserva::tipo() const {
    return this->_tipo;
}

bool Reserva::confirmada() const {
    return this->_confirmada;
}

void Reserva::confirmar() {
    this->_confirmada = true;
}

bool Reserva::operator==(const Reserva& r) const {
    bool igualDocumento = this->_documento == r._documento;
    bool igualConfirmada = this->_confirmada == r._confirmada;
    bool igualFechaDesde = this->_fechaDesde == r._fechaDesde;
    bool igualFechaHasta = this->_fechaHasta == r._fechaHasta;
    return igualDocumento && igualConfirmada && igualFechaDesde && igualFechaHasta;
}

ostream& operator<< (ostream& os, const TipoHabitacion & th)
{
    string tipo;
    switch(th){
        case Simple:
            tipo = "Simple";
            break;
        case Doble:
            tipo = "Doble";
            break;
        case Triple:
            tipo = "Triple";
            break;
        case Cuadruple:
        default:
            tipo = "Cuadruple";
            break;
    }
    os << tipo;
    return os;
}

void Reserva::mostrar(std::ostream& os) const {
    os << "Documento: " << this->_documento << endl;
    os << "Fecha Desde: " << this->_fechaDesde << endl;
    os << "Fecha Hasta: " << this->_fechaHasta << endl;
    os << "Tipo Reserva: " << this->_tipo << endl;
    os << "Confirmada: " << (this->_confirmada ? "True" : "False") << endl;
}

void Reserva::guardar(std::ostream& os) const {
    os << (char)this->ENCABEZADO_ARCHIVO << " ";
    os << this->_documento << " ";
    os << this->_fechaDesde << " ";
    os << this->_fechaHasta << " ";
    os << "|" << this->_tipo << "|" << " ";
    os << "|" << (this->_confirmada ? "True" : "False") << "|";
}

istream& Reserva::tomarTipoHabitacion(istream& is, TipoHabitacion & th) const
{
    //borro espacios
    while( is.peek() == ' ' )
        is.ignore();

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
        cerr << "Error en función 'istream& operator>> (istream& is,TipoHabitacion & th)': tipo no reconocido." << endl;
    return is;
}

istream& Reserva::tomarConfirmada (istream& is, bool & val) const
{
    //borro espacios
    while( is.peek() == ' ' )
        is.ignore();

    string confirmada;
    is >> confirmada;
//    cout << confirmada << endl;
    if( confirmada == "|True|" )
        val = true;
    else if( confirmada == "|False|" )
        val = false;
    return is;
}

void Reserva::cargar (std::istream& is) {

    if( is.peek() == Reserva::ENCABEZADO_ARCHIVO )
        is.ignore();

    is >> this->_documento;
    is >> this->_fechaDesde;
    is >> this->_fechaHasta;
    tomarTipoHabitacion(is, this->_tipo);
    tomarConfirmada(is, this->_confirmada);
}

std::ostream & operator<<(std::ostream & os,const Reserva & r) {
    r.guardar(os);
    return os;
}
