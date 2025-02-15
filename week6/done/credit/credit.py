from cs50 import *


def calculate(card_number,length):
    double = 0
    single = 0

    for i in range(0,length,2):
        card_number[i]
        double += int(card_number[i]) * 2

    for i in range(1,length,2):
        card_number[i]
        single += int(card_number[i])

    if (single + double) % 10 == 0:
        card_number = True

    return card_number



card_number = get_string("Number: ")
length = len(card_number)

if calculate(card_number,length):
    if length == 15 and card_number[0] == "3" and (card_number[1] == "4" or card_number[1] == "7"):
        print("AMEX\n")
    elif (length == 13 or length == 16) and card_number[0] == "4":
        print("VISA\n")
    elif length == 16 and card_number[0] == "5":
        for i in range(1,6):
            if int(card_number[1]) == i:
                print("MASTERCARD\n")
    else:
        print("INVALID\n")
else:
    print("INVALID\n")

