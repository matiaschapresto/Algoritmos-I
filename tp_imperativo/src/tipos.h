#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#include <string>
#include <iostream>

using namespace std;

typedef int Fecha;
typedef int DNI;
typedef int Dinero;
typedef string Cadena;
typedef string Nombre;
typedef string Provincia;
typedef pair<DNI, Fecha> CheckIn;
typedef pair<DNI, Fecha> CheckOut;
enum TipoHabitacion{Simple, Doble, Triple, Cuadruple};
enum Accesorio{Jacuzzi, LCD, PS3, DVD, Pelotero, Inflable};

#endif // TIPOS_H_INCLUDED
