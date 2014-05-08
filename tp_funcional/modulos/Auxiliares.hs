module Auxiliares(sinRepetidos, sacarRepetidos) where

sinRepetidos :: (Eq a) =>[a] -> Bool
sinRepetidos [] = True
sinRepetidos (x:xs)
				| x `elem` xs 					= False
				| otherwise 					= sinRepetidos xs

sacarRepetidos :: (Eq a) =>[a] -> [a]
sacarRepetidos xs 								= sacarRepetidosAux xs []

sacarRepetidosAux :: (Eq a) => [a] -> [a] -> [a]
sacarRepetidosAux [] rs 						= rs
sacarRepetidosAux (x:xs) rs
					| not (x `elem` rs)			= sacarRepetidosAux xs (rs++[x])
					| otherwise 				= sacarRepetidosAux xs rs