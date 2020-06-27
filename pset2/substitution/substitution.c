#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{   
    // Checking the number of command line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string key = argv[1];
    // Key must contain 26 characters
    if (strlen(key) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string k[26];
    // Array filling NULL
    for (int l = 0; l < 26; l++)
    {
        k[l] = NULL;
    }

    int pp = 0;
    // Check key for character uniqueness
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
    // Text request
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {   
        // If character isalpha and little (>= 97 ASCII) 
        if (isalpha(plaintext[i]) && plaintext[i] >= 97)
        {   
            // Get the serial number of a letter in the alphabet
            int tmp = plaintext[i] - 97;
            // Get the key character at this index, case sensitive
            int t = tolower(key[tmp]);
            printf("%c", t);
        }
        // If character isalpha
        else if (isalpha(plaintext[i]))
        {
            // Get the serial number of a letter in the alphabet
            int tmp = plaintext[i] - 65;
            // Get the key character at this index, case sensitive
            int t = toupper(key[tmp]);
            printf("%c", t);
        }
        // If the character is not a letter, then print
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
