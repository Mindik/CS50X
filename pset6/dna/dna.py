from sys import argv
import csv
import re

# Checking the number of command line arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
# Open file for read
with open(argv[2], 'r') as ff:
    sequence = ff.read()
# Open file 'rt'
with open(argv[1]) as f:
    # Save dictionary to variable
    data = csv.DictReader(f)
    # Field names as keys
    key = data.fieldnames
    # Boolean variable
    check = False
    # Check every line in the dictionary
    for row in data:
        # We go through all the keys except the first, as it is the "name"
        for indexKey in range(1, len(key)):
            if check == True:
                break
            # Find the total number of matches
            allKeyInSequence = int(len(re.findall(key[indexKey], sequence)))
            # Just one key match, then immediately check the quantity from the dictionary
            if allKeyInSequence == 1:
                # Number of matches in the dictionary
                dictionaryMatches = int(row[key[indexKey]])
                # If not equal, then exit the cycle
                if allKeyInSequence != dictionaryMatches:
                    check = False
                    break
                # If they are equal and this is the last key, type the name and exit the loop
                if indexKey == len(key) - 1 and allKeyInSequence == dictionaryMatches:
                    check = True
                    print(row["name"])
                    break
            # If all key > 1
            if allKeyInSequence > 1:
                # Save regular expression
                regularExpression = f'(?<={key[indexKey]}){key[indexKey]}(?={key[indexKey]})'
                # Find all matches standing together. +2 - start and end
                sequenceLength = int(len(re.findall(regularExpression, sequence)) + 2)
                dictionaryMatches = int(row[key[indexKey]])
                # If not equal, then exit the cycle
                if sequenceLength != dictionaryMatches:
                    check = False
                    break
                # If they are equal and this is the last key, type the name and exit the loop
                if indexKey == len(key) - 1 and sequenceLength == dictionaryMatches:
                    check = True
                    print(row["name"])
                    break
    if check == False:
        print("No match")
