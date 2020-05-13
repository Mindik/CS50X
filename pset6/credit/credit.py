from cs50 import get_string

card = get_string("Enter number card: ")

sum_one = 0
sum_two = 0
card_v = int(card)
for a in range(len(card)):
    sum_one += card_v % 10
    card_v = int(card_v / 10)
    two = card_v % 10 * 2
    sum_two += int(two % 10 + two // 10)
    card_v = int(card_v / 10)

sum_all = (sum_one + sum_two) % 10
a_card = int(card)
while a_card > 99:
    a_card = int(a_card / 10)

if a_card // 10 == 4 and (len(card) == 13 or len(card) == 16) and sum_all == 0:
    print("VISA")
elif (51 <= a_card or a_card <= 55) and len(card) == 16 and sum_all == 0:
    print("MASTERCARD")
elif (a_card == 34 or a_card == 37) and len(card) == 15 and sum_all == 0:
    print("AMEX")
else:
    print("INVALID")