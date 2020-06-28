import cs50
import csv
from sys import argv, exit

# Checking the Number of Arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")
# Open file for read
with open(argv[1], "r") as characters:
    # Save dict in reader
    reader = csv.DictReader(characters)
    # We look through each line
    for row in reader:
        # Separate Names
        n = list(row["name"].split(' '))
        # Insert in db
        if len(n) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                       n[0], n[1], row["house"], row["birth"])

        if len(n) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       n[0], n[1], n[2], row["house"], row["birth"])
