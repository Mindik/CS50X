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
        // Request card number >= 0
        number_card = get_long("Enter number card: ");
    }
    while (number_card <= 0);
    // Variable for counting the number of digits
    long number_card_count = number_card;
    // Variable for calculating the amount
    long number_card_sum_one = number_card;
    // Counts the number of digits
    while (number_card_count != 0)
    {
        number_card_count /= 10;
        count++;
    }
    // Finds the sum of the odd digits from the end and the sum of the products of even digits
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
    // We get the last 2 digits of the card number
    while (a_number_card > 99)
    {
        a_number_card /= 10;
        a = a_number_card;
    }
    // Prints if the condition is met.
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
