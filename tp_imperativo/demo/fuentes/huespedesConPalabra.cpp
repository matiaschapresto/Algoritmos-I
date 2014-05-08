Lista<DNI> Hotel::huespedesConPalabra() const {
    Lista<DNI> result;
    int i = 0;
    //e1
    while( i < this->_ingresos.longitud() )
    {
        //e2
        result.concatenar( procesarIesimoIngreso( i ) );
        //e3
        i++;
        //e4
    }
    //e5
    result = sacarRepetidos(result);
    //e6
    return result;
}