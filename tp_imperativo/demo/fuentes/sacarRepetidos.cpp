Lista<DNI> Hotel::sacarRepetidos(const Lista<DNI>& dnis) const {
	Lista<DNI> result;
	int i = 0;
	int longitud = dnis.longitud();    
	//Pc: i == 0 $ \land $ longitud == $ |dnis| $ $ \land $ result == []
	//B: i < longitud
	while( i < longitud ){		
		//Fv: longitud - i
		//Cota: 0
		//I: 0$ \leq $i$ \leq $longitud $ \land $ longitud == $ |dnis| $ $ \land $ result == [$ dnis_k $| k$ \selec $[0..i), ($ \lnot $$ \exists $j$ \selec $[0..k)) $ dnis_j $ == $ dnis_k $]
		//Estado e1 
		//Vale B $ \land $ I
		if( !result.pertenece(dnis.iesimo(i)) ){
			result.agregarAtras(dnis.iesimo(i));
		}
		//Qif:(($ dnis_i $ $ \in $ result) $ \land $ (result == result@e1) )$ \lor $( ($ dnis_i $ $ \notin $ result) $ \land $ (result == result@e1 ++ [$ dnis_i $]))
		//estado e2
		//vale Qif $ \land $ i == i@e1
		i++;
		//estado e3
		//vale i == i@e2 + 1 $ \land $ result == result@e2
	}
	//Qc: result == [$ dnis_i $| i$ \selec $[0..longitud), ($ \lnot $$ \exists $j$ \selec $[0..i)) $ dnis_j $ == $ dnis_i $]
	return result;
	//vale result == [$ dnis_i $| i$ \selec $[0..longitud), ($ \lnot $$ \exists $j$ \selec $[0..i)) $ dnis_j $ == $ dnis_i $]
}