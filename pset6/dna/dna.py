from sys import argv
import csv
import re


if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")

with open(argv[2], 'r') as ff:
    sequence = ff.read()

with open(argv[1]) as f:
    data = csv.DictReader(f)
    key = data.fieldnames
    check = False
    for row in data:
        for q in range(1, len(key)):
            if check == True:
                break
            one = int(len(re.findall(key[q], sequence)))
            if one == 1:
                t = one
                r = int(row[key[q]])
                if t != r:
                    check = False
                    break
                if q == len(key) - 1 and t == r:
                    check = True
                    print(row["name"])
                    break
            if one > 1:
                pat = f'(?<={key[q]}){key[q]}(?={key[q]})'
                t = int(len(re.findall(pat, sequence)) + 2)
                r = int(row[key[q]])
                if t != r:
                    check = False
                    break
                if q == len(key) - 1 and t == r:
                    check = True
                    print(row["name"])
                    break
    if check == False:
        print("No match")