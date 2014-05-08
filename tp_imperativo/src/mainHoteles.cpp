#include "interfaz.h"
//#include <sstream>

int main(){
//    cout.setf(ios::boolalpha);

//    //Test IO Reserva
//    Reserva r1;
//    istringstream instream;
//    instream.clear();
//    string instr = "R 31459265 3 5 |Cuadruple| |False|";
//    cout << instr << endl;
//    instream.str(instr);
//    r1.cargar(instream);
//    r1.mostrar(cout);
//
//    ostringstream strout;
//    strout.clear();
//    r1.guardar(strout);
//    cout <<strout.str();

//    //Test IO Habitacion
//    Habitacion h1;
//    istringstream instream;
//    instream.clear();
//    string instr= "A 50 |Cuadruple| [(|Jacuzzi|), (|PS3|), (|DVD|)]";
//    cout << instr << endl;
//    instream.str(instr);
//    h1.cargar(instream);
//    h1.guardar(cout);
//    cout << endl;
//    h1.mostrar(cout);

//    //TEST IO
//        //Declaraciones auxiliares
//            ostringstream assert1;
//            ostringstream assert2;
//            ostringstream os;
//            istringstream is;
//            assert1.clear();
//            assert2.clear();
//            is.clear();
//            os.clear();
//        //guardo el hotel del test en os
//            ht2.guardar(os);
//        //guardo el hotel del test en assert1
//            ht2.guardar(assert1);
//        //cargo is con los datos de os
//            is.str(os.str());
//        //declaro un hotel nuevo
//            Hotel hotelTest;
//        //cargo los datos de is =>>>>>>>>>>>>>>>>>>>>>> En este punto deberia valer ht2 == hotelTest
//            hotelTest.cargar(is);
//            hotelTest.guardar(assert2);
//        //guardo hoteltest en assert2
//        //Luego, como vale ht2 == hotelTest => las strings deben ser iguales.
//            cout << "Test IO Hotel(incluye las IO's de reserva y habitacion): " << (assert1.str() == assert2.str()) << endl;
//    //FIN TEST IO

	// stringstream stream;
	// stream.clear();
	// string archivo = "[((1213,2),2), ((1213,2),2), ((1213,2),2634643)]";//"[(A 21 |Simple| [(|LCD|)]), (A 22 |Simple| [(|Pelotero|), (|Inflable|)])] [((1223, 3),21), ((1224, 3), 22)] [(1223, 5), (1224, 7)]";
	// stream.str(archivo);


	// Lista<pair<pair<DNI, Fecha>, int> > ls;
	// stream >> ls;
	// int i = 0;
	// while( i < ls.longitud() )
	// {
	// 	//cout << ls.iesimo(i).first << " : " << ls.iesimo(i).second << endl;
	// 	cout << ls.iesimo(i).first.first << " : " << ls.iesimo(i).first.second << " : " << ls.iesimo(i).second << endl;
	// 	i++;
	// }

    MenuPrincipal();
    return 0;
}
