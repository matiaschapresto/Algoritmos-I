module Tipos where

type Fecha = Int
type DNI = Int
type Dinero = Int
type Cadena = String
type Nombre = String
type Provincia = String
type CheckIn = (DNI, Fecha)
type CheckOut = (DNI, Fecha)

data Sexo = Femenino | Masculino deriving (Show, Eq)
data TipoHabitacion = Simple | Doble | Triple | Cuadruple deriving (Show, Eq)

data Accesorio = Jacuzzi | LCD | PS3 | DVD | Pelotero | Inflable deriving (Show, Eq, Ord)