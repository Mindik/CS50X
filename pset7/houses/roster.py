import cs50
import csv
from sys import argv, exit

# Checking the Number of Arguments
if len(argv) != 2:
    print("Usage: python roster.py 'house'")
    exit(1)

db = cs50.SQL("sqlite:///students.db")
# Query from the database for the entered house
houses = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[1])
# Print result
for row in houses:
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
