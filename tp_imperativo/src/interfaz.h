#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "Test.h"


void MenuPrincipal();
void MenuReserva();
Reserva MenuCrearReserva();
void MenuHabitacion();
Habitacion MenuCrearHabitacion();
void MenuHotel();
Hotel MenuCrearHotel();
void MenuMinisterio();
Ministerio MenuCrearMinisterio();

//AUX
int LeerOpcion(int maxOpcion);
void Pausar();
void Salir();
void LimpiarPantalla();
void AbrirArchivoParaLeer(ifstream &archivo);
void AbrirArchivoParaEscribir(ofstream &archivo);
void MostrarHoteles(const Lista<Hotel>& hoteles, string titulo);
void MostrarTiposDeHabitaciones();
void MostrarTiposDeAccesorios();
void MostrarListaDeAccesorios(const Lista<Accesorio> lista);

void MostrarHuespedesDeHotel(Hotel hotel);
void MostrarIngresosDeHotel(Hotel hotel);
void MostrarEgresosDeHotel(Hotel hotel);
void MostrarHuespedesDeHotel(Hotel hotel);
void MostrarHabitacionesDeHotel(Hotel hotel);
string accesorio2String(Accesorio s);


#endif // INTERFAZ_H
