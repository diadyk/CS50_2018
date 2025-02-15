from cs50 import *


while True:
    number = get_int("Height: ")
    if number <= 8 and number >= 1:
        break

for i in range(number):
    print(" " * (number-(i+1)), end="")
    print("#" * (i+1), end="")
    print()

