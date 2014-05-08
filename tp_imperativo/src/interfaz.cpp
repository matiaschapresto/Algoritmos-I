#include "interfaz.h"
#include <iostream>
#include <string>

using namespace std;

Reserva reserva;
Habitacion habitacion;
Hotel hotel;
Ministerio ministerio;

bool reservaCreada = false;
bool habitacionCreada = false;
bool hotelCreado = false;
bool ministerioCreado = false;

void MenuPrincipal()
{
    cout.setf(ios::boolalpha);

    bool exit = false;

    while(!exit)
    {
        cout << endl
            << "Hotels" << endl
            << "0. Reserva" << endl
            << "1. Habitacion" << endl
            << "2. Hotel" << endl
            << "3. Ministerio" << endl
            << "4. Tests" << endl;
        int opt=LeerOpcion(4);

        switch(opt){
            case 0:
                LimpiarPantalla();
                MenuReserva();
                break;
            case 1:
                LimpiarPantalla();
                MenuHabitacion();
                break;
            case 2:
                LimpiarPantalla();
                MenuHotel();
                break;
            case 3:
                LimpiarPantalla();
                MenuMinisterio();
                break;
            case 4:
                LimpiarPantalla();
                correrTests();
                break;
        }
    }
}

void MenuReserva()
{
    int maximaOpcion = 2;

    cout << endl
            << "Menu Reserva" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear reserva" << endl
            << "2. Cargar Reserva" << endl;
    if (reservaCreada)
    {
        maximaOpcion = 10;
        cout << "3. Guardar reserva" << endl
        << "4. Mostrar reserva" << endl
        << "5. DNI" << endl
        << "6. Fecha Desde" << endl
        << "7. Fecha Hasta" << endl
        << "8. Tipo Habitacion" << endl
        << "9. Confirmada" << endl
        << "10. Confirmar" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            reserva = MenuCrearReserva();
            reservaCreada = true;
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            reserva.cargar(archivoEntrada);
            archivoEntrada.close();
            reservaCreada = true;
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 3:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            reserva.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            reserva.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 5:
        {
            LimpiarPantalla();
            cout << "El DNI es: " << reserva.documento() << endl;
            Pausar();
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 6:
        {
            LimpiarPantalla();
            cout << "La Fecha Desde es: " << reserva.fechaDesde() << endl;
            Pausar();
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 7:
        {
            LimpiarPantalla();
            cout << "La Fecha Hasta es: " << reserva.fechaHasta() << endl;
            Pausar();
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 8:
        {
            LimpiarPantalla();
            cout << "El tipo de habitacion es: " << reserva.tipo() << endl;
            Pausar();
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 9:
        {
            LimpiarPantalla();
            cout << "El estado de la reserva es: " << (reserva.confirmada()? "Confirmada" : "No confirmada") << endl;
            Pausar();
            LimpiarPantalla();
            MenuReserva();
            break;
        }
        case 10:
        {
            LimpiarPantalla();
            cout << "Confirmando reserva" << endl;
            reserva.confirmar();
            Pausar();
            LimpiarPantalla();
            MenuReserva();
            break;
        }
    }
}

Reserva MenuCrearReserva()
{
    cout << "Creando una reserva. Como desea crearla?" << endl
        << "0. Crear por consola" << endl
        << "1. Cargar de archivo" << endl;

    int opt = LeerOpcion(1);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            int nuevoDNI = 0;
            int nuevofechaDesde = 0;
            int nuevofechaHasta = 0;
            int nuevotipoHabitacion = 0;

            MostrarTiposDeHabitaciones();

            cout << "Ingrese DNI, Fecha Desde, Fecha Hasta y TipoHabitacion entre espacios: " << endl;
            cin >> nuevoDNI;
            cin >> nuevofechaDesde;
            cin >> nuevofechaHasta;
            cin >> nuevotipoHabitacion;

            return Reserva(nuevoDNI, nuevofechaDesde, nuevofechaHasta, (TipoHabitacion)nuevotipoHabitacion);
        }
        case 1:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            reserva.cargar(archivoEntrada);
            archivoEntrada.close();

            return reserva;
        }
    }
    return Reserva();

}

void MenuHabitacion()
{
    int maximaOpcion = 2;

    cout << endl
            << "Menu Reserva" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear habitacion" << endl
            << "2. Cargar habitacion" << endl;
    if (habitacionCreada)
    {
        maximaOpcion = 7;
        cout << "3. Guardar habitacion" << endl
        << "4. Mostrar habitacion" << endl
        << "5. Numero" << endl
        << "6. Tipo" << endl
        << "7. Accesorios" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            habitacion = MenuCrearHabitacion();
            habitacionCreada = true;
            LimpiarPantalla();
            MenuHabitacion();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            habitacion.cargar(archivoEntrada);
            archivoEntrada.close();
            habitacionCreada = true;
            LimpiarPantalla();
            MenuHabitacion();
            break;
        }
        case 3:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            habitacion.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuHabitacion();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            habitacion.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuHabitacion();
            break;
        }
        case 5:
        {
            LimpiarPantalla();
            cout << "El numero es: " << habitacion.numero() << endl;
            Pausar();
            LimpiarPantalla();
            MenuHabitacion();
            break;
        }
        case 6:
        {
            LimpiarPantalla();
            cout << "El tipo es: " << habitacion.tipo() << endl;
            Pausar();
            LimpiarPantalla();
            MenuHabitacion();
            break;
        }
        case 7:
        {
            LimpiarPantalla();
            cout << "Los accesorios son:" << endl;
            MostrarListaDeAccesorios(habitacion.accesorios());
            Pausar();
            LimpiarPantalla();
            MenuHabitacion();
            break;
        }
    }
}

Habitacion MenuCrearHabitacion()
{
    cout << "Creando una habitacion. Como desea crearla?" << endl
        << "0. Crear por consola" << endl
        << "1. Cargar de archivo" << endl;

    int opt = LeerOpcion(2);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            int numero = 0;
            int tipo = 0;
            Lista<Accesorio> accesorios = Lista<Accesorio>();
            int cantAccesorios = 0;
            int accesorio = 0;
            MostrarTiposDeAccesorios();
            MostrarTiposDeHabitaciones();
            cout << "Ingrese numero y tipo de habitacion, la cantidad de accesorios y la lista de los mismo, entre espacios" << endl;
            cin >> numero;
            cin >> tipo;
            cin >> cantAccesorios;
            for(int i = 0; i < cantAccesorios; i++)
            {
                cin >> accesorio;
                accesorios.agregar((Accesorio)accesorio);
            }
            return Habitacion(numero, (TipoHabitacion)tipo, accesorios);        }
        case 1:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            habitacion.cargar(archivoEntrada);
            archivoEntrada.close();

            return habitacion;
        }
    }
    return Habitacion();

}

void MenuHotel()
{
    int maximaOpcion = 2;

    cout << endl
            << "Menu Hotel" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear hotel" << endl
            << "2. Cargar hotel" << endl;
    if (hotelCreado)
    {
        maximaOpcion = 21;
        cout << "3. Guardar hotel" << endl
        << "4. Mostrar hotel" << endl
        << "5. Nombre" << endl
        << "6. Cadena" << endl
        << "7. Huespedes" << endl
        << "8. Habitaciones" << endl
        << "9. Ingresos" << endl
        << "10. Salidas" << endl
        << "11. Reservas" << endl
        << "12. Tarifa por dia" << endl
        << "13. Precio accesorio" << endl
        << "14. Vender" << endl
        << "15. Hacer reserva" << endl
        << "16. Sobre reservado" << endl
        << "17. Registrar huesped" << endl
        << "18. Desregistrar huesped" << endl
        << "19. Huespedes con palabra" << endl
        << "20. Calcular cuenta" << endl
        << "21. Reservas solapadas?" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            hotel = MenuCrearHotel();
            hotelCreado = true;
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            hotel.cargar(archivoEntrada);
            archivoEntrada.close();
            hotelCreado = true;
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 3:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            hotel.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            hotel.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 5:
        {
            cout << "El nombre del hotel es :" << hotel.nombre() << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 6:
        {
            cout << "La cadena es: " << hotel.cadena() << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 7:
        {
            LimpiarPantalla();
            MostrarHuespedesDeHotel(hotel);
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 8:
        {
            LimpiarPantalla();
            MostrarHabitacionesDeHotel(hotel);
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 9:
        {
            LimpiarPantalla();
            MostrarIngresosDeHotel(hotel);
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 10:
        {
            LimpiarPantalla();
            MostrarEgresosDeHotel(hotel);
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 11:
        {
            LimpiarPantalla();
            cout << "Las reservas son: " << endl;
            cout << "[" << endl;
            for (int i = 0; i < hotel.reservas().longitud(); i++)
            {
                 hotel.reservas().iesimo(i).mostrar(cout);
            }
            cout << "]" << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 12:
        {
            int tipoHab;
            LimpiarPantalla();
            MostrarTiposDeHabitaciones();
            cout << "Ingresar tipo de habitacion :";
            cin >> tipoHab;
            cout << endl;
            cout << "El precio es: " << hotel.tarifaXDia((TipoHabitacion)tipoHab) << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 13:
        {
            int acc;
            LimpiarPantalla();
            MostrarTiposDeAccesorios();
            cout << "Ingresar tipo de accesorio :";
            cin >> acc;
            cout << endl;
            cout << "El precio es: " << hotel.precioAccesorio((Accesorio)acc) << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 14:
        {
            string cad;
            LimpiarPantalla();
            cout << "Indique a que cadena se vende: ";
            cin >> cad;
            cout << "Vendiendose..." << endl;
            hotel.vender((Cadena)cad);
            cout << "Vendido" << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 15:
        {
            LimpiarPantalla();
            cout << "Haciendo reserva" << endl;
            Reserva res = MenuCrearReserva();
            hotel.hacerReserva(res);
            cout << "Reserva hecha" << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 16:
        {
            int fecha;
            LimpiarPantalla();
            cout << "Indique la fecha que desea saber si se encuentra sobre reservada: ";
            cin >> fecha;
            cout << "La fecha: " << fecha << (hotel.sobreReservado(fecha)? " si" : " no") << " se encuentra sobrereservada." << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 17:
        {
            int dni, fecha, habitacion;
            LimpiarPantalla();
            MostrarHabitacionesDeHotel(hotel);
            cout << "Indicar dni, fecha y habitacion del hotel, entre espacios" << endl;
            cin >> dni;
            cin >> fecha;
            cin >> habitacion;
            hotel.registrarHuesped(dni, fecha, hotel.habitaciones().iesimo(habitacion));
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 18:
        {
            int huesped, fecha;
            LimpiarPantalla();
            MostrarHuespedesDeHotel(hotel);
            cout << "Indicar el huesped que desea desregistrar y la fecha de salida" << endl;
            cin >> huesped;
            cin >> fecha;
            hotel.desRegistrarHuesped(hotel.huespedes().iesimo(huesped), fecha);
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 19:
        {
            cout << "Los huespedes con palabra son: ";
            int tam = hotel.huespedesConPalabra().longitud();
            for (int i = 0; i < tam; i++)
            {
                cout << hotel.huespedesConPalabra().iesimo(i) << " ";
            }
            cout << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 20:
        {
            int in = 0, out = 0, h = 0;
            LimpiarPantalla();
            MostrarIngresosDeHotel(hotel);
            MostrarEgresosDeHotel(hotel);
            MostrarHabitacionesDeHotel(hotel);
            cout << "Ingresar checkIn, checkOut y habitacion (indices de los mostrados) entre espacios" << endl;
            cin >> in;
            cin >> out;
            cin >> h;
            cout << "La cuenta es de " << hotel.calcularCuenta(hotel.ingresos().iesimo(in).first, hotel.salidas().iesimo(out), hotel.habitaciones().iesimo(h)) << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }
        case 21:
        {
            int dni;
            LimpiarPantalla();
            MostrarHuespedesDeHotel(hotel);
            cout << "Indicar el DNI de la consulta: ";
            cin >> dni;
            cout << endl;
            cout << "La persona con DNI: " << dni << (hotel.reservasSolapadas(dni)? " si" : " no") << " tiene reservas solapadas." << endl;
            Pausar();
            LimpiarPantalla();
            MenuHotel();
            break;
        }


    }
}

Hotel MenuCrearHotel()
{
    cout << "Creando un hotel. Como desea crearlo?" << endl
        << "0. Crear por consola" << endl
        << "1. Cargar de archivo" << endl;

    int opt = LeerOpcion(2);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();

            string op;
            string nombre;
            string cadena;
            Lista<Habitacion> habs = Lista<Habitacion>();
            Lista<pair<TipoHabitacion, Dinero> > thxd = Lista<pair<TipoHabitacion, Dinero> >();
            Lista<pair<Accesorio, Dinero> > pa = Lista<pair<Accesorio, Dinero> >();

            cout << "Indique el nombre del hotel: ";
            getline(cin, nombre);
            getline(cin, nombre);
            cout << "Indique el nombre de la cadena a la que pertenece el hotel " << nombre << ":";
            getline(cin, cadena);

            cout << "Desea agregar habitaciones? [s/n]";
            cin >> op;
            while(op == "s" || op == "S")
            {
                LimpiarPantalla();
                habs.agregar(MenuCrearHabitacion());
                LimpiarPantalla();
                cout << "Desea agregar otra habitacion? [s/n]";
                cin >> op;
            }
            LimpiarPantalla();
            cout << "Desea agregar tipos de habitaciones? [s/n]";
            cin >> op;
            while(op == "s" || op == "S")
            {
                LimpiarPantalla();
                MostrarTiposDeHabitaciones();
                cout << endl << "Indique el tipo de habitacion y el precio de la misma entre espacios :";
                int t, p;
                cin >> t;
                cin >> p;
                thxd.agregar(pair<TipoHabitacion, Dinero>((TipoHabitacion)t,p));
                LimpiarPantalla();
                cout << "Desea agregar otro tipo de habitacion? [s/n]";
                cin >> op;
            }
            LimpiarPantalla();

            cout << "Desea agregar accesorios? [s/n]";
            cin >> op;
            while(op == "s" || op == "S")
            {
                LimpiarPantalla();
                MostrarTiposDeAccesorios();
                cout << endl << "Indique el tipo de accesorio y el precio del mismo entre espacios :";
                int t, p;
                cin >> t;
                cin >> p;
                pa.agregar(pair<Accesorio, Dinero>((Accesorio)t,p));
                LimpiarPantalla();
                cout << "Desea agregar otro accesorio? [s/n]";
                cin >> op;
            }
            LimpiarPantalla();

            return Hotel(nombre, cadena, habs, thxd, pa);
        }
        case 1:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            hotel.cargar(archivoEntrada);
            archivoEntrada.close();

            return hotel;
        }
    }
    return Hotel();
}

void MenuMinisterio()
{
    int maximaOpcion = 2;

    cout << endl
            << "Menu Reserva" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear ministerio" << endl
            << "2. Cargar ministerio" << endl;
    if (ministerioCreado)
    {
        maximaOpcion = 10;
        cout << "3. Guardar ministerio" << endl
        << "4. Mostrar ministerio" << endl
        << "5. Secretarias" << endl
        << "6. Registro" << endl
        << "7. Cadena de hoteles" << endl
        << "8. Agregar hotel" << endl
        << "9. Cadenas amarretas" << endl
        << "10. Fusion Autorizada" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            ministerio = MenuCrearMinisterio();
            ministerioCreado = true;
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            ministerio.cargar(archivoEntrada);
            archivoEntrada.close();
            ministerioCreado = true;
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 3:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            ministerio.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            ministerio.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 5:
        {
            cout << "Secretarias :" << endl;
            for (int i = 0; i < ministerio.secretarias().longitud(); i++)
            {
                cout << i << ". " << ministerio.secretarias().iesimo(i) << endl;
            }
            Pausar();
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 6:
        {
            int prov;
            cout << "Secretarias :" << endl;
            for (int i = 0; i < ministerio.secretarias().longitud(); i++)
            {
                cout << i << ". " << ministerio.secretarias().iesimo(i) << endl;
            }
            cout << "Indicar la provincia :";
            cin >> prov;
            LimpiarPantalla();
            MostrarHoteles(ministerio.registro(ministerio.secretarias().iesimo(prov)), "Hoteles");
            Pausar();
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 7:
        {
            int t = ministerio.cadenasDeHoteles().longitud();
            for (int i = 0; i < t; i++)
            {
                cout << "Cadena " << i << " :" << endl;
                MostrarHoteles(ministerio.cadenasDeHoteles().iesimo(i), "Hoteles");
            }
            Pausar();
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 8:
        {
            int p;
            LimpiarPantalla();
            cout << "Agregando hotel al ministerio" << endl;
            cout << "Las provincias del ministerio son: " << endl;
            for (int i = 0; i < ministerio.secretarias().longitud(); i++)
            {
                cout << i << " ." << ministerio.secretarias().iesimo(i) << endl;
            }
            cout << "Indique la provincia a la cual pertenece el hotel: ";
            cin >> p;
            cout << endl << "Agregando hotel:" << endl;
            Hotel hot = MenuCrearHotel();
            ministerio.agregarHotel(hot, ministerio.secretarias().iesimo(p));
            cout << "Hotel registrado" << endl;
            Pausar();
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 9:
        {
            LimpiarPantalla();
            cout << "Cadenas amarretas: " << endl;
            int t = ministerio.cadenasAmarretas().longitud();
            for (int i = 0; i < t; i++)
            {
                cout << "  Cadena :" << ministerio.cadenasAmarretas().iesimo(i) << endl;
            }
            Pausar();
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
        case 10:
        {
            string cad1, cad2;
            LimpiarPantalla();
            cout << "Indique la primer cadena para la fusion: ";
            getline(cin, cad1);
            getline(cin, cad1);
            cout << "Indique la segunda cadena para la fusion (la que desaparece): ";
            getline(cin, cad2);
            cout << "Fusion en proceso entre: " << cad1 << " y " << cad2 << "." << endl;
            ministerio.fusionAutorizada(cad1, cad2);
            cout << "Fusion realizada" << endl;
            Pausar();
            LimpiarPantalla();
            MenuMinisterio();
            break;
        }
    }
}

Ministerio MenuCrearMinisterio()
{
    cout << "Creando un ministerio. Como desea crearlo?" << endl
        << "0. Crear por consola" << endl
        << "1. Cargar de archivo" << endl;

    int opt = LeerOpcion(2);

    LimpiarPantalla();

    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            string op;
            Lista<Provincia> pa = Lista<Provincia>();

            cout << "Desea agregar provincias? [s/n]";
            cin >> op;
            while(op == "s" || op == "S")
            {
                LimpiarPantalla();
                cout << "Indique el nombre de la provincia que desea agregar :";
                string p;
                getline(cin, p);
                getline(cin, p);
                pa.agregar(p);
                LimpiarPantalla();
                cout << "Desea agregar otra provincia? [s/n]";
                cin >> op;
            }
            LimpiarPantalla();

            return Ministerio(pa);
        }
        case 1:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            ministerio.cargar(archivoEntrada);
            archivoEntrada.close();

            return ministerio;
        }
    }
    return Ministerio();
}

//AUX
int LeerOpcion(int maxOpcion)
{
    cout << "  Ingrese una opcion [" << 0 << "-" << maxOpcion << "]: ";
    int opt;
    bool ok = false;
    while (!ok)
    {
        cin >> opt;
        ok = (opt <= maxOpcion);

        if (!ok)
            cout << "  Opcion incorrecta. Ingrese un numero entre [" << 1 << "-" << maxOpcion << "]: ";
    }
    return opt;
}

void Salir()
{
    cout << "Gracias, Vuelva prontos!" << endl;
}

void Pausar()
{
    cout << endl;
    string opt = "n";
#ifdef WIN32
    system("Pause");
#else
    cout << "Presione una tecla para continuar "<<endl;
    getline(cin,opt);
    getline(cin,opt);
#endif

}

void LimpiarPantalla()
{
#ifdef WIN32
    //system("cls");
#else
    //system("clear");
#endif
}

void AbrirArchivoParaLeer(ifstream &archivo)
{
    cout << "  Ingrese nombre de archivo existente: ";
    string opt;
    bool ok = false;
    getline(cin, opt);
    getline(cin, opt);
    archivo.open(opt.c_str());
    ok = archivo.good();

    while (!ok)
    {
        cout << "  Valor incorrecto. Ingrese nombre de archivo existente: ";
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
    }
}


void AbrirArchivoParaEscribir(ofstream &archivo)
{
    cout << "  Ingrese nombre de archivo: ";
    string opt;
    bool ok = false;
    getline(cin, opt);
    getline(cin, opt);
    archivo.open(opt.c_str());
    ok = archivo.good();

    while (!ok)
    {
        cout << "  Valor incorrecto. Ingrese nombre de archivo: ";
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
    }
}


void MostrarHoteles(const Lista<Hotel>& hoteles, string titulo)
{
    int tam = hoteles.longitud();
    cout << titulo << endl;
    for (int i = 0; i < tam; i++)
    {
        cout << i << " : " << hoteles.iesimo(i).nombre() << " (" << hoteles.iesimo(i).cadena() << ')' << endl;
    }
}

void MostrarTiposDeHabitaciones()
{
    cout << endl;
    cout << "Tipos de Habitacion (especificar por indice)" << endl;
    cout << "0. Simple " << endl;
    cout << "1. Doble " << endl;
    cout << "2. Triple " << endl;
    cout << "3. Cuadruple " << endl;
}

void MostrarTiposDeAccesorios()
{
    cout << endl;
    cout << "Tipos de Accesorio (especificar por indice)" << endl;
    cout << "0. Jacuzzi " << endl;
    cout << "1. LCD " << endl;
    cout << "2. PS3 " << endl;
    cout << "3. DVD" << endl;
    cout << "4. Pelotero" << endl;
    cout << "5. Inflable" << endl;
}

void MostrarListaDeAccesorios(const Lista<Accesorio> lista)
{
    cout << "[";
    for (int i = 0; i < lista.longitud()-1; i++)
    {
        cout << i << ". " << accesorio2String(lista.iesimo(i)) << ",";
    }
    if (lista.longitud() > 0)
    {
        cout << lista.longitud()-1 << ". " << accesorio2String(lista.iesimo(lista.longitud()-1));
    }
    cout << " ]" << endl;
}

void MostrarIngresosDeHotel(Hotel hotel)
{
    cout << endl;
    cout << "Los ingresos son: " << endl;
    cout << "[ ";
    for (int i = 0; i < hotel.ingresos().longitud() - 1; i++)
    {
        cout << i << ". " << hotel.ingresos().iesimo(i).first.first << " " << hotel.ingresos().iesimo(i).first.second << " " << hotel.ingresos().iesimo(i).second.numero() << " - ";
    }
    if (hotel.ingresos().longitud() > 0)
    {
        cout  << hotel.ingresos().iesimo(hotel.ingresos().longitud()-1).first.first << " "
                << hotel.ingresos().iesimo(hotel.ingresos().longitud()-1).first.second << " "
                << hotel.ingresos().iesimo(hotel.ingresos().longitud()-1).second.numero();
    }
    cout << " ]" << endl;
}
void MostrarEgresosDeHotel(Hotel hotel)
{
    cout << endl;
    cout << "Las salidas son: " << endl;
    cout << "[ ";
    for (int i = 0; i < hotel.salidas().longitud() - 1; i++)
    {
        cout << i << ". " << hotel.salidas().iesimo(i).first << " "
        << hotel.salidas().iesimo(i).second << " - ";
    }
    if (hotel.salidas().longitud() > 0)
    {
        cout  << hotel.salidas().iesimo(hotel.salidas().longitud()-1).first << " "
                << hotel.salidas().iesimo(hotel.salidas().longitud()-1).second;
    }
    cout << " ]" << endl;
}
void MostrarHuespedesDeHotel(Hotel hotel)
{
    cout << endl;
    cout << "Los huespedes son: " << endl;
    cout << "[ ";
    for (int i = 0; i < hotel.huespedes().longitud() - 1; i++)
    {
        cout << hotel.huespedes().iesimo(i) << "-";
    }
    if (hotel.huespedes().longitud() > 0)
    {
        cout << hotel.huespedes().iesimo(hotel.huespedes().longitud()-1);
    }
    cout << " ]" << endl;
}
void MostrarHabitacionesDeHotel(Hotel hotel)
{
    cout << endl;
    cout << "Las habitaciones son: " << endl;
    cout << "[ ";
    for (int i = 0; i < hotel.habitaciones().longitud() - 1; i++)
    {
        cout << hotel.habitaciones().iesimo(i).numero() << "-";
    }
    if (hotel.habitaciones().longitud() > 0)
    {
        cout << hotel.habitaciones().iesimo(hotel.habitaciones().longitud()-1).numero();
    }
    cout << " ]" << endl;
}
string accesorio2String(Accesorio s) {
  if (s == DVD) return "DVD";
  if (s == Inflable) return "Inflable";
  if (s == Jacuzzi) return "Jacuzzi";
  if (s == LCD) return "LCD";
  if (s == Pelotero) return "Pelotero";
  if (s == PS3) return "PS3";
  return "???";
}

//Test main


#ifdef DBG
int main()
{
    MenuPrincipal();
}

#endif
