module Habitacion (Habitacion, nuevaH, numeroH, tipoH,
 accesoriosH, pretensionesDePopStarH) where

import Tipos
import Auxiliares

data Habitacion = A Accesorio Habitacion
				 | H Int TipoHabitacion
				 		deriving (Show)

-- Observadores
------------------------------------------------------------------

numeroH :: Habitacion -> Int
numeroH (H num _) = num
numeroH (A a hb) = numeroH hb

tipoH :: Habitacion -> TipoHabitacion
tipoH (H _ tipo) = tipo
tipoH (A a hb) = tipoH hb

accesoriosH :: Habitacion -> [Accesorio]
accesoriosH (H _ _) = []
accesoriosH (A a hb) =  accesoriosH hb ++ [a]

-- NuevaH
------------------------------------------------------------------

nuevaH :: Int -> TipoHabitacion -> [Accesorio] -> Habitacion
nuevaH _ _ as
	| ((estrictamenteCreciente as) == False) = error "Error en función nuevaH: la lista de accesorios recibida no cumple la especificación."
nuevaH num tipo as = agregarAccs (H num tipo) as

estrictamenteCreciente :: [Accesorio] -> Bool
estrictamenteCreciente as | length as <= 1 = True
estrictamenteCreciente (a:as) = (a < (head as)) && (estrictamenteCreciente as)

agregarAccs :: Habitacion -> [Accesorio] -> Habitacion
agregarAccs hb [] = hb
agregarAccs hb (a:as) = agregarAccs (A a hb) as

-- PretensionesDePopStarH
------------------------------------------------------------------

pretensionesDePopStarH :: [Accesorio] -> [Habitacion] -> [Habitacion]
pretensionesDePopStarH as hbs 	= pretensionesDePopStarHAux as hbs []

pretensionesDePopStarHAux :: [Accesorio] -> [Habitacion] -> [Habitacion] -> [Habitacion]
pretensionesDePopStarHAux as [] res 		= res
pretensionesDePopStarHAux as (h:hbs) [] 	= pretensionesDePopStarHAux as hbs [h]
pretensionesDePopStarHAux as (h:hbs) res
			| cantAccsEnH > maxCantAccs 	= pretensionesDePopStarHAux as hbs [h]
			| cantAccsEnH == maxCantAccs 	= pretensionesDePopStarHAux as hbs (h:res)
			| cantAccsEnH < maxCantAccs 	= pretensionesDePopStarHAux as hbs res
				where
					cantAccsEnH = accesoriosPresentes as h
					maxCantAccs = accesoriosPresentes as (head res)

accesoriosPresentes :: [Accesorio] -> Habitacion -> Int
accesoriosPresentes [] hb = 0
accesoriosPresentes (a:as) hb
			| (a `elem` (accesoriosH hb)) = 1 + (accesoriosPresentes as hb)
			| otherwise = accesoriosPresentes as hb