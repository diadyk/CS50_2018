from cs50 import *

number = get_float("Change owed: ")
round(number, 2)

coin1 = 0.01
coin5 = 0.05
coin10 = 0.1
coin25 = 0.25
coin = 0
coins = [coin25,coin10,coin5,coin1]

for coin_value in coins:
    while number >= coin_value:
        number = round(number-coin_value,2)
        coin += 1

print(coin)
