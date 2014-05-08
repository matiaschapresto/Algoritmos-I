#include <sstream>

#include "hotel.h"

Hotel::Hotel() {
}
Hotel::Hotel(const Nombre n, const Cadena c, const Lista<Habitacion>& hs,
      const Lista<pair<TipoHabitacion, Dinero> > thxd, const Lista<pair<Accesorio, Dinero> > pa) {

    this->_nombre = n;
    this->_cadena = c;
    this->_habitaciones = hs;
    this->_tarifaXDia = thxd;
    this->_precioAccesorio = pa;
    Lista<pair<CheckIn,Habitacion> > ingresosVacios;
    Lista<CheckOut> salidasVacias;
    Lista<Reserva> reservasVacias;
    this->_ingresos = ingresosVacios;
    this->_salidas = salidasVacias;
    this->_reservas = reservasVacias;
}
Nombre Hotel::nombre() const {
    return this->_nombre;
}
Cadena Hotel::cadena() const {
    return this->_cadena;
}

Lista<DNI> Hotel::huespedes() const {

    Lista<DNI> dnisDeIngresos;
    Lista<DNI> dnisDeSalidas;

    int i = 0;
    while( i < this->_ingresos.longitud() )
    {
        CheckIn checkIn = this->_ingresos.iesimo(i).first;
        DNI dni = checkIn.first;
        dnisDeIngresos.agregar(dni);
        i++;
    }

    i = 0;
    while( i < this->_salidas.longitud() )
    {
        CheckOut checkOut = this->_salidas.iesimo(i);
        DNI dni = checkOut.first;
        dnisDeSalidas.agregar(dni);
        i++;
    }

    Lista<DNI> resultado;
    i = 0;
    while( i < dnisDeIngresos.longitud() )
    {
        DNI dni = dnisDeIngresos.iesimo(i);
        int cantIngresos = dnisDeIngresos.cantidadDeApariciones(dni);
        int cantSalidas = dnisDeSalidas.cantidadDeApariciones(dni);
        if( cantIngresos - cantSalidas == 1 )
            resultado.agregar(dni);
        i++;
    }

    return resultado;
}

Lista<Habitacion> Hotel::habitaciones() const {
    return this->_habitaciones;
}

Lista<pair<CheckIn,Habitacion> > Hotel::ingresos() const {
    return this->_ingresos;
}

Lista<CheckOut> Hotel::salidas() const {
    return this->_salidas;
}

Lista<Reserva> Hotel::reservas() const {
    return this->_reservas;
}

Dinero Hotel::tarifaXDia(const TipoHabitacion t) const {
    Dinero retorno = -1;
    int i = 0;
    bool flag = false;
    while( (i < this->_tarifaXDia.longitud()) && (!flag) )
    {
        pair<TipoHabitacion, Dinero> e = this->_tarifaXDia.iesimo(i);
        if(e.first == t){
            retorno = e.second;
            flag = true;
        }
        i++;
    }
    if(!flag){
        std::cerr << "Error en funcion 'Dinero Hotel::tarifaXDia(const TipoHabitacion t) const': no cumple la especificación." << std::endl;
    }
    return retorno;
}

Dinero Hotel::precioAccesorio(const Accesorio a) const {
    Dinero retorno = -1;
    bool flag = false;
    int i = 0;
    while( (i < this->_precioAccesorio.longitud()) && (!flag) )
    {
        pair<Accesorio, Dinero> e = this->_precioAccesorio.iesimo(i);
        if(e.first == a){
             retorno = e.second;
             flag=true;
        }
        i++;
    }
    if(!flag){
        std::cerr << "Error en funcion 'Dinero Hotel::precioAccesorio(const Accesorio a) const': no cumple la especificación." << std::endl;
    }
    return retorno;
}

void Hotel::vender(const Cadena c) {
    this->_cadena = c;
}

void Hotel::hacerReserva(const Reserva& r) {
    this->_reservas.agregar(r);
}

int plazasSegunTipoDeHabitacion(TipoHabitacion thb)
{
    int plazas = 0;
    switch( thb )
    {
        case Simple:
            plazas = 1;
            break;
        case Doble:
            plazas = 2;
            break;
        case Triple:
            plazas = 3;
            break;
        case Cuadruple:
        default:
            plazas = 4;
            break;
    }
    return plazas;
}

int Hotel::capacidad() const
{
    int capacidad = 0;
    int i = 0;
    while( i < this->_habitaciones.longitud() )
    {
        Habitacion hb = this->_habitaciones.iesimo(i);
        capacidad += plazasSegunTipoDeHabitacion(hb.tipo());
        i++;
    }
    return capacidad;
}

bool Hotel::sobreReservado(const Fecha f) const {

    int plazasReservadas = 0;
    int i = 0;
    while( i < this->_reservas.longitud() )
    {
        Reserva r = this->_reservas.iesimo(i);
        if( r.fechaDesde() <= f && f <= r.fechaHasta() )
            plazasReservadas += plazasSegunTipoDeHabitacion(r.tipo());
        i++;
    }
    return this->capacidad() < plazasReservadas;
}

void Hotel::registrarHuesped(const DNI d, const Fecha f, const Habitacion& a) {
    pair<DNI,Fecha> checkIn = pair<DNI,Fecha>(d,f);
    pair<CheckIn,Habitacion> ingreso = pair<CheckIn,Habitacion>(checkIn,a) ;
    this->_ingresos.agregar(ingreso);

    int i = 0;
    while(i<this->_reservas.longitud()){
        Reserva r = this->_reservas.iesimo(i);
        if( r.documento() == d && r.fechaDesde() == f && r.tipo() == a.tipo()){
            r.confirmar();
            this->_reservas.eliminarPosicion(i);
            this->_reservas.agregar(r);
            break;
        }
        i++;
    }
}

void Hotel::desRegistrarHuesped(const DNI d, const Fecha f) {
    pair<DNI, Fecha> checkOut = pair<DNI, Fecha>(d,f);
    this->_salidas.agregar(checkOut);
}


Lista<DNI> Hotel::huespedesConPalabra() const {
    Lista<DNI> result;
    int i = 0;
    
    while( i < this->_ingresos.longitud() ) {
        result.concatenar( procesarIesimoIngreso( i ) );
        i++;
    }
    result = sacarRepetidos(result);
    return result;
}

bool Hotel::hayReserva(const pair<CheckIn, Habitacion>& ingreso, const CheckOut& checkOut) const {
    bool hayUnaReserva = false;
    int i = 0;
    int longitud = this->_reservas.longitud();

    while(i < longitud){
        hayUnaReserva = hayUnaReserva ||
                (esReservaValida(ingreso.second, (this->_reservas.iesimo(i)), ingreso.first, checkOut));
        i++;
    }
    return hayUnaReserva;
}

bool Hotel::esReservaValida(const Habitacion &hab, const Reserva &reserva, const CheckIn &checkIn, const CheckOut &checkOut) const{
    return ((reserva.documento() == checkIn.first) &&
        (reserva.fechaDesde() == checkIn.second) &&
        (reserva.fechaHasta() == checkOut.second) &&
        (reserva.tipo() ==  hab.tipo()) &&
        (reserva.confirmada()));
}

Lista<DNI> Hotel::sacarRepetidos(const Lista<DNI>& dnis) const {
	Lista<DNI> result;
	int i = 0;
	int longitud = dnis.longitud();

	while( i < longitud ){
		if( !result.pertenece(dnis.iesimo(i)) ){
			result.agregarAtras(dnis.iesimo(i));
		}
		i++;
	}
	return result;
}


Lista<DNI> Hotel::procesarIesimoIngreso( int i ) const {
    pair<CheckIn,Habitacion> in = this->_ingresos.iesimo(i);
    CheckIn ci = in.first;
    Lista<DNI> result;
	int longitud = this->_salidas.longitud();
    int j = 0;

    while( j < longitud ) {

        CheckOut co = this->_salidas.iesimo(j);
        if( ci.first == co.first && noHaySalidaEnElMedio(ci,co) && hayReserva(in,co) )
            result.agregarAtras( ci.first );
         j++;
    }
    return result;
}

bool Hotel::noHaySalidaEnElMedio(const CheckIn& ci, const CheckOut& co) const {
    bool result = false;
    int i = 0;
	int longitud = this->_salidas.longitud();

    while( i < longitud ) {
        CheckOut oco = this->_salidas.iesimo(i);
        result = result || (ci.first == oco.first && ci.second < oco.second && oco.second < co.second);
        i++;
    }
    return !result;
}

Dinero Hotel::calcularCuenta(const CheckIn i, const CheckOut o, const Habitacion& hb) const {
    int precioAccesorios = 0;
    int ind = 0;
    Lista<Accesorio> accesorios = hb.accesorios();

    while( ind < accesorios.longitud() )
    {
        Accesorio accesorio = accesorios.iesimo(ind);
        precioAccesorios += this->precioAccesorio(accesorio);
        ind++;
    }

    int cantidadDeDias = o.second - i.second;
    int precioHabitacion = this->tarifaXDia(hb.tipo()) * cantidadDeDias;

    return precioAccesorios + precioHabitacion;
}

bool Hotel::reservasSolapadas(const DNI d) const {

    Lista<int> fechasReservadas;
    int i = 0;
    while( i < this->_reservas.longitud() )
    {
        Reserva r = this->_reservas.iesimo(i);
        if( r.documento() == d ){
            //para evitar que cuelgue el programa si alguien ingresa mal los datos.
            if( r.fechaHasta() < r.fechaDesde() )
            {
                std::cerr << "Error en función 'bool Hotel::reservasSolapadas(const DNI d) const': la reserva no cumple la especificación" << std::endl;
                break;
            }
            int f =  r.fechaDesde();
            while( f <= r.fechaHasta() )
            {
                fechasReservadas.agregar(f);
                f++;
            }
        }
        i++;
    }

    bool haySolapamiento = false;
    i = 0;
    while( i < fechasReservadas.longitud() && haySolapamiento == false )
    {
        Fecha f = fechasReservadas.iesimo(i);
        if( fechasReservadas.cantidadDeApariciones(f) > 1 )
        {
            haySolapamiento = true;
        }
        i++;
    }

    return haySolapamiento;
}
bool Hotel::operator==(const Hotel& ht) const {

    bool nombreEquiv = this->_nombre == ht._nombre;
    bool cadenaEquiv = this->_cadena == ht._cadena;
    bool habitacionesEquiv = mismos(this->_habitaciones , ht._habitaciones);
    bool tarifaXDiaEquiv = mismos(this->_tarifaXDia, ht._tarifaXDia);
    bool precioAccesorioEquiv = mismos(this->_precioAccesorio, ht._precioAccesorio);
    bool ingresosEquiv = mismos(this->_ingresos, ht._ingresos);
    bool salidasEquiv = mismos(this->_salidas, ht._salidas);
    bool reservasEquiv = mismos(this->_reservas, ht._reservas);
    return  nombreEquiv &&
            cadenaEquiv &&
            habitacionesEquiv &&
            tarifaXDiaEquiv &&
            precioAccesorioEquiv &&
            ingresosEquiv &&
            salidasEquiv &&
            reservasEquiv;
}

void Hotel::mostrar(std::ostream& os) const {
    os << "Nombre:\t" << this->_nombre << endl;
    os << "Cadena:\t" << this->_cadena << endl;
    os << "Habitaciones:\t" << this->stringifyHabitaciones(this->_habitaciones) << endl;
    os << "Ingresos:\t" << this->stringifyIngresos(this->_ingresos) << endl;
    os << "Salidas:\t" << this->stringifySalidas(this->_salidas) << endl;
    os << "Reservas:\t" << this->stringifyReservas(this->_reservas) << endl;
}

void Hotel::guardar(std::ostream& os) const {
    os << (char)this->ENCABEZADO_ARCHIVO;
    os << " |" << this->_nombre << "|";
    os << " |" << this->_cadena << "| ";
    os << this->stringifyHabitaciones(this->_habitaciones) << " ";
    os << this->stringifyIngresos(this->_ingresos) << " ";
    os << this->stringifySalidas(this->_salidas) << " ";
    os << this->stringifyReservas(this->_reservas);
}

void Hotel::cargar (istream& is) {

    if( is.peek() == Hotel::ENCABEZADO_ARCHIVO )
        is.ignore();

    tomarTexto(is, this->_nombre);
    tomarTexto(is, this->_cadena);
    tomarHabitaciones(is, this->_habitaciones);
    tomarIngresos(is, this->_ingresos);
    tomarSalidas(is, this->_salidas);
    tomarReservas(is, this->_reservas);
    tomarTarifas(is, this->_tarifaXDia);
    tomarPrecioAccesorios(is, this->_precioAccesorio);
}

std::ostream & operator<<(std::ostream & os,const Hotel & h) {
    h.mostrar(os);
    return os;
}

string Hotel::stringifyHabitaciones(const Lista<Habitacion> habitaciones) const{
    ostringstream buffer;
    buffer.clear();
    buffer << "[";
    if(habitaciones.longitud()>0){
        int i = 0;
        while(i<habitaciones.longitud()-1){
            buffer << "(";
            habitaciones.iesimo(i).guardar(buffer);
            buffer << "),";
            i++;
        }
        buffer << "(";
        habitaciones.iesimo(habitaciones.longitud()-1).guardar(buffer);
        buffer << ")";
    }
    buffer << "]";
    return buffer.str();
}

string Hotel::stringifyReservas(const Lista<Reserva> reservas) const{
    ostringstream buffer;
    buffer.clear();
    buffer << "[";
    if(reservas.longitud()>0){
        int i = 0;
        while(i<reservas.longitud()-1){
            buffer << "(";
            reservas.iesimo(i).guardar(buffer);
            buffer << "), ";
            i++;
        }
        buffer << "(";
        reservas.iesimo(reservas.longitud()-1).guardar(buffer);
        buffer << ")";
    }
    buffer << "]";
    return buffer.str();
}

string Hotel::stringifyIngresos(const Lista<pair<CheckIn,Habitacion> > & ingresos) const{
    ostringstream buffer;
    buffer.clear();
    buffer << "[";
    if(ingresos.longitud()>0){
        int i=0;
        while(i<ingresos.longitud()-1){
            pair<CheckIn, Habitacion> item = ingresos.iesimo(i);
            pair<CheckIn, int> stringItem = make_pair(item.first, item.second.numero());
            buffer << "((" << stringItem.first.first << ", " << stringItem.first.second << "), " << stringItem.second << "), ";
            i++;
        }
        pair<CheckIn, Habitacion> item = ingresos.iesimo(ingresos.longitud()-1);
        pair<CheckIn, int> stringItem = make_pair(item.first, item.second.numero());
        buffer << "((" << stringItem.first.first << ", " << stringItem.first.second << "), " << stringItem.second << ")";
    }
    buffer << "]";
    return buffer.str();
}

string Hotel::stringifySalidas(const Lista<CheckOut> & salidas) const{
    ostringstream buffer;
    buffer.clear();
    buffer << "[";
    if(salidas.longitud()>0){
        int i=0;
        while(i<salidas.longitud()-1){
            pair<DNI, Fecha> item = salidas.iesimo(i);
            buffer << "(" << item.first << ", " << item.second << "), ";
            i++;
        }
        pair<DNI, Fecha> item = salidas.iesimo(salidas.longitud()-1);
        buffer << "(" << item.first << ", " << item.second << ")";
    }
    buffer << "]";
    return buffer.str();
}

void Hotel::borrarEspacios(istream& is) const
{
    while( is.peek() == ' ' )
        is.ignore();
}

Lista<string> Hotel::parsearLista(istream& is) const
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

void Hotel::parsearTupla(istream& is, string& first, string& second) const
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

istream& Hotel::tomarTexto(istream& is, string & s) const
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

istream& Hotel::tomarTipoHabitacion (istream& is, TipoHabitacion & th) const
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
        cerr << "Error en función 'istream& Hotel::tomarTipoHabitacion (istream& is, TipoHabitacion & th)': tipo no reconocido." << endl;
    return is;
}

istream& Hotel::tomarAccesorio (istream& is, Accesorio & ac) const
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
        cerr << "Error en función 'istream& Hotel::tomarAccesorio (istream& is, Accesorio & ac)': accesorio no reconocido." << endl;
    return is;
}

istream& Hotel::tomarHabitaciones (istream& is, Lista<Habitacion> & ls) const {

    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
        elemento = elemento.substr(1,elemento.size()-2);
        //cout << elemento << endl;
        stringstream stream(elemento);
        Habitacion hb;
        hb.cargar(stream);
        ls.agregarAtras(hb);
        i++;
    }

    return is;
}

istream& Hotel::tomarIngresos (istream& is, Lista<pair<CheckIn,Habitacion> > & ingresos) const
{
    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
        //cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        pair<CheckIn,Habitacion> ing;
        tomarIngreso(stream, ing);
        ingresos.agregarAtras(ing);
        i++;
    }

    return is;
}

istream& Hotel::tomarIngreso (istream& is, pair<CheckIn,Habitacion> & ingreso) const
{
    string first,second;
    parsearTupla(is,first,second);

    stringstream streamFirst(first);
    stringstream streamSecond(second);
    tomarCheckIn(streamFirst, ingreso.first);
    int nroHabitacion;
    streamSecond >> nroHabitacion;
    if(!hallarHabitacionPorNumero(nroHabitacion, ingreso.second)){
        cerr << "Error en funcion 'Hotel::hallarHabitacionPorNumero(int numero)': habitación no encontrada." << endl;
    }

    return is;
}

bool Hotel::hallarHabitacionPorNumero(int numero, Habitacion &target) const
{
    int j = 0;
    bool flag = false;
    while( (j < this->_habitaciones.longitud()) && (!flag))
    {
        Habitacion hb = this->_habitaciones.iesimo(j);
        if( hb.numero() == numero )
        {
            target = hb;
            flag=true;
        }
        j++;
    }
    return flag;
}

istream& Hotel::tomarCheckIn (istream& is, CheckIn & checkIn) const
{
    string first, second;
    parsearTupla(is,first,second);

    stringstream streamFirst(first);
    stringstream streamSecond(second);
    streamFirst >> checkIn.first;
    streamSecond >> checkIn.second;

    return is;
}

istream& Hotel::tomarCheckOut (istream& is, CheckOut & checkOut) const
{
    string first, second;
    parsearTupla(is,first,second);

    stringstream streamFirst(first);
    stringstream streamSecond(second);
    streamFirst >> checkOut.first;
    streamSecond >> checkOut.second;

    return is;
}

istream& Hotel::tomarSalidas (istream& is, Lista<CheckOut> & salidas) const
{
    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
//        cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        CheckOut co;
        tomarCheckOut(stream, co);
        salidas.agregarAtras(co);
        i++;
    }

    return is;
}

istream& Hotel::tomarReservas (istream& is, Lista<Reserva> & reservas) const
{
    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
//        cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        Reserva r;
        r.cargar(stream);
        reservas.agregarAtras(r);
        i++;
    }

    return is;
}

istream& Hotel::tomarTarifas (istream& is, Lista<pair<TipoHabitacion, Dinero> > & tarifas) const
{
    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
//        cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        pair<TipoHabitacion, Dinero> thd;
        tomarTarifa(stream, thd);
        tarifas.agregarAtras(thd);
        i++;
    }

    return is;
}

istream& Hotel::tomarTarifa (istream& is, pair<TipoHabitacion, Dinero> & thd) const
{
    string first, second;
    parsearTupla(is,first,second);

    stringstream streamFirst(first);
    stringstream streamSecond(second);
    tomarTipoHabitacion ( streamFirst, thd.first);
    streamSecond >> thd.second;
    return is;
}

istream& Hotel::tomarPrecioAccesorios (istream& is, Lista<pair<Accesorio, Dinero> > & precios) const
{
    Lista<string> elementos = parsearLista(is);

    int i = 0;
    while( i < elementos.longitud() )
    {
        string elemento = elementos.iesimo(i);
//        cout << elemento << endl;
        elemento = elemento.substr(1,elemento.size()-2);
        stringstream stream(elemento);
        pair<Accesorio, Dinero> accd;
        tomarPrecioAccesorio(stream, accd);
        precios.agregarAtras(accd);
        i++;
    }

    return is;
}

istream& Hotel::tomarPrecioAccesorio (istream& is, pair<Accesorio, Dinero> & precio) const
{
    string first, second;
    parsearTupla(is,first,second);

    stringstream streamFirst(first);
    stringstream streamSecond(second);
    tomarAccesorio( streamFirst, precio.first);
    streamSecond >> precio.second;
    return is;
}
