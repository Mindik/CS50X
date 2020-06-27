// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

//Prototypes hash-function
uint32_t murmur3_32(const void *_key, uint32_t len, uint32_t seed);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 32767;

// Hash table
node *table[N];

int words;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // len word in array
    char check_word[strlen(word)];
    uint32_t lena = strlen(word);
    // Copy strings
    strcpy(check_word, word);
    // If the character is a letter, then change case
    for (int a = 0; a < lena + 1; a++)
    {
        if (isalpha(check_word[a]))
        {
            check_word[a] = tolower(check_word[a]);
        }
    }
    // Get a hash for a word
    unsigned int hash_c = hash(check_word);

    node *cursor = table[hash_c];
    // If the word in the table does not match, then check with all other words
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, check_word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    uint32_t len_check = strlen(word);
    // Hash-function and solt 111 :)
    return murmur3_32(word, len_check, 111) % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Fill in the whole table NULL
    for (int y = 0; y < N; y++)
    {
        table[y] = NULL;
    }
    // Open file dictionary for read
    FILE *fileDic = fopen(dictionary, "r");
    // If error open
    if (fileDic == NULL)
    {
        printf("Dictionary file does not open!\n");
        return 1;
    }
    char buffer[LENGTH];
    // Reads a word from a file until it finds the end of a line
    while (fscanf(fileDic, "%s", buffer) != EOF)
    {
        // Allocates memory for a new node
        node *new_node = malloc(sizeof(node));
        // Copy word from buffer in new_node word
        strcpy(new_node->word, buffer);
        // Toggle point to NULL
        new_node->next = NULL;
        // Get hash for word from buffer
        unsigned int hash_n = hash(buffer);
        // If the table is full, then move the pointer to an empty value and save 
        if (table[hash_n] != NULL)
        {
            for (node *b = table[hash_n]; b != NULL; b = b->next)
            {
                if (b->next == NULL)
                {
                    b->next = new_node;
                    break;
                }
            }
        }
        else
        {
            table[hash_n] = new_node;
        }
        words++;

    }
    fclose(fileDic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int f = 0; f < N; f++)
    {
        node *cur = table[f];
        while (cur != NULL)
        {
            node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    return true;
}

//https://github.com/maciejczyzewski/retter/blob/master/algorithms/MurmurHash/murmurhash3_32.c
uint32_t murmur3_32(const void *_key, uint32_t len, uint32_t seed)
{
    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;
    static const uint32_t r1 = 15;
    static const uint32_t r2 = 13;
    static const uint32_t m = 5;
    static const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;
    const char *key = _key;

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *) key;
    int i;
    for (i = 0; i < nblocks; i++)
    {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    const uint8_t *tail = (const uint8_t *)(key + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3)
    {
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];

            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}
