#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE 512

int main(int argc, char *argv[])
{
    // Check the number of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Pointer to an argument
    char *infile = argv[1];
    // Open file
    FILE *card = fopen(infile, "r");
    // Check error open
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    // New file = NULL
    FILE *new_file = NULL;
    // Array char max len = 7 (001.jpg)
    char jpgName[7];
    // Counter for name file
    int count = 0;
    // array unsigned int 
    uint8_t arr[SIZE];
    // Reads one 512-sized block from a card and writes to an array
    while (fread(arr, SIZE, 1, card))
    {
        // Check the first three bytes and compare the fourth
        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] >= 0xe0 || arr[3] <= 0xef))
        {
            // If new file open, then close
            if (new_file != NULL)
            {
                fclose(new_file);
            }
            // Save the new name to the variable
            sprintf(jpgName, "%03d.jpg", count);
            count++;
            // Open file for writing
            new_file = fopen(jpgName, "w");
        }
        // If new file is open, then write array
        if (new_file != NULL)
        {
            fwrite(arr, SIZE, 1, new_file);
        }
    }
    fclose(card);
    fclose(new_file);
    return 0;
}
