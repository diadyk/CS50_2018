from cs50 import *
from sys import *

k = int(sys.argv[1])


text = get_string("plaintext: ")
print("ciphertext: ", end="")

for i in range(len(text)):
    text_number = ord(text[i])
    if text_number >= 65 and text_number <= 90:
        output_text = chr((text_number - 65 + k) % 26 + 65)
        print(output_text, end="")

    elif text_number >= 97 and text_number <= 122:
        output_text = chr((text_number - 97 + k) % 26 + 97)
        print(output_text, end="")

    else:
        print(text[i], end="")

print("\n", end="")

