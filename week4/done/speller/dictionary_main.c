// ADDED
// File for showing the work of functions
// This file runs independently of the main program

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

#define N 26
#define DICTIONARY "dictionaries/large"


typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[N];




unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}





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
            unload();
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



unsigned int size(void)
{
    char abc[26] = "abcdefghijklmnopqrstuvwxyz";
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
    printf("%d\n", sum);
    return sum;
}


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





int main(int argc, char *argv[])
{
    char *dictionary = (argc == 2) ? argv[1] : DICTIONARY;
    const char *word  = "azure";
    if (load(dictionary))
    {
        check(word);
        size();

        unload();
    }
    else
    {
        return 1;
    }

    return 0;
}

