// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int wordCount = 0;
unsigned int hashValue;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hashValue = hash(word);
    node *pointer = table[hashValue];

    while (pointer != NULL)
    {
        if (strcasecmp(word, pointer->word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary
    FILE *Dict = fopen(dictionary, "r");

    // if the return value is NULL
    if (Dict == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Read the dictionary
    char word[LENGTH + 1];

    while (fscanf(Dict, "%s", word) != EOF)
    {
        node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, word);
        hashValue = hash(word);
        temp->next = table[hashValue];
        table[hashValue] = temp;

        wordCount++;
    }
    // Close dictionary
    fclose(Dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordCount > 0)
    {
        return wordCount;
    }
    return 0;
}

void freenode(node *n)
{
    if (n->next != NULL)
    {
        freenode(n->next);
    }
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the start of the linked list
        node *cursor = table[i];

        // If coursor is not NULL, free memory
        while (cursor != NULL)
        {
            // Create temp
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up temp;
            free(tmp);
        }
    }
    return true;
}
