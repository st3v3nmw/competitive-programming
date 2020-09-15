from random import randint

def genRandom(n : int, f):
    with open("_out.txt", "w") as fl:
        for _ in range(n):
            fl.write(f())

def genSimilar(n : int, data):
    with open("_out.txt", "w") as fl:
        for _ in range(n):
            fl.write(data)

genRandomUpper = lambda: chr(randint(65, 90))
genRandomLower = lambda: chr(randint(97, 122))
genRandomBin = lambda: '0' if randint(0, 1) == 0 else '1'

if __name__ == "__main__":
    # genRandom(42, genRandomChars)
    genSimilar(20000, "0")
    # genRandom(20000, genRandomBin)
    # genRandom(1500, genRandomLower)