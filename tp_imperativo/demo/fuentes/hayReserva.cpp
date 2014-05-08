bool Hotel::hayReserva(const pair<CheckIn, Habitacion>& ingreso, const CheckOut& checkOut) const {
    bool hayUnaReserva = false;
    int i = 0;
    int longitud = this->_reservas.longitud();
    //Pc: (i == 0) $ \land $ (hayUnaReserva==false) $ \land $ (longuitud == |reservas(this)|)
    //B: i $<$ longitud
    //Fv: longitud - i
    //cota: 0
    while(i < longitud){
        //I: (0$\leq$i$\leq$longuitud) $ \land $ (longuitud == |reservas(this)|) $ \land $ hayUnaReserva = ($\exists$ j $\selec$ [0..i))
		//esReservaValida(snd(ingreso), $reservas(this)_j$ , fst(ingreso), checkout)
        //estado e1
        //Vale I $ \land $ B
        hayUnaReserva = hayUnaReserva || 
		(esReservaValida(ingreso.second, (this->_reservas.iesimo(i)), ingreso.first, checkOut));
        //estado e2
        //Vale i==i@e1 $ \land $ hayUnaReserva = hayUnaReserva@e1 $ \lor $ 
		//esReservaValida(snd(ingreso), $ reservas(this)_i $ , fst(ingreso), checkout)
        i++;
        //estado e3
        //Vale i==i@e2 + 1 $ \land $ hayUnaReserva == hayUnaReserva@e2
    }
    //Qc: hayUnaReserva = ($\exists$ j $\selec$ [0..longitud)) 
	//esReservaValida(snd(ingreso), $ reservas(this)_j $ , fst(ingreso), checkout)
    return hayUnaReserva;
    //Estado final res == ($\exists$ j $\selec$ [0..|reservas(this)|)) 
	//esReservaValida(snd(ingreso), $ reservas(this)_j $ , fst(ingreso), checkout) 
	//(porque longitud == |reservas|)
}