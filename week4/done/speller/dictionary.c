// EDITED
// Main file for program working 

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26
#define DICTIONARY "dictionaries/large"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            // unload();
            return false;
        }
        strcpy(new_node->word,word);

        int hash_word = hash(word);

        new_node->next = hashtable[hash_word];
        hashtable[hash_word] = new_node;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int size[N];
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        node *current = hashtable[i];
        int count = 0;
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
        size[i] = count;
    }

    for (int i = 0; i < N; i++)
    {
        sum +=size[i];
    }
    return sum;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_word = hash(word);
    node *current = hashtable[hash_word];
    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        hashtable[i] = NULL;
    }
    return true;
}
