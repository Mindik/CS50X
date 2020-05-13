#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long number_card;
    int count = 0;
    int sum_one = 0;
    int tmp = 0;
    int sum_two = 0;
    int all_sum = 0;
    int a = 0;

    do
    {
        number_card = get_long("Enter number card: ");
    }
    while (number_card <= 0);

    long number_card_count = number_card;
    long number_card_sum_one = number_card;

    while (number_card_count != 0)
    {
        number_card_count /= 10;
        count++;
    }

    while (number_card_sum_one != 0)
    {
        sum_one += number_card_sum_one % 10;
        number_card_sum_one /= 10;
        tmp = number_card_sum_one % 10 * 2;
        sum_two += tmp % 10 + tmp / 10;
        number_card_sum_one /= 10;
    }
    all_sum = (sum_one + sum_two) % 10;

    long a_number_card = number_card;
    while (a_number_card > 99)
    {
        a_number_card /= 10;
        a = a_number_card;
    }

    if (a / 10 == 4 && (count == 13 || count == 16) && all_sum == 0)
    {
        printf("VISA\n");
    }
    else if ((a >= 51 && a <= 55) && count == 16 && all_sum == 0)
    {
        printf("MASTERCARD\n");
    }
    else if ((a == 34 || a == 37) && count == 15 && all_sum == 0)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}