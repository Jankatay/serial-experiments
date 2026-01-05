-- The lazuri language spoken in northern Turkey has a really cool rule. 
-- "Every noun must end with a vowel"
-- So I made came up with this state machine to check if a word is  100% NOT a noun

-- Definetely not a noun by mathmatical implication!
not_noun_also :: [Char] -> Bool
not_noun_also [] = False
not_noun_also (x:xh) | elem x "aeiouAEIOU" = not_noun_also xh
                     | otherwise = not_noun xh

-- Could still be a verb etc. Implication was one-way :3
not_noun :: [Char] -> Bool
not_noun [] = True
not_noun (x:xh) | elem x "aeiouAEIOU" = not_noun_also xh
                | otherwise = not_noun xh

-- some tests 
main :: IO ()
main = do 
  putStr $ "not_noun ['M','j','o','r','a'] -> " ++ (show $ not_noun ['M', 'j', 'o', 'r', 'a']) ++ "\n"
  putStr $ "not_noun ['M','t','u','t','a', 'k'] -> " ++ (show $ not_noun ['M', 't', 'u', 't', 'a', 'z']) ++ "\n"
  putStr $ "not_noun_also ['M','t','u','t','a', 'k'] -> " ++ (show $ not_noun_also ['M', 't', 'u', 't', 'a', 'z']) ++ "\n"

-- Findings: I was expecting it to be "not noun" and "possibly noun" like the previous experiment
-- they both turned out to be "not noun," just in a different state to start. 
-- I want to research this more. 
-- Also I am aware there is MUCH better way of doing this, I am not learning FP now tho and this is more closer to what a state-machine would do.
