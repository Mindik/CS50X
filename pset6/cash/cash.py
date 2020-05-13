from cs50 import get_float


def main():
    dollars = get_positive_float()
    cents = int(round(dollars * 100))
    sum_m = cents // 25 + cents % 25 // 10 + cents % 25 % 10 // 5 + cents % 25 % 10 % 5
    print(sum_m)


def get_positive_float():
    while True:
        a = get_float("Enter dollars: ")
        if a > 0:
            break
    return a


main()