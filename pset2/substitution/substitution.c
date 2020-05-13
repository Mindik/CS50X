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
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string k[26];

    for (int l = 0; l < 26; l++)
    {
        k[l] = NULL;
    }

    int pp = 0;

    for (int p = 0, n = strlen(key); p < n; p++)
    {
        if (!isalpha(key[p]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else if (isalpha(key[p]))
        {
            pp = tolower(key[p]) - 97;

            if (k[pp] == NULL)
            {
                k[pp] = &key[p];
            }

            else if (k[pp] != NULL)
            {
                printf("Letters are repeated\n");
                return 1;
            }
        }

    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]) && plaintext[i] >= 97)
        {
            int tmp = plaintext[i] - 97;
            int t = tolower(key[tmp]);
            printf("%c", t);
        }
        else if (isalpha(plaintext[i]))
        {
            int tmp = plaintext[i] - 65;
            int t = toupper(key[tmp]);
            printf("%c", t);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}