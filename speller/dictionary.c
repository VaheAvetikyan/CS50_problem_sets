// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *create(char *str);
node *insert(node *head, char *str);
void destroy(node *head);
unsigned int hash(const char *word);

#define MULTIPLIER (37)
int word_count;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Convert the word to lowercase
    char *str = calloc(LENGTH, sizeof(char));

    int i = 0;
    while (word[i])
    {
        str[i] = tolower(word[i]);
        i++;
    }

    unsigned long h = hash(str);
    node *tmp = table[h];
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, str) == 0)
        {
            // Free the allocated mamory of a string
            free(str);
            return true;
        }
        tmp = tmp->next;
    }
    // Free the allocated mamory of a string
    free(str);
    return false;
}

/* Hashes word to a number
*
* Hush function from
* http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html
* With some additional functionality
*/
unsigned int hash(const char *word)
{
    unsigned long h = 0;

    // casts to unsigned const char *
    // this ensures that elements of s will be treated as having values >= 0
    unsigned const char *us = (unsigned const char *) word;

    while (*us != '\0')
    {
        h = h * MULTIPLIER + (*us - 'a');
        us++;
    }
    h %= N;
    return h;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Create a buffer for every word
    char *word = malloc(LENGTH * sizeof(char));

    // Read the dictionary one string at a time
    while (fscanf(dict, "%s", word) != EOF)
    {
        unsigned long h = hash(word);

        if (table[h] == NULL)
        {
            table[h] = create(word);
        }
        else
        {
            node *tmp = table[h];
            while (tmp->next != NULL)
            {
                if (strcmp(tmp->word, word) == 0)
                {
                    break;
                }
                tmp = tmp->next;
            }
            if (strcmp(tmp->word, word) != 0)
            {
                table[h] = insert(table[h], word);
            }
        }
        word_count++;
    }
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free the hash tables
    for (int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }
    return true;
}

// Create a node
node *create(char *str)
{
    // Allocate memory for a new node
    node *node = malloc(sizeof(struct node));
    if (node == NULL)
    {
        return NULL;
    }
    // Initialize value field
    strcpy(node->word, str);
    // Initialize next field
    node->next = NULL;
    // Return the pointer to node
    return node;
}

// Insert a new node into a hash table
node *insert(node *head, char *str)
{
    // Allocate memory for a new node
    node *node = malloc(sizeof(struct node));
    if (node == NULL)
    {
        return NULL;
    }
    // Initialize value field
    strcpy(node->word, str);
    // Initialize next field
    node->next = head;
    // New head of the list
    head = node;
    // Return the pointer to the list
    return head;
}

// Delete an element from hash table
void destroy(node *head)
{
    if (head == NULL)
    {
        return;
    }
    destroy(head->next);
    free(head);
}

