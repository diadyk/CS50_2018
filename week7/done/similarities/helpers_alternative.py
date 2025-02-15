# EDITED

from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    common_list = []
    list_a = []
    list_b = []
    len_a = len(a)
    len_b = len(b)
    index = 0
    letter_from = -1

    list = list_a
    string = a
    length = len_a

    for i in range(2):
        for letter_to in range(length):
            if string[letter_to] == "\n":
                list.append(string[letter_from + 1:letter_to])
                letter_from = letter_to
            elif (length-1)-letter_to == 0:
                list.append(string[letter_from + 1:letter_to+1])
        letter_from = -1
        list = list_b
        string = b
        length = len_b

    for i in range(len(list_a)):
        for o in range(len(list_b)):
            if list_a[i] == list_b[o]:
                for str in common_list:
                    if str == list_a[i]:
                        index += 1
                if index == 0:
                    common_list.append(list_a[i])
                index = 0
    return common_list


def sentences(a, b):
    """Return sentences in both a and b"""

    common_list = []
    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)
    index = 0

    for i in range(len(list_a)):
        for o in range(len(list_b)):
            if list_a[i] == list_b[o]:
                for str in common_list:
                    if str == list_a[i]:
                        index += 1
                if index == 0:
                    common_list.append(list_a[i])
                index = 0
    return common_list

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    common_list = []
    list_a = []
    list_b = []
    split_a = a.split(" ")
    split_b = b.split(" ")
    list = list_a
    split = split_a
    index = 0


    for i in range(2):
        for i in split:
            length = len(i)
            for o in range(length-1):
                if len(i[o:o+n]) == n:
                    list.append(i[o:o+n])
        list = list_b
        split = split_b

    for q in range(len(list_a)):
        for w in range(len(list_b)):
            if list_a[q] == list_b[w]:
                for str in common_list:
                    if str == list_a[q]:
                        index += 1
                if index == 0:
                    common_list.append(list_a[q])
                index = 0
    return common_list
