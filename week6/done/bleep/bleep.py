from cs50 import *
from sys import *


def main():
    file = sys.argv[1]

    if len(argv) > 2:
        print("Usage: python vigenere.py k")
        exit(1)

    with open(file, "r") as file:
        dictionary = file.read().split()

    text = get_string("What message would you like to censor?\n")
    words = text.split()
    for i in words:
        if i.lower() in dictionary:
            print("*" * len(i), end=" ")
        else:
            print(i, end=" ")
    print()



if __name__ == "__main__":
    main()
