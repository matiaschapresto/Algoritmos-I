module Ministerio (Ministerio, agregarHotelM, secretariasM,
 registroM, nuevoM, cadenasDeHotelesM, cadenasAmarretasM, fusionAutorizadaM)
where

import Tipos
import Auxiliares
import Reserva
import Habitacion
import Hotel

data Ministerio = REG Provincia Hotel Ministerio 
				 | MT [Provincia]
				 	deriving (Show)

-- Observadores
---------------------------------------------------------------------
secretariasM :: Ministerio -> [Provincia]
secretariasM (MT ps)				= ps
secretariasM (REG pr h m) 			= secretariasM m

registroM :: Ministerio -> Provincia -> [Hotel]
registroM (MT _) _ 					=  []
registroM (REG pr h m) p 		
					| p == pr 		= (registroM m p) ++ [h]
					| otherwise		= registroM m p

cadenasDeHotelesM :: Ministerio -> [[Hotel]]
cadenasDeHotelesM m =  cadenasDeHotelesMAux m (nombresDeCadenas m)

nombresDeCadenas :: Ministerio -> [Cadena]
nombresDeCadenas (MT _) 						=  []
nombresDeCadenas (REG pr h m)
			| not ( (cadenaH h) `elem` cs) 		= (cadenaH h):cs
			| otherwise 						= cs
				where cs = nombresDeCadenas m

cadenasDeHotelesMAux :: Ministerio -> [Cadena] ->[[Hotel]]
cadenasDeHotelesMAux _ [] 		= []
cadenasDeHotelesMAux m (c:cs)	= (hotelesDeCadena m c) : cadenasDeHotelesMAux m cs

hotelesDeCadena ::  Ministerio -> Cadena ->[Hotel]
hotelesDeCadena (MT _)	_						= []
hotelesDeCadena (REG p h m) c
						| (cadenaH h) == c 		= (hotelesDeCadena m c) ++ [h]
						| otherwise 			= hotelesDeCadena m c

-- AgregarHotelM
---------------------------------------------------------------------
agregarHotelM :: Ministerio -> Hotel -> Provincia -> Ministerio
agregarHotelM m h p = REG p h m

-- NuevoM
---------------------------------------------------------------------
nuevoM :: [Provincia] -> Ministerio
nuevoM ps =  MT ps

-- CadenasAmarretasM
---------------------------------------------------------------------
cadenasAmarretasM :: Ministerio -> [Cadena]
cadenasAmarretasM m 						= cadenasAmarretasMAux m (nombresDeCadenas m) []

cadenasAmarretasMAux :: Ministerio -> [Cadena] -> [Cadena] -> [Cadena]
cadenasAmarretasMAux _ [] res 				= res
cadenasAmarretasMAux m (c:cs) [] 			= [c]
cadenasAmarretasMAux m (c:cs) res
				| provsEnC < minProvs		= cadenasAmarretasMAux m cs [c]
				| provsEnC == minProvs		= cadenasAmarretasMAux m cs (c:res)
				| provsEnC > minProvs		= cadenasAmarretasMAux m cs res
					where
						provsEnC = cantProvinciasEnCadena m c
						minProvs = cantProvinciasEnCadena m (head res)

cantProvinciasEnCadena :: Ministerio -> Cadena -> Int
cantProvinciasEnCadena m c 					= length (provinciasEnCadena m c)

provinciasEnCadena :: Ministerio -> Cadena -> [Provincia]
provinciasEnCadena m c 						= provinciasEnCadenaAux m c []

provinciasEnCadenaAux :: Ministerio -> Cadena -> [Provincia] -> [Provincia]
provinciasEnCadenaAux (MT _) _ ps 			= sacarRepetidos ps
provinciasEnCadenaAux (REG p h m) c ps
			| (cadenaH h) == c 				= provinciasEnCadenaAux m c (p:ps)
			| otherwise						= provinciasEnCadenaAux m c ps

-- FusionAutorizadaM
---------------------------------------------------------------------
fusionAutorizadaM :: Ministerio -> Cadena -> Cadena -> Ministerio
fusionAutorizadaM (REG p h m) c1 c2
		| (cadenaH h) == c2 				= (REG p hEnC1 (fusionAutorizadaM m c1 c2))
		| otherwise							= (REG p h (fusionAutorizadaM m c1 c2))
			where
				hEnC1 = venderH h c1
fusionAutorizadaM m _ _						= m
