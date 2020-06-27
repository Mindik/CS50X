#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    float letter = 0;
    float word = 1;
    float sentence = 0;
    float L = 0;
    float S = 0;
    // Request text
    string text = get_string("Text: ");
    // Go through all the characters
    for (int b = 0, n = strlen(text); b < n; b++)
    {   
        // If the character is a letter, then increase the counter
        if (isalpha(text[b]))
        {
            letter++;
        }
        // If the character is " ", then increase the counter
        if (text[b] == ' ')
        {
            word++;
        }
        // If the character is ".", "!", "?", then increase the counter
        if (text[b] == '.' || text[b] == '!' || text[b] == '?')
        {
            sentence++;
        }
    }
    // Formulas in the specification
    L = letter * 100 / word;
    S = sentence * 100 / word;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
