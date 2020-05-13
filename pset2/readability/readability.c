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

    string text = get_string("Text: ");

    for (int b = 0, n = strlen(text); b < n; b++)
    {
        if (isalpha(text[b]))
        {
            letter++;
        }
        if (text[b] == ' ')
        {
            word++;
        }
        if (text[b] == '.' || text[b] == '!' || text[b] == '?')
        {
            sentence++;
        }
    }

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