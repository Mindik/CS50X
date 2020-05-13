from cs50 import get_int


def main():
    i = get_positive_int()

    r = '#'
    s = ' '
    for a in range(i):
        print(f"{s * (i - a - 1)}{r * (a + 1)}")


def get_positive_int():
    while True:
        n = get_int("Enter positive number: ")
        if n <= 8 and n > 0:
            break
    return n


main()