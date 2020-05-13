#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;

    do
    {
        n = get_int("Enter positive number: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        for (int b = 0; b < n - i - 1; b++)
        {
            printf(" ");

        }
        for (int a = 0; a < i + 1; a++)
        {
            printf("#");
        }

        printf("  ");

        for (int a = 0; a < i + 1; a++)
        {
            printf("#");
        }

        printf("\n");

    }
}