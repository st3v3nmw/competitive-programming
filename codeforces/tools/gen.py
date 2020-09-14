from random import randint

def genRandom(n : int, f):
    with open("_out.txt", "w") as fl:
        for _ in range(n):
            fl.write(f())

def genSimilar(n : int, data):
    with open("_out.txt", "w") as fl:
        for _ in range(n):
            fl.write(data)

genRandomChars = lambda: chr(randint(65, 90))

if __name__ == "__main__":
    # genRandom(42, genRandomChars)
    # genSimilar(42, "A")

    pass