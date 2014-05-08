#include<algorithm>
#include<iostream>
#include<vector>
#include <sstream>

#include "reserva.h"
#include "habitacion.h"
#include "hotel.h"
#include "ministerio.h"

#define ASSERT(x, msg) \
    if (! (x)) \
    { \
        cout << "ERROR!! Assert " << #x << " failed\n"; \
        cout << " on line " << __LINE__  << "\n"; \
        cout << " in file " << __FILE__ << "\n";  \
        cout << " msg: " << msg << "\n"; \
        fallo = true; \
    }

using namespace std;

// TODO: agregar test de ==

template<class T>
bool mismaLista(Lista<T> l1, Lista<T> l2)
{
    if(l1.longitud()!=l2.longitud())
        return false;
    vector<T> vec1, vec2;
    for(int i=0;i<l1.longitud();i++)
    {
        vec1.push_back(l1.iesimo(i));
        vec2.push_back(l2.iesimo(i));
    }
    for(unsigned i=0;i<vec1.size();i++)
    if(count(vec1.begin(),vec1.end(),vec1[i])!=count(vec2.begin(),vec2.end(),vec1[i]))
        return false;
    return true;
}

bool fallo;
Reserva r1,r2,r3,r4,r5,r6,r7,r8,r9,r10, r11;
DNI d1,d2,d3,d4,d5,d6,d7,d8,d9,d10, d11;
Fecha desde1,desde2,desde3,desde4,desde5,desde6,desde7,desde8,desde9,desde10,desde11;
Fecha hasta1,hasta2,hasta3,hasta4,hasta5,hasta6,hasta7,hasta8,hasta9,hasta10,hasta11;
TipoHabitacion tipo1,tipo2,tipo3,tipo4,tipo5,tipo6,tipo7,tipo8,tipo9,tipo10,tipo11;

void TestReserva()
{

    ASSERT(r1.documento() == d1, "El documento de la reserva 1 es incorrecto" )
    ASSERT(r1.fechaDesde() == desde1, "La fechaDesde de la reserva 1 es incorrecta" )
    ASSERT(r1.fechaHasta() == hasta1, "La fechaHasta de la reserva 1 es incorrecta")
    ASSERT(r1.tipo() == tipo1, "El tipo de habitacion de la reserva 1 es incorrecto")
    ASSERT(r1.confirmada() == false, "La reserva 1 esta confirmada pero no deberia estarlo")

    ASSERT(r2.documento() == d2, "El documento de la reserva 2 es incorrecto" )
    ASSERT(r2.fechaDesde() == desde2, "La fechaDesde de la reserva 2 es incorrecta" )
    ASSERT(r2.fechaHasta() == hasta2, "La fechaHasta de la reserva 2 es incorrecta")
    ASSERT(r2.tipo() == tipo2, "El tipo de habitacion de la reserva 2 es incorrecto")
    ASSERT(r2.confirmada() == true, "La reserva 2 no esta confirmada y deberia estarlo")

    ASSERT(r3.documento() == d3, "El documento de la reserva 3 es incorrecto" )
    ASSERT(r3.fechaDesde() == desde3, "La fechaDesde de la reserva 3 es incorrecta" )
    ASSERT(r3.fechaHasta() == hasta3, "La fechaHasta de la reserva 3 es incorrecta")
    ASSERT(r3.tipo() == tipo3, "El tipo de habitacion de la reserva 3 es incorrecto")
    ASSERT(r3.confirmada() == false, "La reserva 3 esta confirmada pero no deberia estarlo")

}

void iniciarDatosReserva() {

    d1 = 33444555;
    desde1 = 1;
    hasta1 = 2;
    tipo1 = Simple;
    r1 = Reserva(d1,desde1,hasta1,tipo1);

    d2 = 33444555;
    desde2 = 1;
    hasta2 = 2;
    tipo2 = Simple;
    r2 = Reserva(d2,desde2,hasta2,tipo2);
    r2.confirmar();

    d3 = 33444555;
    desde3 = 3;
    hasta3 = 5;
    tipo3 = Doble;
    r3 = Reserva(d3,desde3,hasta3,tipo3);

    d4 = 33444555;
    desde4 = 3;
    hasta4 = 5;
    tipo4 = Doble;
    r4 = Reserva(d4,desde4,hasta4,tipo4);
    r4.confirmar();

    d5 = 37654321;
    desde5 = 4;
    hasta5 = 7;
    tipo5 = Doble;
    r5 = Reserva(d5,desde5,hasta5,tipo5);

    d6 = 37654321;
    desde6 = 4;
    hasta6 = 7;
    tipo6 = Doble;
    r6 = Reserva(d6,desde6,hasta6,tipo6);
    r6.confirmar();

    d7 = 30100200;
    desde7 = 6;
    hasta7 = 9;
    tipo7 = Doble;
    r7 = Reserva(d7,desde7,hasta7,tipo7);

    d8 = 30100200;
    desde8 = 6;
    hasta8 = 9;
    tipo8 = Doble;
    r8 = Reserva(d8,desde8,hasta8,tipo8);
    r8.confirmar();

    d9 = 30100201;
    desde9 = 6;
    hasta9 = 9;
    tipo9 = Doble;
    r9 = Reserva(d9,desde9,hasta9,tipo9);

    d10 = 30100200;
    desde10 = 7;
    hasta10 = 8;
    tipo10 = Doble;
    r10 = Reserva(d10,desde10,hasta10,tipo10);

    d11 = 37654321;
    desde11 = 6;
    hasta11 = 11;
    tipo11 = Doble;
    r11 = Reserva(d11,desde11,hasta11,tipo11);
}

Lista<Accesorio> listaA1, listaA2, listaA3, listaA4, listaA5;

void TestListaAccesorios()
{
    ASSERT(listaA1.iesimo(0)==Pelotero, "El 0-esimo elemento de la lista 1 debe ser Pelotero")
    ASSERT(listaA1.cabeza()==Pelotero, "El 0-esimo elemento de la lista 1 debe ser Pelotero")
    ASSERT(listaA1.longitud()==1, "La lista 1 debe tener 1 elemento")
    // TODO: cambiar el orden de las listas deben estar ordenadas en orden creciente
    ASSERT(listaA2.iesimo(0)==Inflable, "El 0-esimo elemento de la lista 2 debe ser Inflable")
    ASSERT(listaA2.iesimo(1)==Pelotero, "El 0-esimo elemento de la lista 2 debe ser Pelotero" )
    ASSERT(listaA2.iesimo(2)==DVD, "El 0-esimo elemento de la lista 2 debe ser DVD")
    ASSERT(listaA2.iesimo(3)==PS3, "El 0-esimo elemento de la lista 2 debe ser PS3")
    ASSERT(listaA2.iesimo(4)==LCD, "El 0-esimo elemento de la lista 2 debe ser LCD")
    ASSERT(listaA2.iesimo(5)==Jacuzzi, "El 0-esimo elemento de la lista 2 debe ser Jacuzzi")
    ASSERT(listaA2.longitud()==6, "La lista 2 debe tener 6 elementos")
    // TODO: cambiar el orden de las listas deben estar ordenadas en orden creciente
    ASSERT(listaA5.iesimo(0)==PS3, "El 0-esimo elemento de la lista 5 debe ser PS3")
    ASSERT(listaA5.iesimo(1)==LCD, "El 0-esimo elemento de la lista 5 debe ser LCD" )
    ASSERT(listaA5.iesimo(2)==Jacuzzi, "El 0-esimo elemento de la lista 5 debe ser Jacuzzi")
    ASSERT(listaA5.longitud()==3, "La lista 5 debe tener 3 elementos")
}

void iniciarDatosListaAccesorios() {
    listaA1 = Lista<Accesorio>();
    listaA1.agregar(Pelotero);

    listaA2 = Lista<Accesorio>();
    listaA2.agregar(Jacuzzi);
    listaA2.agregar(LCD);
    listaA2.agregar(PS3);
    listaA2.agregar(DVD);
    listaA2.agregar(Pelotero);
    listaA2.agregar(Inflable);

    listaA3 = Lista<Accesorio>();
    listaA3.agregar(Jacuzzi);
    listaA3.agregar(Pelotero);

    listaA4 = Lista<Accesorio>();

    listaA5 = Lista<Accesorio>();
    listaA5.agregarAtras(PS3);
    listaA5.agregarAtras(LCD);
    listaA5.agregarAtras(Jacuzzi);

}

Habitacion h1,h2,h3,h4,h5,h6,h7;

void TestHabitacion()
{

    ASSERT(h1.numero()==1, "La habitacion h1 debe ser la numero 1")
    ASSERT(h1.tipo()==Simple, "La habitacion h1 debe ser Simple")
    ASSERT(h1.accesorios().longitud()==0, "La habitacion h1 no debe tener accesorios")

    ASSERT(h2.numero()==2, "La habitacion h2 debe ser la numero 2")
    ASSERT(h2.tipo()==Doble, "La habitacion h2 debe ser Doble")
    ASSERT(h2.accesorios().longitud()==0, "La habitacion h2 no debe tener accesorios")

    ASSERT(h3.tipo()==Triple, "La habitacion h3 debe ser Triple")

    ASSERT(h4.tipo()==Cuadruple, "La habitacion h4 debe ser Doble")

    ASSERT(h5.accesorios() == listaA5, "La habitacion h5 debe tener PS3, LCD y Jacuzzi")

    ASSERT(h6.accesorios() == listaA1, "La habitacion h6 debe tener unicamente Pelotero")

    ASSERT(h7.accesorios() == listaA2, "La habitacion h7 debe tener Inflable, Pelotero, DVD, PS3, LCD y Jacuzzi")

}

void iniciarDatosHabitacion() {
    h1 = Habitacion(1,Simple,listaA4);
    h2 = Habitacion(2,Doble,listaA4);
    h3 = Habitacion(3,Triple,listaA4);
    h4 = Habitacion(4,Cuadruple,listaA4);
    h5 = Habitacion(5,Doble,listaA5);
    h6 = Habitacion(6,Triple,listaA1);
    h7 = Habitacion(7,Cuadruple,listaA2);
}

Lista<Habitacion> listaH1;

void TestPretensionesDePopStar()
{

    Lista<Habitacion> PPS1 = Lista<Habitacion>();
    PPS1.agregar(h6);
    ASSERT(mismaLista(pretensionesDePopStar(listaA1,listaH1),PPS1), "El test Pretensiones de PopStar 1 debe dar unicamente la habitacion h6")


    Lista<Habitacion> PPS2 = Lista<Habitacion>();
    PPS2.agregar(h5);
    ASSERT(mismaLista(pretensionesDePopStar(listaA2,listaH1),PPS2), "El test Pretensiones de PopStar 2 debe dar unicamente la habitacion h5")

    Lista<Habitacion> PPS3 = Lista<Habitacion>();
    PPS3.agregar(h5);
    PPS3.agregar(h6);
    ASSERT(mismaLista(pretensionesDePopStar(listaA3,listaH1),PPS3), "El test Pretensiones de PopStar 3 debe dar las habitaciones h5 y h6")


    Lista<Habitacion> PPS4 = Lista<Habitacion>();
    PPS4.agregar(h1);
    PPS4.agregar(h2);
    PPS4.agregar(h3);
    PPS4.agregar(h4);
    PPS4.agregar(h5);
    PPS4.agregar(h6);
    ASSERT(mismaLista(pretensionesDePopStar(listaA4,listaH1),PPS4), "El test Pretensiones de PopStar 4 debe dar las habitaciones h1, h2, h3, h4, h5 y h6")

}

void iniciarDatosListaHabitaciones(){
    listaH1 = Lista<Habitacion>();
    listaH1.agregar(h1);
    listaH1.agregar(h2);
    listaH1.agregar(h3);
    listaH1.agregar(h4);
    listaH1.agregar(h5);
    listaH1.agregar(h6);
}

Hotel ht0,ht1,ht2,ht3,ht4,ht5,ht6,ht7,ht8,ht9,ht10, ht11;
Lista<Habitacion> listaHab1;
Lista<pair<TipoHabitacion,Dinero> > listaTarifaHab1;
Lista<pair<Accesorio,Dinero> > listaPrecio1;
Lista<DNI> huespedes1,huespedes2,huespedes3;
Lista<pair<CheckIn,Habitacion> > listaIngresos1,listaIngresos2,listaIngresos3;
Lista<CheckOut> listaSalidas1,listaSalidas2,listaSalidas3;
Lista<Reserva> listaReservas1,listaReservas2,listaReservas3;
void TestHotel()
{
    ASSERT(ht0.nombre()=="Hotel1", "El nombre del hotel ht0 debe ser Hotel1")
    ASSERT(ht0.cadena()=="CheRaton", "La cadena del hotel ht0 debe ser CheRaton")
    ASSERT(ht0.huespedes().longitud() == 0, "El hotel ht0 no debe tener huespedes")
    ASSERT(mismaLista(ht0.habitaciones(),listaHab1), "Las habitaciones del hotel ht0 deben ser h1, h2 y h5")
    ASSERT(ht0.ingresos().longitud() == 0, "El hotel ht0 no debe tener ingresos")
    ASSERT(ht0.salidas().longitud() == 0, "El hotel ht0 no debe tener salidas")
    ASSERT(ht0.reservas().longitud() == 0, "El hotel ht0 no debe tener reservas")
    ASSERT(ht0.tarifaXDia(Triple)==3, "En el hotel ht0 la habitacion triple debe salir 3")
    ASSERT(ht0.precioAccesorio(Jacuzzi)==10, "En el hotel ht0 el Jacuzzi debe salir 10")

    ht1 = ht0;
    ht1.hacerReserva(r2);
    ht1.hacerReserva(r3);
    ht1.hacerReserva(r5);
    ht1.hacerReserva(r7);
    listaReservas1.agregar(r2);
    listaReservas1.agregar(r3);
    listaReservas1.agregar(r5);
    listaReservas1.agregar(r7);
    ASSERT(ht1.huespedes().longitud() == 0, "El hotel ht1 no debe tener huespedes")
    ASSERT(mismaLista(ht1.ingresos(),listaIngresos1), "El hotel ht1 no debe tener ingresos")
    ASSERT(ht1.ingresos().longitud() == 0, "El hotel ht1 no debe tener ingresos")
    ASSERT(ht1.salidas().longitud() == 0, "El hotel ht1 no debe tener salidas")
    ASSERT(mismaLista(ht1.reservas(),listaReservas1), "El hotel ht1 debe tener las reservas r2, r3, r5 y r7")


    ht2 = ht1;
    ht2.registrarHuesped(33444555,3,h5);
    ht2.registrarHuesped(37654321,4,h2);
    ht2.desRegistrarHuesped(33444555,5);
    ht2.registrarHuesped(30100200,6,h5);
    huespedes2 = Lista<DNI>();
    huespedes2.agregar(37654321);
    huespedes2.agregar(30100200);
    listaIngresos2 = Lista<pair<CheckIn,Habitacion> >();
    listaIngresos2.agregar(make_pair(make_pair(33444555,3),h5));
    listaIngresos2.agregar(make_pair(make_pair(37654321,4),h2));
    listaIngresos2.agregar(make_pair(make_pair(30100200,6),h5));
    listaSalidas2 = Lista<CheckOut>();
    listaSalidas2.agregar(make_pair(33444555,5));
    listaReservas2 = Lista<Reserva>();
    listaReservas2.agregar(r2);
    listaReservas2.agregar(r4);
    listaReservas2.agregar(r6);
    listaReservas2.agregar(r8);
    ASSERT(mismaLista(ht2.huespedes(),huespedes2), "El hotel ht2 debe tener los huespedes 37654321 y 30100200")
    ASSERT(mismaLista(ht2.ingresos(),listaIngresos2), "El hotel ht2 debe tener los ingresos ((33444555,3),h5), ((37654321,4),h2) y ((30100200,6),h5)")
    ASSERT(mismaLista(ht2.salidas(),listaSalidas2), "El hotel ht2 debe tener la salida (33444555,5)")
    ASSERT(mismaLista(ht2.reservas(),listaReservas2), "El hotel ht2 debe tener las reservas r2, r4, r6 y r8")

    ht3 = ht2;
    ht3.desRegistrarHuesped(30100200,7);
    huespedes3 = Lista<DNI>();
    huespedes3.agregar(37654321);
    listaIngresos3 = listaIngresos2;
    listaSalidas3 = listaSalidas2;
    listaSalidas3.agregar(make_pair(30100200,7));
    listaReservas3 = listaReservas2;
    ASSERT(mismaLista(ht3.huespedes(),huespedes3), "El hotel ht3 debe tener el huesped 37654321")
    ASSERT(mismaLista(ht3.ingresos(),listaIngresos3), "El hotel ht2 debe tener los ingresos ((33444555,3),h5), ((37654321,4),h2) y ((30100200,6),h5)")
    ASSERT(mismaLista(ht3.salidas(),listaSalidas3), "El hotel ht3 debe tener las salidas (33444555,5) y (30100200,7)")
    ASSERT(mismaLista(ht3.reservas(),listaReservas3), "El hotel ht3 debe tener las reservas r2, r4, r6 y r8")


    ht4 = ht1;
    ht4.vender("FourScissors");

    /**Test Vender**/
    ASSERT(ht4.cadena()=="FourScissors", "La cadena del hotel ht4 debe ser FourScissors" )
    ASSERT(mismaLista(ht4.huespedes(), ht1.huespedes()), "Se mantienen los huepedes")
    ASSERT(mismaLista(ht4.habitaciones(), ht1.habitaciones()), "Se mantienen las habitaciones")
    ASSERT(mismaLista(ht4.ingresos(), ht1.ingresos()), "Se mantienen los ingresos")
    ASSERT(mismaLista(ht4.salidas(), ht1.salidas()), "Se mantienen las salidas")
    ASSERT(mismaLista(ht4.reservas(), ht1.reservas()), "Se mantienen las reservas")
    /**Fin Test Vender**/

    ht5 = ht1;
    ht5.hacerReserva(r9);

    /**Test Sobrereservado**/
    ASSERT(ht5.sobreReservado(5)==false, "En el dia 5 el hotel ht5 no debe estar sobrereservado" )
    ASSERT(ht5.sobreReservado(6)==true, "En el dia 6 el hotel ht5 debe estar sobrereservado" )
    /**Fin Test Sobrereservado**/


     /**Test Huespedes con Palabra **/
    Lista<DNI> conPalabra = Lista<DNI>();
     conPalabra.agregar(33444555);
     ASSERT(mismaLista(ht3.huespedesConPalabra(),conPalabra), "El unico huesped con palabra del hotel ht3 es 33444555" )
     ht11 = ht0;
     ht11.hacerReserva(r5);
     ht11.hacerReserva(r11);
     ht11.registrarHuesped(d11, 4, h5);
     ht11.desRegistrarHuesped(d11,5);
     ht11.registrarHuesped(d11, 6, h5);
     ht11.desRegistrarHuesped(d11,7);
     ASSERT(ht11.huespedesConPalabra().longitud() == 0, "No hay ningun huesped con palabra en ht11" )
     /**Fin Test Huespedes con Palabra**/
    /**Test Calcular Cuenta**/
    ASSERT(ht2.calcularCuenta(make_pair(33444555,3),make_pair(33444555,5),h5)==74, "La cuenta debe dar 74" )
    /**Fin Test Calcular Cuenta**/


    ht6 = ht1;
    ht6.hacerReserva(r10);

    /**Test Reservas Solapadas**/
    ASSERT(ht6.reservasSolapadas(33444555)==false, "El huesped 33444555 no debe tener reservas solapadas" )
    ASSERT(ht6.reservasSolapadas(30100200)==true, "El huesped 30100200 debe tener reservas solapadas" )
    /**Fin Test Reservas Solapadas**/
}

void iniciarDatosHoteles() {

    listaHab1 = Lista<Habitacion>();
    listaHab1.agregar(h1);
    listaHab1.agregar(h2);
    listaHab1.agregar(h5);
    listaTarifaHab1 = Lista<pair<TipoHabitacion,Dinero> >();
    listaTarifaHab1.agregar(make_pair(Simple,1));
    listaTarifaHab1.agregar(make_pair(Doble,2));
    listaTarifaHab1.agregar(make_pair(Triple,3));
    listaTarifaHab1.agregar(make_pair(Cuadruple,4));
    listaPrecio1 = Lista<pair<Accesorio,Dinero> >();
    listaPrecio1.agregar(make_pair(Jacuzzi,10));
    listaPrecio1.agregar(make_pair(LCD,20));
    listaPrecio1.agregar(make_pair(PS3,40));
    huespedes1 = Lista<DNI>();
    listaIngresos1 = Lista<pair<CheckIn,Habitacion> >();
    listaSalidas1 = Lista<CheckOut>();
    listaReservas1 = Lista<Reserva>();
    ht0 = Hotel("Hotel1","CheRaton",listaHab1,listaTarifaHab1,listaPrecio1);

}

Lista<Habitacion> listaHab10;

void TestMinisterio()
{
    Lista<Provincia> listaProv = Lista<Provincia>();
    listaProv.agregar("TheShire");
    listaProv.agregar("Mordor");
    Ministerio m1, m2, m3, m4, m5, m6, m7;
    m1 = Ministerio(listaProv);
    m2 = m1;
    m2.agregarHotel(ht7,"TheShire");
    // M2: (("Hotel1","CheRaton"), "TheShire)
    m3 = m2;
    m3.agregarHotel(ht8,"Mordor");
    // M3: (("Hotel1","CheRaton"), "TheShire) ( ("Hotel2","FourScissors"),"Mordor")
    m4 = m2;
    m4.agregarHotel(ht9,"Mordor");
    // M4(("Hotel1","CheRaton"), "TheShire) (("Hotel2","CheRaton"),"Mordor")
    m5 = m3;
    m5.agregarHotel(ht10,"Mordor");
    // M5: (("Hotel1","CheRaton"), "TheShire) ( ("Hotel2","FourScissors"),"Mordor") ( ("Hotel3","CheRaton"),"Mordor")


    ASSERT(mismaLista(m5.secretarias(),listaProv), "Mismas provincias al construir un ministerio" )
    ASSERT(m1.cadenasDeHoteles().longitud()==0, "Cadenas de hoteles deben estar vacias" )
    ASSERT(m1.registro("TheShire").longitud()==0, "No debe haber ningun hotel")
    ASSERT(m1.registro("Mordor").longitud()==0, "No debe haber ningun hotel")

    /** Test Cadenas de Hoteles **/
    ASSERT(m2.cadenasDeHoteles().longitud()==1, "hay una unica cadena de hoteles en M2" )
    ASSERT(m2.cadenasDeHoteles().iesimo(0).longitud()==1, "la cadena de M2 tiene un unico hotel" )
    ASSERT(m2.cadenasDeHoteles().iesimo(0).iesimo(0)==ht7, "la cadena tiene un unico hotel" )

    ASSERT(m3.cadenasDeHoteles().longitud()==2, "hay dos cadenas de hoteles en M3" )
    ASSERT(m3.cadenasDeHoteles().iesimo(0).longitud()==1, "la cadena 1 de M3 tiene un unico hotel" )
    ASSERT(m3.cadenasDeHoteles().iesimo(1).longitud()==1, "la cadena 2 de M3 tiene un unico hotel" )

    ASSERT(m4.cadenasDeHoteles().longitud()==1, "hay una unica cadena de hoteles en M4" )
    ASSERT(m4.cadenasDeHoteles().iesimo(0).longitud()==2, "la cadena de M4 tiene dos hoteles" )
    ASSERT(m4.cadenasDeHoteles().iesimo(0).iesimo(0).cadena()=="CheRaton", "la cadena tiene un unico hotel" )
    ASSERT(m4.cadenasDeHoteles().iesimo(0).iesimo(1).cadena()=="CheRaton", "la cadena tiene un unico hotel" )
    /**Fin Cadenas de Hoteles**/

    /**Test Cadenas Amarretas**/
    ASSERT(m1.cadenasAmarretas().longitud() == 0, "M1 no tiene cadenas amarretas" )
    ASSERT(m2.cadenasAmarretas().longitud() == 1 && m2.cadenasAmarretas().iesimo(0) == "CheRaton", "La unica cadena amarreta de M2 es CheRaton")
    ASSERT(m4.cadenasAmarretas().longitud() == 1 && m4.cadenasAmarretas().iesimo(0) == "CheRaton", "La unica cadena amarreta de M4 es CheRaton")
    ASSERT(m5.cadenasAmarretas().longitud() == 1 && m5.cadenasAmarretas().iesimo(0) == "FourScissors", "La unica cadena amarreta de M5 es FourScissors" )
    Lista<Cadena> amarretas = Lista<Cadena>();
    amarretas.agregar("FourScissors");
    amarretas.agregar("CheRaton");
    ASSERT(mismaLista(m3.cadenasAmarretas(), amarretas), "FourScissors y CheRaton son cadenas amarretas de m3" )
    /**Fin Test Cadenas Amarretas**/

    /**FusionAutorizada**/
    m6 = m5;
    ASSERT(m6 == m5, "En este momento los ministerios M5 y M6 son iguales" )
    m6.fusionAutorizada("CheRaton", "FourScissors");
    ASSERT((m6 == m5) == false, "En este momento los ministerios M5 y M6 son distintos" )
    ASSERT(mismaLista(m6.secretarias(),listaProv), "se mantienen las provincias al fusionar")
    ASSERT(m6.cadenasDeHoteles().longitud() == 1, "Al fusionar queda una sola cadena")
    ASSERT(m6.cadenasDeHoteles().iesimo(0).longitud() == 3, "Queda una unica cadena de tres hoteles")
    ASSERT(m6.cadenasDeHoteles().iesimo(0).iesimo(0).cadena() ==  "CheRaton", "Los tres hoteles tienen cadena CheRaton")
    ASSERT(m6.cadenasDeHoteles().iesimo(0).iesimo(1).cadena() ==  "CheRaton", "Los tres hoteles tienen cadena CheRaton")
    ASSERT(m6.cadenasDeHoteles().iesimo(0).iesimo(2).cadena() ==  "CheRaton", "Los tres hoteles tienen cadena CheRaton")

    m7 = m5;
    ASSERT(m7 == m5, "En este momento los ministerios M5 y M7 son iguales" )
    m7.fusionAutorizada("FourScissors", "CheRaton");
    ASSERT((m7 == m5) == false, "En este momento los ministerios M5 y M7 son distintos" )
    ASSERT(mismaLista(m7.secretarias(),listaProv), "se mantienen las provincias al fusionar")
    ASSERT(m7.cadenasDeHoteles().longitud() == 1, "Al fusionar queda una sola cadena")
    ASSERT(m7.cadenasDeHoteles().iesimo(0).longitud() == 3, "Queda una unica cadena de tres hoteles")
    ASSERT(m7.cadenasDeHoteles().iesimo(0).iesimo(0).cadena() ==  "FourScissors", "Los tres hoteles tienen cadena FourScissors")
    ASSERT(m7.cadenasDeHoteles().iesimo(0).iesimo(1).cadena() ==  "FourScissors", "Los tres hoteles tienen cadena FourScissors")
    ASSERT(m7.cadenasDeHoteles().iesimo(0).iesimo(2).cadena() ==  "FourScissors", "Los tres hoteles tienen cadena FourScissors")
    /**Fin Test Fusion Autorizada**/

    /** Inicio TEST IO Ministerio**/
    //Declaraciones auxiliares
        ostringstream assertM1;
        ostringstream assertM2;
        istringstream isM;
        assertM1.clear();
        assertM2.clear();
        isM.clear();
    //guardo el ministerio del test en assertM1
        m7.guardar(assertM1);
    //cargo isM con los datos de osM
        isM.str(assertM1.str());
    //declaro un ministerio nuevo
        Ministerio ministerioDeMagia;
    //cargo los datos de is =>>>>>>>>>>>>>>>>>>>>>> En este punto deberia valer m7 == ministerioDeMagia
        ministerioDeMagia.cargar(isM);
        ministerioDeMagia.guardar(assertM2);
    //guardo ministerioDeMagia en assertM2
    //Luego, como vale m7 == ministerioDeMagia => las strings deben ser iguales.
    ASSERT((assertM1.str() == assertM2.str()) == true , "Test IO Ministerio(incluye las IO's de hotel, reserva y habitacion)")
    /** Fin TEST IO Ministerio**/

}


void iniciarDatosMinisterio() {

    ht7 = Hotel("Hotel1","CheRaton",Lista<Habitacion>(),Lista<pair<TipoHabitacion,Dinero> >(),Lista<pair<Accesorio,Dinero> >());
    ht8 = Hotel("Hotel2","FourScissors",Lista<Habitacion>(),Lista<pair<TipoHabitacion,Dinero> >(),Lista<pair<Accesorio,Dinero> >());
    ht9 = Hotel("Hotel2","CheRaton",Lista<Habitacion>(),Lista<pair<TipoHabitacion,Dinero> >(),Lista<pair<Accesorio,Dinero> >());
    listaHab10 = Lista<Habitacion>();
    listaHab10.agregar(h5);
    listaHab10.agregar(h7);
    Lista<pair<TipoHabitacion,Dinero> > listaTarifaHab10 = Lista<pair<TipoHabitacion,Dinero> >();
    listaTarifaHab10.agregar(make_pair(Simple,1));
    listaTarifaHab10.agregar(make_pair(Doble,2));
    listaTarifaHab10.agregar(make_pair(Triple,3));
    listaTarifaHab10.agregar(make_pair(Cuadruple,4));
    Lista<pair<Accesorio,Dinero> > listaPrecio10 = Lista<pair<Accesorio,Dinero> >();
    listaPrecio10.agregar(make_pair(Jacuzzi,10));
    listaPrecio10.agregar(make_pair(LCD,20));
    listaPrecio10.agregar(make_pair(PS3,40));
    ht10 = Hotel("Hotel3","CheRaton",listaHab10,listaTarifaHab10,listaPrecio10);
}

int correrTests()
{
    fallo = false;
    iniciarDatosReserva() ;
    iniciarDatosListaAccesorios();
    iniciarDatosHabitacion();
    iniciarDatosListaHabitaciones();
    iniciarDatosHoteles();
    iniciarDatosMinisterio();
    TestReserva();
    TestListaAccesorios();
    TestHabitacion();
    TestPretensionesDePopStar();
    TestHotel();
    TestMinisterio();
    if(fallo)
    {
        cout << "Hay errores en los tests (corregilos antes de la entrega)" << endl;
    } else {
        cout << "Los tests han finalizado correctamente. Vamo'!!!!" << endl;
    }

    return fallo;
}
