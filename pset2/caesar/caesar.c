#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Enter key!\n");
        return 1;
    }

    string key = argv[1];

    for (int a = 0, n = strlen(key); a < n; a++)
    {
        if (isalpha(key[a]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(key);

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]) && plaintext[i] >= 97)
        {
            int t = ((plaintext[i] - 97 + k) % 26) + 97;
            printf("%c", t);
        }
        else if (isalpha(plaintext[i]))
        {
            int t = ((plaintext[i] - 65 + k) % 26) + 65;
            printf("%c", t);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}