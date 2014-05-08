Lista<DNI> Hotel::procesarIesimoIngreso( int i ) const {
    pair<CheckIn,Habitacion> in = this->_ingresos.iesimo(i);
    CheckIn ci = in.first;
    Lista<DNI> result;
	int longitud = this->_salidas.longitud();
    int j = 0;
	//Fv: longitud - j
	//Cota: 0
   	//Pc: vale ci == prm($ingresos_i$) $ \land $ result == [] $ \land $ j == 0 $ \land $ longitud == $|salidas(this)|$ 
	//$ \land $ in == $ingresos_i$
    while( j < longitud )
    {//E1: vale I $ \land $ B
        //I:vale result == [prm(prm(in)) $|$ in $\selec$ [$ingresos(this)_i$], co $\selec$ $salidas(this){[0..j)}$, prm(prm(in))) == prm(co) 
		//$ \land $ noHaySalidaEnElmedio(prm(in),co,this) $ \land $ hayReserva(in,co,this)]
		// $ \land $ 0$ \leq $j$ \leq $longitud $ \land $ longitud == $|salidas(this)|$ $ \land $ ci == prm($ingresos_i$) $ \land $ in == $ingresos_i$
        CheckOut co = this->_salidas.iesimo(j);
		//E2: vale j == j@E1 $ \land $ co == salidas($this$)_j $ \land $ result == result@E1
        if( ci.first == co.first && noHaySalidaEnElMedio(ci,co) && hayReserva(in,co) )
            result.agregarAtras( ci.first );
		 //Qif: vale (( prm(ci) == prm(co) $ \land $ noHaySalidaEnElMedio(ci,co) $ \land $ hayReserva(in,co) 
		 //				$ \land $ result == result@E2 ++ [ci]) $ \lor $
		 //             (( prm(ci) != prm(co) $ \lor $ !noHaySalidaEnElMedio(ci,co) $ \lor $ !hayReserva(in,co)) 
		 //				$ \land $ result == result@E2) 
		 //  $ \land $  j == j@E2 $ \land $ co == co@E2 $ \land $ ci == ci@E2
						
         j++;
		 //E3: vale  j == j@Qif + 1 $ \land $ co == co@Qif $ \land $ ci == ci@Qif $ \land $ result == result@Qif
		 
    }
	//Qc:result== [prm(prm(in)) $|$ in $\selec$ [$ingresos(this)_i$], co $\selec$ salidas(this), 
	//prm(prm(in))) == prm(co) $ \land $ noHaySalidaEnElmedio(prm(in),co,this) $ \land $ hayReserva(in,co,this)]
    return result;
	//Q: vale res == [prm(prm(in)) $|$ in $\selec$ [ingresos(this)_i], co $\selec$ salidas(this), 
	//prm(prm(in))) == prm(co) $ \land $ noHaySalidaEnElmedio(prm(in),co,this) $ \land $ hayReserva(in,co,this)]
}