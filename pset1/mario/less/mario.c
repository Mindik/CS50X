#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;

    do
    {
        // Request an integer from 1 to 8
        n = get_int("Enter positive number: ");
    }
    while (n < 1 || n > 8);
    
    // Height Cycle
    for (int i = 0; i < n; i++)
    {   
        // printf " " n - i - 1 (1. 8 - 0 - 1 = 7)
        for (int b = 0; b < n - i - 1; b++)
        {
            printf(" ");

        }
        // printf "#" i + 1 (1. 0 + 1 = 1)
        for (int a = 0; a < i + 1; a++)
        {
            printf("#");
        }
        printf("\n");
    }
}
