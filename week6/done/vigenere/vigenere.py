from cs50 import *
from sys import *

code = sys.argv[1]
if len(argv) > 2:
    print("Usage: python vigenere.py k")
    exit(1)
if any(char.isdigit() for char in code):
    print("Usage: python vigenere.py k")
    exit(1)

code = code.lower()
print(code)

text = get_string("plaintext: ")
print("ciphertext: ", end="")

index = -1
for i in range(len(text)):
    text_number = ord(text[i])

    if index == len(code)-1:
        index = 0
    elif (text_number >= 65 and text_number <= 90) or (text_number >= 97 and text_number <= 122):
        index += 1
    k = ord(code[index])

    if text_number >= 65 and text_number <= 90:
        output_text = chr((text_number - 65 + (k-97)) % 26 + 65)
        print(output_text, end="")

    elif text_number >= 97 and text_number <= 122:
        output_text = chr((text_number - 97 + (k-97)) % 26 + 97)
        print(output_text, end="")

    else:
        print(text[i], end="")

print("\n", end="")
