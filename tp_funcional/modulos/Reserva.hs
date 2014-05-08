module Reserva (Reserva, nuevaR, documentoR, fechaDesdeR,
 fechaHastaR, tipoR, confirmadaR, confirmarR) where

import Tipos
import Auxiliares

data Reserva = R DNI Fecha Fecha TipoHabitacion Bool
			deriving (Show, Eq)

-- Observadores
----------------------------------------------------------------
documentoR :: Reserva -> DNI
documentoR (R d _ _ _ _) = d

fechaDesdeR :: Reserva -> Fecha
fechaDesdeR (R _ fd _ _ _) = fd

fechaHastaR :: Reserva -> Fecha
fechaHastaR (R _ _ fh _ _) = fh

tipoR :: Reserva -> TipoHabitacion
tipoR (R _ _ _ t _) = t

confirmadaR :: Reserva -> Bool
confirmadaR (R _ _ _ _ c) = c

-- NuevaR
----------------------------------------------------------------
nuevaR :: DNI -> Fecha -> Fecha -> TipoHabitacion -> Reserva
nuevaR _ fd fh _ | ((fd < fh) == False) = error "Error en función nuevaR: las fechas recibidas no cumplen la especificación."
nuevaR d fd fh t = R d fd fh t False


-- ConfirmarR
----------------------------------------------------------------
confirmarR :: Reserva -> Reserva
confirmarR (R d fd fh t _) = R d fd fh t True