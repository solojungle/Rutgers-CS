-- Ali Awari (aka87)
-- Principles of Programming
-- April 7, 2019

-- 1. Hopscotch
getNth :: Int -> [a] -> [a]
getNth _ [] = []
getNth n xs
  | n < 0 || n >= length xs  = []
  | otherwise = xs !! n : []

skipSingle :: Int -> [a] -> [a]
skipSingle x xs
  | otherwise = concat [getNth n xs | n <- remIndex x xs]

remIndex :: Int -> [a] -> [Int]
remIndex x xs
  | x < 0 || x > length xs = []
  | otherwise = [ n - 1 | n <- [0..length xs], n `rem` x == 0]

skips :: [a] -> [[a]]
skips [] = []
skips xs = do
  [ skipSingle x xs | x <- [1.. length xs]]

-- 2. Local maxima
localMaxima :: [Integer] -> [Integer]
localMaxima [] = []
localMaxima xs
  | length xs < 3 = []
  | otherwise = concat [ localMax x | x <- sublist 3 (tailList xs) ]

localMax :: [Integer] -> [Integer]
localMax [] = []
localMax xs
  | length xs < 3 = []
  | otherwise = maxCompare (take 3 xs)

maxCompare :: [Integer] -> [Integer]
maxCompare [] = []
maxCompare (a:b:c:xs)
  | a >= b = []
  | c >= b = []
  | otherwise = b : []

tailList [] = []
tailList xs
  | length xs < 3 = []
  | length xs >= 3 = concat [take 3 xs, tailList (tail xs)]

sublist :: Int -> [a] -> [[a]]
sublist n ls
    | n <= 0 || null ls = []
    | otherwise = take n ls:sublist n (drop n ls)

-- 3. Histogram
histogram :: [Integer] -> String
histogram xs =
    fst (foldr
        (\_ (sec, x) -> ((map (\x -> if x > 0 then '*' else ' '))
        x ++ "\n" ++ sec, map (subtract 1) x))
        ("", (countEach xs))
        [1..maximum (countEach xs)]) ++ "==========\n0123456789\n"
    where
        countEach xs = map (\x -> count x xs) [0..9]

count x = length . filter (== x)
