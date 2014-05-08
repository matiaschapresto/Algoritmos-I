module Main where

import Habitacion
import Hotel
import Ministerio
import Reserva
import Tipos
import HUnit

--Auxiliares
menorHabitacion :: [Habitacion] -> Int
menorHabitacion (h:[]) = numeroH h
menorHabitacion (h1:(h2:hs))	| numeroH h1 < menorHabitacion (h2:hs) = numeroH h1
								| otherwise = menorHabitacion (h2:hs)

ordenaHabitaciones :: [Habitacion] -> [Habitacion]
ordenaHabitaciones [] = []
ordenaHabitaciones (h:[]) = (h:[])
ordenaHabitaciones (h1:(h2:hs))	| menorHabitacion (h1:(h2:hs)) == numeroH h1 = (h1:(ordenaHabitaciones(h2:hs)))
								| menorHabitacion (h1:(h2:hs)) == numeroH h2 = (h2:(ordenaHabitaciones(h1:hs)))
								| otherwise = ordenaHabitaciones (h1:ordenaHabitaciones(h2:hs))

menorDocumento :: [DNI] -> DNI
menorDocumento (d:[]) = d
menorDocumento (d1:(d2:ds))	| d1 < menorDocumento (d2:ds) = d1
							| otherwise = menorDocumento (d2:ds)

ordenaDocumentos :: [DNI] -> [DNI]
ordenaDocumentos [] = []
ordenaDocumentos (d:[]) = (d:[])
ordenaDocumentos (d1:(d2:ds))	| menorDocumento (d1:(d2:ds)) == d1 = (d1:ordenaDocumentos(d2:ds))
								| menorDocumento (d1:(d2:ds)) == d2 = (d2:ordenaDocumentos(d1:ds))
								| otherwise = ordenaDocumentos (d1:ordenaDocumentos(d2:ds))

mismoIngreso :: (CheckIn,Habitacion) -> (CheckIn,Habitacion) -> Bool
mismoIngreso i1 i2 = fst i1 == fst i2 && mismaHabitacion (snd i1) (snd i2)

menorIngreso :: [(CheckIn,Habitacion)] -> (CheckIn,Habitacion)
menorIngreso (i:[]) = i
menorIngreso (i1:(i2:is))	| fst i1 < fst (menorIngreso (i2:is)) = i1
							| fst i1 > fst (menorIngreso (i2:is)) = menorIngreso (i2:is)
							| (numeroH (snd i1)) < (numeroH (snd (menorIngreso (i2:is)))) = i1
							| otherwise = menorIngreso(i2:is)

ordenaIngresos :: [(CheckIn,Habitacion)] -> [(CheckIn,Habitacion)]
ordenaIngresos [] = []
ordenaIngresos (i:[]) = (i:[])
ordenaIngresos (i1:(i2:is))	| mismoIngreso (menorIngreso(i1:(i2:is))) i1 = (i1:ordenaIngresos(i2:is))
							| mismoIngreso (menorIngreso(i1:(i2:is))) i2 = (i2:ordenaIngresos(i1:is))
							| otherwise = ordenaIngresos (i1:ordenaIngresos(i2:is))

menorReserva :: [Reserva] -> Reserva
menorReserva (r:[]) = r
menorReserva (r1:(r2:rs))	| documentoR r1 < documentoR (menorReserva (r2:rs)) = r1
							| documentoR r1 > documentoR (menorReserva (r2:rs)) = menorReserva (r2:rs)
							| fechaDesdeR r1 < fechaDesdeR (menorReserva (r2:rs)) = r1
							| otherwise = menorReserva (r2:rs)

ordenaReservas :: [Reserva] -> [Reserva]
ordenaReservas [] = []
ordenaReservas (r:[]) = (r:[])
ordenaReservas (r1:(r2:rs))	| menorReserva(r1:(r2:rs)) == r1 = (r1:ordenaReservas(r2:rs))
							| menorReserva(r1:(r2:rs)) == r2 = (r2:ordenaReservas(r1:rs))
							| otherwise = ordenaReservas (r1:ordenaReservas(r2:rs))

menorCheckOut :: [CheckOut] -> CheckOut
menorCheckOut (co:[]) = co
menorCheckOut (co1:(co2:cos))	| co1 < menorCheckOut (co2:cos) = co1
							| otherwise = menorCheckOut (co2:cos)
							
ordenaCheckOuts :: [CheckOut] -> [CheckOut]
ordenaCheckOuts [] = []
ordenaCheckOuts (co:[]) = (co:[])
ordenaCheckOuts (co1:(co2:cos))	| menorCheckOut(co1:(co2:cos)) == co1 = (co1:ordenaCheckOuts(co2:cos))
								| menorCheckOut(co1:(co2:cos)) == co2 = (co2:ordenaCheckOuts(co1:cos))
								| otherwise = ordenaCheckOuts (co1:ordenaCheckOuts(co2:cos))

menorProvincia :: [Provincia] -> Provincia
menorProvincia (p:[]) = p
menorProvincia (p1:(p2:ps))	| p1 < menorProvincia (p2:ps) = p1
							| otherwise = menorProvincia (p2:ps)
							
ordenaProvincias :: [Provincia] -> [Provincia]
ordenaProvincias [] = []
ordenaProvincias (p:[]) = (p:[])
ordenaProvincias (p1:(p2:ps))	| menorProvincia (p1:(p2:ps)) == p1 = (p1:ordenaProvincias(p2:ps))
								| menorProvincia (p1:(p2:ps)) == p2 = (p2:ordenaProvincias(p1:ps))
								| otherwise = ordenaProvincias (p1:ordenaProvincias(p2:ps))

menorHotel :: [Hotel] -> Hotel
menorHotel (h:[]) = h
menorHotel (h1:(h2:hs))	| nombreH h1 < nombreH (menorHotel (h2:hs)) = h1
						| nombreH h1 > nombreH (menorHotel (h2:hs)) = menorHotel(h2:hs)
						| cadenaH h1 < cadenaH (menorHotel (h2:hs)) = h1
						| otherwise = menorHotel (h2:hs)

ordenaHoteles :: [Hotel] -> [Hotel]
ordenaHoteles [] = []
ordenaHoteles (h:[]) = (h:[])
ordenaHoteles (h1:(h2:hs))	| mismoHotel (menorHotel (h1:(h2:hs))) h1 = (h1:ordenaHoteles(h2:hs))
							| mismoHotel (menorHotel (h1:(h2:hs))) h2 = (h2:ordenaHoteles(h1:hs))
							| otherwise = ordenaHoteles (h1:ordenaHoteles(h2:hs))

ordenaListasDeHotelesAux1 :: [[Hotel]] -> [[Hotel]]
ordenaListasDeHotelesAux1 [] = []
ordenaListasDeHotelesAux1 (hs:hss) = ((ordenaHoteles hs): (ordenaListasDeHotelesAux1 hss))

menorCadena :: [[Hotel]] -> Cadena
menorCadena ((h:hs):[]) = cadenaH h
menorCadena (((h1):hs1):((h2:hs2):hss))	| cadenaH h1 < (menorCadena ((h2:hs2):hss)) = cadenaH h1
										| otherwise = menorCadena ((h2:hs2):hss)

ordenaListasDeHotelesAux2 :: [[Hotel]] -> [[Hotel]]
ordenaListasDeHotelesAux2 [] = []
ordenaListasDeHotelesAux2 (hs:[]) = (hs:[])
ordenaListasDeHotelesAux2 ((h1:hs1):((h2:hs2):hss))	| cadenaH h1 < menorCadena ((h2:hs2):hss) = (h1:hs1):(ordenaListasDeHotelesAux2 ((h2:hs2):hss))
													| cadenaH h2 < menorCadena ((h1:hs1):hss) = (h2:hs2):(ordenaListasDeHotelesAux2 ((h1:hs1):hss))
													| otherwise = ordenaListasDeHotelesAux2 ((h1:hs1):(ordenaListasDeHotelesAux2 ((h2:hs2):hss)))

ordenaListasDeHoteles :: [[Hotel]] -> [[Hotel]]
ordenaListasDeHoteles hss = ordenaListasDeHotelesAux2 (ordenaListasDeHotelesAux1 hss)

hayDeTipo :: [Habitacion] -> TipoHabitacion -> Bool
hayDeTipo [] t = False
hayDeTipo (h:hs) t	| tipoH h == t = True
					| otherwise = hayDeTipo hs t

tarifaXDiaAux :: Hotel -> TipoHabitacion -> Dinero
tarifaXDiaAux ht t	| hayDeTipo (habitacionesH ht) t == True = tarifaXDiaH ht t
					| otherwise = 0

tieneAccesorio :: [Habitacion] -> Accesorio -> Bool
tieneAccesorio [] a = False
tieneAccesorio (h:hs) a | a `elem` accesoriosH h = True
						| otherwise = tieneAccesorio hs a
					
precioAccesorioAux :: Hotel -> Accesorio -> Dinero
precioAccesorioAux ht t	| tieneAccesorio (habitacionesH ht) t == True = precioAccesorioH ht t
						| otherwise = 0
--Mismos de Listas
mismosAccesorios :: [Accesorio] -> [Accesorio] -> Bool
mismosAccesorios [] [] = True
mismosAccesorios (a1:as1) (a2:as2)	| a1 == a2 = mismosAccesorios as1 as2
										| otherwise = False
mismaListaAccesorios _ _ = False

mismasHabitacionesAux :: [Habitacion] -> [Habitacion] -> Bool
mismasHabitacionesAux [] [] = True
mismasHabitacionesAux (h1:hs1) (h2:hs2)	| mismaHabitacion h1 h2 == True = mismasHabitacionesAux hs1 hs2
											| otherwise = False
mismasHabitacionesAux _ _ = False

mismasHabitaciones :: [Habitacion] -> [Habitacion] -> Bool
mismasHabitaciones hs1 hs2 = mismasHabitacionesAux (ordenaHabitaciones hs1) (ordenaHabitaciones hs2)

mismosDocumentosAux :: [DNI] -> [DNI] -> Bool
mismosDocumentosAux [] [] = True
mismosDocumentosAux (d1:ds1) (d2:ds2)	| d1 == d2 = mismosDocumentosAux ds1 ds2
										| otherwise = False
mismosDocumentosAux _ _ = False

mismosDocumentos :: [DNI] -> [DNI] -> Bool
mismosDocumentos ds1 ds2 = mismosDocumentosAux (ordenaDocumentos ds1) (ordenaDocumentos ds2)

mismosIngresosAux :: [(CheckIn,Habitacion)] -> [(CheckIn,Habitacion)] -> Bool
mismosIngresosAux [] [] = True
mismosIngresosAux (i1:is1) (i2:is2)	| mismoIngreso i1 i2 = mismosIngresos is1 is2
									| otherwise = False
mismosIngresosAux _ _ = False

mismosIngresos :: [(CheckIn,Habitacion)] -> [(CheckIn,Habitacion)] -> Bool
mismosIngresos is1 is2 = mismosIngresosAux (ordenaIngresos is1) (ordenaIngresos is2)

mismasReservasAux :: [Reserva] -> [Reserva] -> Bool
mismasReservasAux [] [] = True
mismasReservasAux (r1:rs1) (r2:rs2)	| mismaReserva r1 r2 = mismasReservasAux rs1 rs2
									| otherwise = False
mismasReservasAux _ _ = False

mismasReservas :: [Reserva] -> [Reserva] -> Bool
mismasReservas rs1 rs2 = mismasReservasAux (ordenaReservas rs1) (ordenaReservas rs2)

mismosCheckOutsAux :: [CheckOut] -> [CheckOut] -> Bool
mismosCheckOutsAux [] [] = True
mismosCheckOutsAux (co1:cos1) (co2:cos2)	| co1 == co2 = mismosCheckOutsAux cos1 cos2
											| otherwise = False
mismosCheckOutsAux _ _ = False

mismosCheckOuts :: [CheckOut] -> [CheckOut] -> Bool
mismosCheckOuts co1 co2 = mismosCheckOutsAux (ordenaCheckOuts co1) (ordenaCheckOuts co2)

mismasSecretariasAux :: [Provincia] -> [Provincia] -> Bool
mismasSecretariasAux [] [] = True
mismasSecretariasAux (p1:ps1) (p2:ps2)	| p1 == p2 = mismasSecretariasAux ps1 ps2
										| otherwise = False
mismasSecretariasAux _ _ = False

mismasSecretarias :: [Provincia] -> [Provincia] -> Bool
mismasSecretarias ps1 ps2 = mismasSecretariasAux (ordenaProvincias ps1) (ordenaProvincias ps2)

mismosHotelesAux :: [Hotel] -> [Hotel] -> Bool
mismosHotelesAux [] [] = True
mismosHotelesAux (h1:hs1) (h2:hs2)	| mismoHotel h1 h2 = mismosHotelesAux hs1 hs2
									| otherwise = False
mismosHotelesAux _ _ = False

mismosHoteles :: [Hotel] -> [Hotel] -> Bool
mismosHoteles hs1 hs2 = mismosHotelesAux (ordenaHoteles hs1) (ordenaHoteles hs2)

mismasListasDeHotelesAux :: [[Hotel]] -> [[Hotel]] -> Bool
mismasListasDeHotelesAux [] [] = True
mismasListasDeHotelesAux (hs1:hss1) (hs2:hss2)	| mismosHoteles hs1 hs2 = mismasListasDeHoteles hss1 hss2
mismasListasDeHotelesAux _ _ = False

mismasListasDeHoteles :: [[Hotel]] -> [[Hotel]] -> Bool
mismasListasDeHoteles hss1 hss2 = mismasListasDeHotelesAux (ordenaListasDeHoteles hss1) (ordenaListasDeHoteles hss2)

--Mismos de Reserva
mismaReserva :: Reserva -> Reserva -> Bool
mismaReserva r1 r2	| mismoDocumentoR r1 (documentoR r2) && mismaFechaDesdeR r1 (fechaDesdeR r2) && mismaFechaHastaR r1 (fechaHastaR r2)
					&& mismoTipoR r1 (tipoR r2) && mismoEstadoR r1 (confirmadaR r2) = True
					| otherwise = False
					
mismoDocumentoR :: Reserva -> DNI -> Bool
mismoDocumentoR r d | documentoR r == d = True
					| otherwise = False

mismaFechaDesdeR :: Reserva -> Fecha -> Bool
mismaFechaDesdeR r f	| fechaDesdeR r == f = True
						| otherwise = False

mismaFechaHastaR :: Reserva -> Fecha -> Bool
mismaFechaHastaR r f	| fechaHastaR r == f = True
						| otherwise = False

mismoTipoR :: Reserva -> TipoHabitacion -> Bool
mismoTipoR r t	| tipoR r == t = True
				| otherwise = False

mismoEstadoR :: Reserva -> Bool -> Bool
mismoEstadoR r c	| confirmadaR r == c = True
					| otherwise = False

--Mismos de Habitacion
mismaHabitacion :: Habitacion -> Habitacion -> Bool
mismaHabitacion h1 h2	| mismoNumeroH h1 (numeroH h2) && mismoTipoH h1 (tipoH h2) && mismosAccesoriosH h1 (accesoriosH h2) = True
						| otherwise = False

mismoNumeroH :: Habitacion -> Int -> Bool
mismoNumeroH h n	| numeroH h == n = True
					| otherwise = False

mismoTipoH :: Habitacion -> TipoHabitacion -> Bool
mismoTipoH h t	| tipoH h == t = True
				| otherwise = False

mismosAccesoriosH :: Habitacion -> [Accesorio] -> Bool
mismosAccesoriosH h as	| mismosAccesorios (accesoriosH h) as = True
						| otherwise = False

--Mismos de Hotel
mismoHotel :: Hotel -> Hotel -> Bool
mismoHotel h1 h2	| mismoNombreHT h1 (nombreH h2) && mismaCadenaHT h1 (cadenaH h2) && mismosHuespedesHT h1 (huespedesH h2)
					&& mismasHabitacionesHT h1 (habitacionesH h2) && mismosIngresosHT h1 (ingresosH h2) && mismasSalidasHT h1 (salidasH h2)
					&& mismasReservasHT h1 (reservasH h2) 
					&& (tarifaXDiaAux h1 Simple) == (tarifaXDiaAux h2 Simple)
					&& (tarifaXDiaAux h1 Doble) == (tarifaXDiaAux h2 Doble)
					&& (tarifaXDiaAux h1 Triple) == (tarifaXDiaAux h2 Triple)
					&& (tarifaXDiaAux h1 Cuadruple) == (tarifaXDiaAux h2 Cuadruple)
					&& (precioAccesorioAux h1 Jacuzzi) == (precioAccesorioAux h2 Jacuzzi)
					&& (precioAccesorioAux h1 LCD) == (precioAccesorioAux h2 LCD)
					&& (precioAccesorioAux h1 PS3) == (precioAccesorioAux h2 PS3)
					&& (precioAccesorioAux h1 DVD) == (precioAccesorioAux h2 DVD)
					&& (precioAccesorioAux h1 Pelotero) == (precioAccesorioAux h2 Pelotero)
					&& (precioAccesorioAux h1 Inflable) == (precioAccesorioAux h2 Inflable) = True
					| otherwise = False

mismoNombreHT :: Hotel -> Nombre -> Bool
mismoNombreHT ht n	| nombreH ht == n = True
					| otherwise = False

mismaCadenaHT :: Hotel -> Cadena -> Bool
mismaCadenaHT ht c	| cadenaH ht == c = True
					| otherwise = False

mismosHuespedesHT :: Hotel -> [DNI] -> Bool
mismosHuespedesHT ht ds = mismosDocumentos (huespedesH ht) ds

mismasHabitacionesHT :: Hotel -> [Habitacion] -> Bool
mismasHabitacionesHT ht hs = mismasHabitaciones (habitacionesH ht) hs

mismosIngresosHT :: Hotel -> [(CheckIn,Habitacion)] -> Bool
mismosIngresosHT ht is = mismosIngresos (ingresosH ht) is

mismasSalidasHT :: Hotel -> [CheckOut] -> Bool
mismasSalidasHT ht co = mismosCheckOuts (salidasH ht) co

mismasReservasHT :: Hotel -> [Reserva] -> Bool
mismasReservasHT ht rs = mismasReservas (reservasH ht) rs

mismaTarifaHT :: Hotel -> TipoHabitacion -> Dinero -> Bool
mismaTarifaHT ht t d = tarifaXDiaH ht t == d

mismoPrecioAccesorioHT :: Hotel -> Accesorio -> Dinero -> Bool
mismoPrecioAccesorioHT ht a d = precioAccesorioH ht a == d

--Mismos de Ministerio
mismasSecretariasM :: Ministerio -> [Provincia] -> Bool
mismasSecretariasM m ps = mismasSecretarias (secretariasM m) ps

mismosRegistrosM :: Ministerio -> Provincia -> [Hotel] -> Bool
mismosRegistrosM m p hs = mismosHoteles (registroM m p) hs

mismasCadenasM :: Ministerio -> [[Hotel]] -> Bool
mismasCadenasM m hss = mismasListasDeHoteles (cadenasDeHotelesM m) hss
    
--Reservas
r1 :: Reserva
r1 = nuevaR 33444555 1 2 Simple

testRD1 = TestCase (assertEqual "Test Documento Reserva1:" (documentoR r1) (33444555))
testRFD1 = TestCase (assertEqual "Test Fecha Desde Reserva1:" (fechaDesdeR r1) (1))
testRFH1 = TestCase (assertEqual "Test Fecha Hasta Reserva1: " (fechaHastaR r1) (2))
testRT1 = TestCase (assertEqual "Test Tipo Reserva1: " (tipoR r1) (Simple))
testRC1 = TestCase (assertEqual "Test Confirmada Reserva1: " (confirmadaR r1) (False))

r2 :: Reserva
r2 = confirmarR r1

testRD2 = TestCase (assertEqual "Test Documento Reserva2:" (documentoR r2) (33444555))
testRFD2 = TestCase (assertEqual "Test Fecha Desde Reserva2:" (fechaDesdeR r2) (1))
testRFH2 = TestCase (assertEqual "Test Fecha Hasta Reserva2: " (fechaHastaR r2) (2))
testRT2 = TestCase (assertEqual "Test Tipo Reserva2: " (tipoR r2) (Simple))
testRC2 = TestCase (assertEqual "Test Confirmada Reserva2: " (confirmadaR r2) (True))

r3 :: Reserva
r3 = nuevaR 33444555 3 5 Doble

testRD3 = TestCase (assertEqual "Test Documento Reserva3:" (documentoR r3) (33444555))
testRFD3 = TestCase (assertEqual "Test Fecha Desde Reserva3:" (fechaDesdeR r3) (3))
testRFH3 = TestCase (assertEqual "Test Fecha Hasta Reserva3: " (fechaHastaR r3) (5))
testRT3 = TestCase (assertEqual "Test Tipo Reserva3: " (tipoR r3) (Doble))
testRC3 = TestCase (assertEqual "Test Confirmada Reserva3: " (confirmadaR r3) (False))

r4 :: Reserva
r4 = confirmarR r3

testRD4 = TestCase (assertEqual "Test Documento Reserva4:" (documentoR r4) (33444555))
testRFD4 = TestCase (assertEqual "Test Fecha Desde Reserva4:" (fechaDesdeR r4) (3))
testRFH4 = TestCase (assertEqual "Test Fecha Hasta Reserva4: " (fechaHastaR r4) (5))
testRT4 = TestCase (assertEqual "Test Tipo Reserva4: " (tipoR r4) (Doble))
testRC4 = TestCase (assertEqual "Test Confirmada Reserva4: " (confirmadaR r4) (True))

r5 :: Reserva
r5 = nuevaR 37654321 4 7 Doble

testRD5 = TestCase (assertEqual "Test Documento Reserva5:" (documentoR r5) (37654321))
testRFD5 = TestCase (assertEqual "Test Fecha Desde Reserva5:" (fechaDesdeR r5) (4))
testRFH5 = TestCase (assertEqual "Test Fecha Hasta Reserva5: " (fechaHastaR r5) (7))
testRT5 = TestCase (assertEqual "Test Tipo Reserva5: " (tipoR r5) (Doble))
testRC5 = TestCase (assertEqual "Test Confirmada Reserva5: " (confirmadaR r5) (False))

r6 :: Reserva
r6 = confirmarR r5

testRD6 = TestCase (assertEqual "Test Documento Reserva6:" (documentoR r6) (37654321))
testRFD6 = TestCase (assertEqual "Test Fecha Desde Reserva6:" (fechaDesdeR r6) (4))
testRFH6 = TestCase (assertEqual "Test Fecha Hasta Reserva6: " (fechaHastaR r6) (7))
testRT6 = TestCase (assertEqual "Test Tipo Reserva6: " (tipoR r6) (Doble))
testRC6 = TestCase (assertEqual "Test Confirmada Reserva6: " (confirmadaR r6) (True))

r7 :: Reserva
r7 = nuevaR 30100200 6 9 Doble

testRD7 = TestCase (assertEqual "Test Documento Reserva7:" (documentoR r7) (30100200))
testRFD7 = TestCase (assertEqual "Test Fecha Desde Reserva7:" (fechaDesdeR r7) (6))
testRFH7 = TestCase (assertEqual "Test Fecha Hasta Reserva7: " (fechaHastaR r7) (9))
testRT7 = TestCase (assertEqual "Test Tipo Reserva7: " (tipoR r7) (Doble))
testRC7 = TestCase (assertEqual "Test Confirmada Reserva7: " (confirmadaR r7) (False))

r8 :: Reserva
r8 = confirmarR r7

testRD8 = TestCase (assertEqual "Test Documento Reserva8:" (documentoR r8) (30100200))
testRFD8 = TestCase (assertEqual "Test Fecha Desde Reserva8:" (fechaDesdeR r8) (6))
testRFH8 = TestCase (assertEqual "Test Fecha Hasta Reserva8: " (fechaHastaR r8) (9))
testRT8 = TestCase (assertEqual "Test Tipo Reserva8: " (tipoR r8) (Doble))
testRC8 = TestCase (assertEqual "Test Confirmada Reserva8: " (confirmadaR r8) (True))

r9 :: Reserva
r9 = nuevaR 30100201 6 9 Doble

r10 :: Reserva
r10 = nuevaR 30100200 7 8 Doble

--Habitaciones
h1 :: Habitacion
h1 = nuevaH 1 Simple []

testHbN1 = TestCase (assertEqual "Test Numero Habitacion1:" (numeroH h1) (1))
testHbT1 = TestCase (assertEqual "Test Tipo Habitacion1:" (tipoH h1) (Simple))
testHbA1 = TestCase (assertEqual "Test Accesorios Habitacion1:" (accesoriosH h1) ([]))

h2 :: Habitacion
h2 = nuevaH 2 Doble []

testHbN2 = TestCase (assertEqual "Test Numero Habitacion2:" (numeroH h2) (2))
testHbT2 = TestCase (assertEqual "Test Tipo Habitacion2:" (tipoH h2) (Doble))
testHbA2 = TestCase (assertEqual "Test Accesorios Habitacion2:" (accesoriosH h2) ([]))

h3 :: Habitacion
h3 = nuevaH 3 Triple []

testHbN3 = TestCase (assertEqual "Test Numero Habitacion3:" (numeroH h3) (3))
testHbT3 = TestCase (assertEqual "Test Tipo Habitacion3:" (tipoH h3) (Triple))
testHbA3 = TestCase (assertEqual "Test Accesorios Habitacion3:" (accesoriosH h3) ([]))

h4 :: Habitacion
h4 = nuevaH 4 Cuadruple []

testHbN4 = TestCase (assertEqual "Test Numero Habitacion4:" (numeroH h4) (4))
testHbT4 = TestCase (assertEqual "Test Tipo Habitacion4:" (tipoH h4) (Cuadruple))
testHbA4 = TestCase (assertEqual "Test Accesorios Habitacion4:" (accesoriosH h4) ([]))

h5 :: Habitacion
h5 = nuevaH 5 Doble [Jacuzzi,LCD,PS3]

testHbN5 = TestCase (assertEqual "Test Numero Habitacion5:" (numeroH h5) (5))
testHbT5 = TestCase (assertEqual "Test Tipo Habitacion5:" (tipoH h5) (Doble))
testHbA5 = TestCase (assertEqual "Test Accesorios Habitacion5:" (accesoriosH h5) ([Jacuzzi,LCD,PS3]))

h6 :: Habitacion
h6 = nuevaH 6 Triple [Pelotero]

testHbN6 = TestCase (assertEqual "Test Numero Habitacion6:" (numeroH h6) (6))
testHbT6 = TestCase (assertEqual "Test Tipo Habitacion6:" (tipoH h6) (Triple))
testHbA6 = TestCase (assertEqual "Test Accesorios Habitacion6:" (accesoriosH h6) ([Pelotero]))

h7 :: Habitacion
h7 = nuevaH 7 Cuadruple [Jacuzzi,LCD,PS3,DVD,Pelotero,Inflable]

testHbN7 = TestCase (assertEqual "Test Numero Habitacion7:" (numeroH h7) (7))
testHbT7 = TestCase (assertEqual "Test Tipo Habitacion7:" (tipoH h7) (Cuadruple))
testHbA7 = TestCase (assertEqual "Test Accesorios Habitacion7:" (accesoriosH h7) ([Jacuzzi,LCD,PS3,DVD,Pelotero,Inflable]))

--Listas de Accesorios
listaA1 :: [Accesorio]
listaA1 = [Pelotero]

listaA2 :: [Accesorio]
listaA2 = [Jacuzzi,LCD,PS3,DVD,Pelotero,Inflable]

listaA3 :: [Accesorio]
listaA3 = [Jacuzzi,Pelotero]

listaA4 :: [Accesorio]
listaA4 = []

--Listas de habitaciones
listaH1 :: [Habitacion]
listaH1 = [h1,h2,h3,h4,h5,h6]

--Pretensiones de PopStar
testPPS1 = TestCase (assertEqual "Test Pretensiones de PopStar1:" (mismasHabitaciones (pretensionesDePopStarH listaA1 listaH1) [h6]) (True))
testPPS2 = TestCase (assertEqual "Test Pretensiones de PopStar2:" (mismasHabitaciones (pretensionesDePopStarH listaA2 listaH1) [h5]) (True))
testPPS3 = TestCase (assertEqual "Test Pretensiones de PopStar3:" (mismasHabitaciones (pretensionesDePopStarH listaA3 listaH1) [h5,h6]) (True))
testPPS4 = TestCase (assertEqual "Test Pretensiones de PopStar4:" (mismasHabitaciones (pretensionesDePopStarH listaA4 listaH1) [h1,h2,h3,h4,h5,h6]) (True))

--nuevoH :: Nombre -> Cadena -> [Habitacion] -> [(TipoHabitacion, Dinero)] -> [(Accesorio, Dinero)] -> Hotel
--Hoteles
ht1 :: Hotel
ht1 = nuevoH "Hotel1" "CheRaton" [h1,h2,h5] [(Simple, 1),(Doble,2),(Triple,3),(Cuadruple,4)] [(Jacuzzi,10),(LCD,20),(PS3,40)]

testHtN1 = TestCase (assertEqual "Test Nombre Hotel1:" (nombreH ht1) ("Hotel1"))
testHtC1 = TestCase (assertEqual "Test Cadena Hotel1:" (cadenaH ht1) ("CheRaton"))
testHtHu1 = TestCase (assertEqual "Test Huespedes Hotel1:" (mismosDocumentos (huespedesH ht1) ([])) (True))
testHtHab1 = TestCase (assertEqual "Test Habitaciones Hotel1:" (mismasHabitaciones (habitacionesH ht1) [h1,h2,h5]) (True))
testHtI1 = TestCase (assertEqual "Test Ingresos Hotel1:" (mismosIngresos (ingresosH ht1) ([])) (True))
testHtS1 = TestCase (assertEqual "Test Salidas Hotel1:" (mismosCheckOuts (salidasH ht1) ([])) (True))
testHtR1 = TestCase (assertEqual "Test Reservas Hotel1:" (mismasReservas (reservasH ht1) ([])) (True))
testHtT1 = TestCase (assertEqual "Test Tarifa Habitacion Hotel1:" (tarifaXDiaH ht1 Triple) (3))
testHtA1 = TestCase (assertEqual "Test Precio Accesorio Hotel1:" (precioAccesorioH ht1 Jacuzzi) (10))

ht2 :: Hotel
ht2 = hacerReservaH ht1 r2

ht3 :: Hotel
ht3 = hacerReservaH ht2 r3

ht4 :: Hotel
ht4 = hacerReservaH ht3 r5

ht5 :: Hotel
ht5 = hacerReservaH ht4 r7

testHtHu5 = TestCase (assertEqual "Test Huespedes Hotel5:" (mismosDocumentos (huespedesH ht5) ([])) (True))
testHtI5 = TestCase (assertEqual "Test Ingresos Hotel5:" (mismosIngresos (ingresosH ht5) ([])) (True))
testHtS5 = TestCase (assertEqual "Test Salidas Hotel5:" (mismosCheckOuts (salidasH ht5) ([])) (True))
testHtR5 = TestCase (assertEqual "Test Reservas Hotel5:" (mismasReservas (reservasH ht5) ([r2,r3,r5,r7])) (True))

ht6 :: Hotel
ht6 = registrarHuespedH ht5 33444555 3 h5

ht7 :: Hotel
ht7 = registrarHuespedH ht6 37654321 4 h2

ht8 :: Hotel
ht8 = desregistrarHuespedH ht7 33444555 5

ht9 :: Hotel
ht9 = registrarHuespedH ht8 30100200 6 h5

testHtHu9 = TestCase (assertEqual "Test Huespedes Hotel9:" (mismosDocumentos (huespedesH ht9) ([37654321,30100200])) (True))
testHtI9 = TestCase (assertEqual "Test Ingresos Hotel9:" (mismosIngresos (ingresosH ht9) ([((33444555,3),h5),((37654321,4),h2),((30100200,6),h5)])) (True))
testHtS9 = TestCase (assertEqual "Test Salidas Hotel9:" (mismosCheckOuts (salidasH ht9) ([(33444555,5)])) (True))
testHtR9 = TestCase (assertEqual "Test Reservas Hotel9:" (mismasReservas (reservasH ht9) ([r2,r4,r6,r8])) (True))

ht10 :: Hotel
ht10 = desregistrarHuespedH ht9 30100200 7

testHtHu10 = TestCase (assertEqual "Test Huespedes Hotel10:" (mismosDocumentos (huespedesH ht10) ([37654321])) (True))
testHtI10 = TestCase (assertEqual "Test Ingresos Hotel10:" (mismosIngresos (ingresosH ht10) ([((33444555,3),h5),((37654321,4),h2),((30100200,6),h5)])) (True))
testHtS10 = TestCase (assertEqual "Test Salidas Hotel10:" (mismosCheckOuts (salidasH ht10) ([(33444555,5),(30100200,7)])) (True))
testHtR10 = TestCase (assertEqual "Test Reservas Hotel10:" (mismasReservas (reservasH ht10) ([r2,r4,r6,r8])) (True))

ht11 :: Hotel
ht11 = venderH ht1 "FourScissors"

ht12 :: Hotel
ht12 = hacerReservaH ht5 r9

ht13 :: Hotel
ht13 = hacerReservaH ht5 r10

ht14 :: Hotel
ht14 = nuevoH "Hotel1" "CheRaton" [] [] []

ht15 :: Hotel
ht15 = nuevoH "Hotel2" "FourScissors" [] [] []

ht16 :: Hotel
ht16 = nuevoH "Hotel2" "CheRaton" [] [] []

ht17 :: Hotel
ht17 = nuevoH "Hotel3" "CheRaton" [] [] []

-- Vender
testVender = TestCase (assertEqual "Test Vender Cadena Hotel11:" (cadenaH ht11) ("FourScissors"))

-- Sobrereservado
testSobreReservado1 = TestCase (assertEqual "Test SobreReservado 1 Hotel12:" (sobreReservadoH ht12 5) (False))
testSobreReservado2 = TestCase (assertEqual "Test SobreReservado 2 Hotel12:" (sobreReservadoH ht12 6) (True))

-- Huespedes con Palabra
testHuespedesConPalabra = TestCase (assertEqual "Test HuespedesConPalabra Hotel10:" (mismosDocumentos (huespedesConPalabraH ht10) [33444555]) (True)) 

-- Calcular Cuenta
testCalcularCuenta = TestCase (assertEqual "Test Calcular Cuenta Hotel9:" (calcularCuentaH ht9 (33444555,3) (33444555,5) h5) (74))

-- Reservas Solapadas
testReservasSolapadas1 = TestCase (assertEqual "Test Reservas Solapadas 1 Hotel13:" (reservasSolapadasH ht13 33444555) (False))
testReservasSolapadas2 = TestCase (assertEqual "Test Reservas Solapadas 2 Hotel13:" (reservasSolapadasH ht13 30100200) (True))


-- Ministerio
m1 :: Ministerio
m1 = nuevoM ["TheShire","Mordor"]

m2 :: Ministerio
m2 = agregarHotelM m1 ht14 "TheShire"

m3 :: Ministerio
m3 = agregarHotelM m2 ht15 "Mordor"

m4 :: Ministerio
m4 = agregarHotelM m2 ht16 "Mordor"

m5 :: Ministerio
m5 = agregarHotelM m3 ht17 "Mordor"

-- Cadenas Amarretas
testCadenasAmarretas = TestCase (assertEqual "Test Cadenas Amarretas:" (cadenasAmarretasM m5) (["FourScissors"]))

-- Fusion Autorizada
testFusionAutorizada = TestCase (assertEqual "Test Fusion Autorizada:" (mismasSecretarias (secretariasM (fusionAutorizadaM m3 "CheRaton" "FourScissors")) ["TheShire","Mordor"]
																	&&  mismosRegistrosM (fusionAutorizadaM m3 "CheRaton" "FourScissors") "TheShire" [ht14]
																	&&  mismasCadenasM (fusionAutorizadaM m3 "CheRaton" "FourScissors") [[ht14,ht16]] ) (True))

tests = TestList [	TestLabel "testRD1" testRD1,
					TestLabel "testRFD1" testRFD1,
					TestLabel "testRFH1" testRFH1,
					TestLabel "testRT1" testRT1,
					TestLabel "testRC1" testRC1,
					TestLabel "testRD2" testRD2,
					TestLabel "testRFD2" testRFD2,
					TestLabel "testRFH2" testRFH2,
					TestLabel "testRT2" testRT2,
					TestLabel "testRC2" testRC2,
					TestLabel "testRD3" testRD3,
					TestLabel "testRFD3" testRFD3,
					TestLabel "testRFH3" testRFH3,
					TestLabel "testRT3" testRT3,
					TestLabel "testRC3" testRC3,
					TestLabel "testRD4" testRD4,
					TestLabel "testRFD4" testRFD4,
					TestLabel "testRFH4" testRFH4,
					TestLabel "testRT4" testRT4,
					TestLabel "testRC4" testRC4,
					TestLabel "testRD5" testRD5,
					TestLabel "testRFD5" testRFD5,
					TestLabel "testRFH5" testRFH5,
					TestLabel "testRT5" testRT5,
					TestLabel "testRC5" testRC5,
					TestLabel "testRD6" testRD6,
					TestLabel "testRFD6" testRFD6,
					TestLabel "testRFH6" testRFH6,
					TestLabel "testRT6" testRT6,
					TestLabel "testRC6" testRC6,
					TestLabel "testRD7" testRD7,
					TestLabel "testRFD7" testRFD7,
					TestLabel "testRFH7" testRFH7,
					TestLabel "testRT7" testRT7,
					TestLabel "testRC7" testRC7,
					TestLabel "testRD8" testRD8,
					TestLabel "testRFD8" testRFD8,
					TestLabel "testRFH8" testRFH8,
					TestLabel "testRT8" testRT8,
					TestLabel "testRC8" testRC8,
					
					TestLabel "testHbN1" testHbN1,
					TestLabel "testHbT1" testHbT1,
					TestLabel "testHbA1" testHbA1,
					TestLabel "testHbN2" testHbN2,
					TestLabel "testHbT2" testHbT2,
					TestLabel "testHbA2" testHbA2,
					TestLabel "testHbN3" testHbN3,
					TestLabel "testHbT3" testHbT3,
					TestLabel "testHbA3" testHbA3,
					TestLabel "testHbN4" testHbN4,
					TestLabel "testHbT4" testHbT4,
					TestLabel "testHbA4" testHbA4,
					TestLabel "testHbN5" testHbN5,
					TestLabel "testHbT5" testHbT5,
					TestLabel "testHbA5" testHbA5,
					TestLabel "testHbN6" testHbN6,
					TestLabel "testHbT6" testHbT6,
					TestLabel "testHbA6" testHbA6,
					TestLabel "testHbN7" testHbN7,
					TestLabel "testHbT7" testHbT7,
					TestLabel "testHbA7" testHbA7,
					
					TestLabel "testPPS1" testPPS1,
					TestLabel "testPPS2" testPPS2,
					TestLabel "testPPS3" testPPS3,
					TestLabel "testPPS4" testPPS4,

					TestLabel "testHtN1" testHtN1,
					TestLabel "testHtC1" testHtC1,
					TestLabel "testHtHu1" testHtHu1,
					TestLabel "testHtHab1" testHtHab1,
					TestLabel "testHtI1" testHtI1,
					TestLabel "testHtS1" testHtS1,
					TestLabel "testHtR1" testHtR1,
					TestLabel "testHtT1" testHtT1,
					TestLabel "testHtA1" testHtA1,
					TestLabel "testHtHu5" testHtHu5,
					TestLabel "testHtI5" testHtI5,
					TestLabel "testHtS5" testHtS5,
					TestLabel "testHtR5" testHtR5,
					TestLabel "testHtHu9" testHtHu9,
					TestLabel "testHtI9" testHtI9,
					TestLabel "testHtS9" testHtS9,
					TestLabel "testHtR9" testHtR9,
					TestLabel "testHtHu10" testHtHu10,
					TestLabel "testHtI10" testHtI10,
					TestLabel "testHtS10" testHtS10,
					TestLabel "testHtR10" testHtR10,

					TestLabel "testVender" testVender,

					TestLabel "testSobreReservado1" testSobreReservado1,
					TestLabel "testSobreReservado2" testSobreReservado2,

					TestLabel "testHuespedesConPalabra" testHuespedesConPalabra,

					TestLabel "testCalcularCuenta" testCalcularCuenta,
					TestLabel "testReservasSolapadas1" testReservasSolapadas1,
					TestLabel "testReservasSolapadas2" testReservasSolapadas2,
					
					TestLabel "testCadenasAmarretas" testCadenasAmarretas,

					TestLabel "testFusionAutorizada" testFusionAutorizada]
main = do runTestTT tests
