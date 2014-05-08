module Hotel (Hotel, sobreReservadoH, huespedesConPalabraH, nuevoH,
		nombreH, cadenaH, ingresosH, salidasH, huespedesH, reservasH, habitacionesH,
		tarifaXDiaH, precioAccesorioH, registrarHuespedH, desregistrarHuespedH, hacerReservaH,
		calcularCuentaH, reservasSolapadasH, venderH)
where

import Tipos
import Auxiliares
import Habitacion
import Reserva
import List

data Hotel = HT Nombre Cadena [Habitacion] [(TipoHabitacion, Dinero)] [(Accesorio, Dinero)]
			| CI DNI Fecha Habitacion Hotel
			| CO DNI Fecha Hotel
			| R Reserva Hotel
				deriving (Show)

-- Observadores
-------------------------------------------------------------------

nombreH :: Hotel -> Nombre
nombreH (HT nom _ _ _ _) 						= nom
nombreH (CI _ _ _ h) 							= nombreH h
nombreH (CO _ _ h) 								= nombreH h
nombreH (R _ h) 								= nombreH h

cadenaH :: Hotel -> Cadena
cadenaH (HT _ cad _ _ _) 						= cad
cadenaH (CI _ _ _ h) 							= cadenaH h
cadenaH (CO _ _ h) 								= cadenaH h
cadenaH (R _ h) 								= cadenaH h

ingresosH :: Hotel -> [(CheckIn, Habitacion)]
ingresosH (HT _ _ _ _ _) 						= []
ingresosH (CI d f hb h) 						= (ingresosH h) ++ [((d,f),hb)]
ingresosH (CO _ _ h) 							= ingresosH h
ingresosH (R _ h) 								= ingresosH h

ingresosDeH :: Hotel -> DNI -> [CheckIn]
ingresosDeH  (HT _ _ _ _ _) _					= []
ingresosDeH  (CI d f hb h) 	dni					 
				| dni == d 						= (ingresosDeH h dni) ++ [(d,f)]
				| otherwise 					= ingresosDeH h dni
ingresosDeH  (CO _ _ h) 	dni					= ingresosDeH h dni
ingresosDeH  (R _ h) 		dni					= ingresosDeH h dni

salidasH :: Hotel -> [CheckOut]
salidasH (HT _ _ _ _ _) 						= []
salidasH (CI _ _ _ h) 							= salidasH h
salidasH (CO d f h) 							= (salidasH h) ++ [(d,f)]
salidasH (R _ h) 								= salidasH h

salidasDeH :: Hotel -> DNI -> [CheckOut]
salidasDeH (HT _ _ _ _ _)	_ 					= []
salidasDeH (CI _ _ _ h) 	dni 				= salidasDeH h dni
salidasDeH (CO d f h)   	dni
				| dni == d 						= (salidasDeH h dni) ++ [(d,f)]
				| otherwise 					= salidasDeH h dni
salidasDeH (R _ h) 			dni 				= salidasDeH h dni

huespedesH :: Hotel -> [DNI]
huespedesH h 									= huespedesHAux h []

--	{TODO} COMENTAR O IMPLEMENTAR DE FORMA MÁS DECLARATIVA..
huespedesHAux :: Hotel -> [DNI] -> [DNI]
huespedesHAux (HT _ _ _ _ _) 	hs				= hs
huespedesHAux (CI d _ _ h) 		hs	
							| d `elem` hs 		= huespedesHAux h (sacarHuesped d hs)
							| otherwise 		= huespedesHAux h (d:hs)
huespedesHAux (CO d _ h) 		hs
							| d `elem` hs 		= huespedesHAux h (sacarHuesped d hs)
							| otherwise 		= huespedesHAux h (d:hs)
huespedesHAux (R _ h) 			hs				= huespedesHAux h hs

sacarHuesped :: DNI -> [DNI] -> [DNI]
sacarHuesped _ [] 								= []
sacarHuesped d (od:ds)
				| d /= od 						= od:(sacarHuesped d ds)
				| otherwise 					= sacarHuesped d ds

reservasH :: Hotel -> [Reserva]
reservasH (HT _ _ _ _ _) 						= []
reservasH (CI _ _ _ h) 							= reservasH h
reservasH (CO _ _ h) 							= reservasH h
reservasH (R r h) 								= (reservasH h) ++ [r]

habitacionesH :: Hotel -> [Habitacion]
habitacionesH (HT _ _ hbs _ _) 					= hbs
habitacionesH (CI _ _ _ h) 						= habitacionesH h
habitacionesH (CO _ _ h) 						= habitacionesH h
habitacionesH (R _ h) 							= habitacionesH h

tarifaXDiaH :: Hotel -> TipoHabitacion -> Dinero
tarifaXDiaH (HT _ _ _ tfs _) th					= companieroDeTupla th tfs
tarifaXDiaH (CI _ _ _ h) th 					= tarifaXDiaH h th
tarifaXDiaH (CO _ _ h) th 						= tarifaXDiaH h th
tarifaXDiaH (R _ h) th 							= tarifaXDiaH h th

precioAccesorioH :: Hotel -> Accesorio -> Dinero
precioAccesorioH (HT _ _ _ _ acs) a				= companieroDeTupla a acs
precioAccesorioH (CI _ _ _ h) a 				= precioAccesorioH h a
precioAccesorioH (CO _ _ h) a 					= precioAccesorioH h a
precioAccesorioH (R _ h) a 						= precioAccesorioH h a

companieroDeTupla :: (Eq a) => a -> [(a,b)] -> b
companieroDeTupla _ [] = error "Error en función companieroDeTupla: ninguna tupla en la lista contiene al elemento buscado como primera componente."
companieroDeTupla e (t:ts)
				| e == (fst t) 		= snd t
				| otherwise 		= companieroDeTupla e ts

-- SobreReservadoH
-------------------------------------------------------------------

sobreReservadoH :: Hotel -> Fecha -> Bool
sobreReservadoH h f =  (capacidadH h) < (plazasReservadas h f)

plazasReservadas :: Hotel -> Fecha -> Int
plazasReservadas (HT _ _ _ _ _) f 				= 0
plazasReservadas (CI _ _ _ h) f 				= plazasReservadas h f
plazasReservadas (CO _ _ h) f 					= plazasReservadas h f
plazasReservadas (R r h) f 						
	| reservaIncluyeFecha r f  	= (capacidadHabitacion (tipoR r)) + plazasReservadas h f
	| otherwise 				= plazasReservadas h f

reservaIncluyeFecha :: Reserva -> Fecha -> Bool
reservaIncluyeFecha r f 						= (desde <= f) && (f <= hasta)
			where
				desde = fechaDesdeR	r
				hasta = fechaHastaR	r

capacidadH :: Hotel -> Int
capacidadH h 									= capacidadHAux (habitacionesH h)

capacidadHAux :: [Habitacion] -> Int
capacidadHAux [] 					= 0
capacidadHAux (hb:hbs)				= capacidadHabitacion (tipoH hb) + capacidadHAux hbs

capacidadHabitacion :: TipoHabitacion -> Int
capacidadHabitacion	Simple						= 1
capacidadHabitacion	Doble						= 2
capacidadHabitacion	Triple						= 3
capacidadHabitacion	Cuadruple					= 4

-- HuespedesConPalabraH
-------------------------------------------------------------------

huespedesConPalabraH :: Hotel -> [DNI]
huespedesConPalabraH h = huespedesConPalabraHAux h []

huespedesConPalabraHAux :: Hotel -> [DNI] -> [DNI]
huespedesConPalabraHAux (HT _ _ _ _ _) ds 		= sacarRepetidos ds
huespedesConPalabraHAux (CI _ _ _ h) ds 		= huespedesConPalabraHAux h ds
huespedesConPalabraHAux (CO d f h) ds 			
		| existeReservaConsistente h i co	 	= huespedesConPalabraHAux h (d:ds)
		| otherwise 							= huespedesConPalabraHAux h ds
			where
				co = (d,f)
				i = obtenerIngresoAsociado h co
huespedesConPalabraHAux (R _ h) ds 				= huespedesConPalabraHAux h ds

obtenerIngresoAsociado :: Hotel -> CheckOut -> (CheckIn,Habitacion)
obtenerIngresoAsociado (HT _ _ _ _ _) co 		= error "Error en función obtenerIngresoAsociado: existe un CheckOut sin un CheckIn asociado"
obtenerIngresoAsociado (CI d f hb h) co
	| (dni == d) && (f < fechaHasta)			= ((d,f),hb)
	| otherwise 								= obtenerIngresoAsociado h co
		where
			dni = fst co
			fechaHasta = snd co
obtenerIngresoAsociado (CO _ _ h) co 			= obtenerIngresoAsociado h co
obtenerIngresoAsociado (R _ h) co 				= obtenerIngresoAsociado h co

existeReservaConsistente :: Hotel-> (CheckIn,Habitacion) -> CheckOut -> Bool
existeReservaConsistente (HT _ _ _ _ _) i co 		= False
existeReservaConsistente (CI _ _ _ h) i co 			= existeReservaConsistente h i co
existeReservaConsistente (CO _ _ h) i co 			= existeReservaConsistente h i co
existeReservaConsistente (R r h) i co
	| ingDeReserva && coDeReserva				= True
	| otherwise 								= existeReservaConsistente h i co
		where
			dniIng = fst (fst i)
			fechaIng = snd (fst i)
			tipoHabIng = tipoH (snd i)
			dniCo = fst co
			fechaCo = snd co
			ingDeReserva = (dniIng == documentoR r) && (fechaIng == fechaDesdeR r) &&
							 (tipoHabIng == tipoR r)
			coDeReserva = (documentoR r == dniCo) && (fechaCo == fechaHastaR r)

-- NuevoH
-------------------------------------------------------------------

nuevoH :: Nombre -> Cadena -> [Habitacion] -> [(TipoHabitacion, Dinero)] -> [(Accesorio, Dinero)] -> Hotel
nuevoH nom cad hbs tfs acs 						= HT nom cad hbs tfs acs

-- RegistrarHuespedH
-------------------------------------------------------------------

registrarHuespedH :: Hotel -> DNI -> Fecha -> Habitacion -> Hotel
registrarHuespedH h d f a 						= CI d f a hConReservaConfirmada
	where
		tipoDeHb = tipoH a
		checkIn  = (d,f)
		ingreso  = (checkIn, tipoDeHb)
		hConReservaConfirmada = confirmarReservaDelIngreso h ingreso

confirmarReservaDelIngreso :: Hotel -> (CheckIn,TipoHabitacion) -> Hotel
confirmarReservaDelIngreso (HT _ _ _ _ _) _ 	= error "Error en función confirmarReservaDelIngreso: se intentó registrar un ingreso para el cual no existía Reserva."
confirmarReservaDelIngreso (CI d f hb h) i 		= CI d f hb (confirmarReservaDelIngreso h i)
confirmarReservaDelIngreso (CO d f h) i 		= CO d f (confirmarReservaDelIngreso h i)
confirmarReservaDelIngreso (R r h) i
			| reservaAsociadaAIngreso r i		= R (confirmarR r) h
			| otherwise 						= R r (confirmarReservaDelIngreso h i)

reservaAsociadaAIngreso :: Reserva -> (CheckIn,TipoHabitacion) -> Bool
reservaAsociadaAIngreso r ((d,f),th)
		| (dni == d) && (desde == f) && (tipo == th) 	= True
		| otherwise 									= False
			where
				dni 	= documentoR r
				desde 	= fechaDesdeR r
				tipo 	= tipoR r

-- DesregistrarHuespedH
-------------------------------------------------------------------

desregistrarHuespedH :: Hotel -> DNI -> Fecha -> Hotel
desregistrarHuespedH h d f			= CO d f h

-- HacerReservaH
-------------------------------------------------------------------

hacerReservaH :: Hotel -> Reserva -> Hotel
hacerReservaH h r 					= R r h

-- CalcularCuentaH
-------------------------------------------------------------------

calcularCuentaH :: Hotel -> CheckIn -> CheckOut -> Habitacion -> Dinero
calcularCuentaH h ci co hb =  
	 (alquilerDeAccesorios h (accesoriosH hb)) + (dias ci co)*(tarifaXDiaH h (tipoH hb))

alquilerDeAccesorios :: Hotel -> [Accesorio] -> Dinero
alquilerDeAccesorios _ []			= 0
alquilerDeAccesorios h (a:as) 		= (precioAccesorioH h a) + (alquilerDeAccesorios h as)

dias :: CheckIn -> CheckOut -> Int
dias ci co 							= (snd co) - (snd ci)

-- ReservasSolapadasH
-------------------------------------------------------------------

reservasSolapadasH :: Hotel -> DNI -> Bool
reservasSolapadasH h d 			= not (sinRepetidos (diasDeReservas (reservasDe h d)))

reservasDe :: Hotel -> DNI -> [Reserva]
reservasDe h d 									= reservasDeAux (reservasH h) d

reservasDeAux :: [Reserva] -> DNI -> [Reserva]
reservasDeAux [] _ 								= []
reservasDeAux (r:rs) d
				| (documentoR r) == d 			= r:(reservasDeAux rs d)
				| otherwise						= reservasDeAux rs d

diasDeReservas :: [Reserva] -> [Fecha]
diasDeReservas [] = []
diasDeReservas (r:rs) 							= diasDeReserva r ++ diasDeReservas rs

diasDeReserva :: Reserva -> [Fecha]
diasDeReserva r 								= diasDeReservaAux r []

diasDeReservaAux :: Reserva -> [Fecha] -> [Fecha]
diasDeReservaAux r [] 							= diasDeReservaAux r [fechaDesdeR r]
diasDeReservaAux r fs 
				| f < (fechaHastaR r)			= diasDeReservaAux r (fs++[f+1])
				| otherwise 					= fs
					where f = last fs

-- VenderH
-------------------------------------------------------------------

venderH :: Hotel -> Cadena -> Hotel
venderH (HT n c hbs tfs acs) nc 			= (HT n nc hbs tfs acs)
venderH (CI d f hb h) nc 					= (CI d f hb (venderH h nc))
venderH (CO d f h) nc 						= (CO d f (venderH h nc))
venderH (R r h) nc 							= (R r (venderH h nc))