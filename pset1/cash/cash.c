#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int m25, m10, m5, m1, sum = 0;

    do
    {   
        // Request amount entry > 0
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    // Convert to cents
    int cents = round(dollars * 100);
    // Get the amount using "/" and "%"
    sum = cents / 25 + cents % 25 / 10 + cents % 25 % 10 / 5 + cents % 25 % 10 % 5 / 1;

    printf("%i\n", sum);
}
