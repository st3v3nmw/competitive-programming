module Main where
import System.Environment

main::IO()
main = do
    args <- getArgs
    let arg1 = read(args !! 0) :: Integer
    let arg2 = read(args !! 1) :: Integer
    putStrLn("Result: " ++ show(arg1 * arg2))

    name <- getLine
    putStrLn("\nHello, " ++ name ++ "!")