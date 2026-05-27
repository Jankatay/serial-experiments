module Main where

-- state 0
state_even :: [Int] -> Bool
state_even (0:xs) = state_even xs
state_even (1:xs) = state_odd xs
state_even [] = True

-- state 1
state_odd :: [Int] -> Bool
state_odd (0:xs) = state_odd xs
state_odd (1:xs) = state_even xs
state_odd [] = False

-- Some experiments
main :: IO ()
main = do 
  putStr $ "state_even [] -> " ++ (show $ state_even []) ++ "\n" 
  putStr $ "state_even [1] -> " ++ (show $ state_even [1]) ++ "\n" 
  putStr $ "state_even [1,0,0,1] -> " ++ (show $ state_even [1, 0, 0, 1]) ++ "\n" 
  putStr $ "state_odd [1,0,1,1] -> " ++ (show $ state_odd [1, 0, 1, 1]) ++ "\n" 
