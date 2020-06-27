#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{   
    // Input check
    if (argc != 2)
    {
        printf("Enter key!\n");
        return 1;
    }

    string key = argv[1];

    for (int a = 0, n = strlen(key); a < n; a++)
    {   
        // Checking the key for the absence of letters
        if (isalpha(key[a]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Convert key in digit
    int k = atoi(key);
    // Text request
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {   
        // If the current character is a letter and in ASCII more than 97
        if (isalpha(plaintext[i]) && plaintext[i] >= 97)
        {   
            // We bring to the serial number in the alphabet, add the value of the number, we get the number in the alphabet (% 26). 
            // Add 97 so that the character is in the same case.
            int t = ((plaintext[i] - 97 + k) % 26) + 97;
            printf("%c", t);
        }
        // If the current character is a letter
        else if (isalpha(plaintext[i]))
        {
            // We bring to the serial number in the alphabet, add the value of the number, we get the number in the alphabet (% 26). 
            // Add 65 so that the character is in the same case.
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
