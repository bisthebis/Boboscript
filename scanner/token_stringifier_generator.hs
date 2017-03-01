import System.IO
import Control.Monad

removePunc :: String -> String
removePunc xs = [ x | x <- xs, not (x `elem` ",.?!-:;\"\'") ]

main = do
    content <- fmap (map removePunc) $ fmap words $ readFile "tokens.txt"
    forM_ content (\s -> putStrLn $ "ADD_CASE(" ++ s ++ ");")
    