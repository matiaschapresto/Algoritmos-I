bool Hotel::noHaySalidaEnElMedio(const CheckIn& ci, const CheckOut& co) const {
    bool result = false;
    int i = 0;
	int longitud = this->_salidas.longitud();
	//Pc: result == false $ \land $ i == 0 $ \land $ longitud == |salidas(this)|
	//Fv: longitud - i
	//Cota: 0
    while( i < longitud )
    {//E1: vale B && I: result == (( $ \exists $ co $ \selec $ $ salidas(this)_{[0..i)} $), prm(co) == prm(ci)) 
	//$ fechaCheckIn(ci) < fechaCheckOut(co) < fechaCheckOut(o)) $ $ \land $ 0$ \leq $i$ \leq $n $ \land $ longitud == $|$salidas(this)$|$
        CheckOut oco = this->_salidas.iesimo(i);
		//E2: vale i == i@E1 $ \land $ result == result@E1 $ \land $ oco == $ salidas_i $
        result = result || (ci.first == oco.first && ci.second < oco.second && oco.second < co.second);
		//E3: vale i == i@E2 $ \land $ result == result@E2 $ \lor $ 
		//(prm(oco) == prm(ci) $ \land $ sgd(ci) $ < $ sgd(oco) $ \land $ sgd(oco) $ < $ sgd(co)) $ \land $ oco == oco@E2
        i++;
		//E4: vale i == i@E3 + 1 $ \land $ result == result@E3 $ \land $ oco == oco@E3
    }
	//Qc: ($ \exists $ co \selec salidas(this), prm(co) == prm(ci)) $ fechaCheckIn(ci) < fechaCheckOut(co) < fechaCheckOut(o) $
    return !result;
	//vale result = $ \lnot $ ($ \exists $ co \selec salidas(this), prm(co) == prm(ci)) $ fechaCheckIn(ci) < fechaCheckOut(co) < fechaCheckOut(o) $
}