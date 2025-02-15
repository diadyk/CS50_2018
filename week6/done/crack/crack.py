from cs50 import *
import hashlib

def hash_string(input_string: str) -> str:
    hash_object = hashlib.sha1()
    hash_object.update(input_string.encode('utf-8'))
    return hash_object.hexdigest()

def find_word(dictionary,login):
    for q in range(52):
        letter1 = chr(q + 71) if q >= 26 else chr(q + 65)

        for w in range(52):
            letter2 = chr(w + 71) if w >= 26 else chr(w + 65)

            for r in range(52):
                letter3 = chr(r + 71) if r >= 26 else chr(r + 65)

                for t in range(52):
                    letter4 = chr(t + 71) if t >= 26 else chr(t + 65)

                    for p in range(52):
                        letter5 = chr(p + 71) if p >= 26 else chr(p + 65)
                        word = letter1 + letter2 + letter3 + letter4 + letter5

                        hashed_word = hash_string(word)
                        if hashed_word == dictionary.get("BAAAz"):
                            print(hashed_word)
                            return word

dictionary = {
    "login": "hash password",
    "Max": "a95e85aed56318093b024674e217cae0bd30241d",
    "BAAAz": "dfd928b931d1fae792a8cf1d67166491e143cb04",
    "AXUnt": "aee130664346556147327baa8c30ca08eda3a55b",
    "dimax": "0f13d72f4f54d55c73057cd00d046ab851b4363a"
}
login = get_string("Login: ")
print(find_word(dictionary,login))


