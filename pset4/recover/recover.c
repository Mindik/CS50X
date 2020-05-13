#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    char *infile = argv[1];
    FILE *card = fopen(infile, "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    FILE *new_file = NULL;
    char jpgName[7];
    int count = 0;
    uint8_t arr[SIZE];

    while (fread(arr, SIZE, 1, card))
    {
        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] >= 0xe0 || arr[3] <= 0xef))
        {
            if (new_file != NULL)
            {
                fclose(new_file);
            }
            sprintf(jpgName, "%03d.jpg", count);
            count++;
            new_file = fopen(jpgName, "w");
        }
        if (new_file != NULL)
        {
            fwrite(arr, SIZE, 1, new_file);
        }
    }
    fclose(card);
    fclose(new_file);
    return 0;
}
