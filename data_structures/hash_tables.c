#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure
typedef struct hash
{
    char* name;
    struct hash* next;
}
node;

#define table_size (26)
#define elements (5)
#define MULTIPLIER (37)
unsigned int hash(const char* str);
node* create(char* str);
node* insert(node* head, char* str);
bool find(char* str, char hash_function);
void destroy(node* head);

node* hashtables[table_size] = {NULL};

int main(int argc, char* argv[])
{
    if (argc != 2 || (argv[1][0] != 'h' && argv[1][0] != 'f'))
    {
        printf("Usage: ./hash_tables hash/first_letter");
        return 1;
    }

    unsigned long h;
    char hash_function = argv[1][0];
    // Populate the hash tables
    for(int i = 0; i < elements; i++)
    {
        char* str = get_string("Name: ");

        switch(hash_function)
        {
            case 'h':
                h = hash(str);
                break;

            case 'f':
                h = str[0];
                h = tolower(h) - 'a' + 1;
                break;
        }

        if (hashtables[h] == NULL)
        {
            hashtables[h] = create(str);
        }
        else if (strcmp(hashtables[h]->name, str) != 0)
        {
            node* tmp = hashtables[h];
            while (tmp->next != NULL)
            {
                if(strcmp(tmp->name, str) == 0)
                {
                    break;
                }
                tmp = tmp->next;
            }
            if(strcmp(tmp->name, str) != 0)
            {
                hashtables[h] = insert(tmp, str);
            }
        }
    }

    for(int i = 0; i < table_size; i++)
    {
        if(hashtables[i] != NULL)
        {
            printf("%s, %p\n", hashtables[i]->name, hashtables[i]->next);
        }
    }

    char* str_search = get_string("Find a name in the list: ");

    bool search = find(str_search, hash_function);
    printf("%s\n", search ? "True" : "False");

    // Free the hash tables
    for(int i = 0; i < table_size; i++)
    {
        destroy(hashtables[i]);
    }
}

/*
* Hush function from
* http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html
*/
unsigned int hash(const char* str)
{
    unsigned long h;
    unsigned const char *us;

    // cast s to unsigned const char *
    // this ensures that elements of s will be treated as having values >= 0
    us = (unsigned const char *) str;

    h = 0;
    while(*us != '\0')
    {
        h = h * MULTIPLIER + *us;
        us++;
    }
    h %= 13;
    h %= 100;
    return h;
}

// Create a node
node* create(char* str)
{
    // Allocate memory for a new node
    node* node = malloc(sizeof(node));
    if (node == NULL)
    {
        return NULL;
    }
    // Initialize value field
    strcpy(node->name, str);
    // Initialize next field
    node->next = NULL;
    // Return the pointer to node
    return node;
}

// Insert a new node into a hash table
node* insert(node* head, char* str)
{
    // Allocate memory for a new node
    node* node = malloc(sizeof(node));
    if (node == NULL)
    {
        return NULL;
    }
    // Initialize value field
    strcpy(node->name, str);
    // Initialize next field
    node->next = head;
    // New head of the list
    head = node;
    // Return the pointer to the list
    return head;
}

// Search inside the hash table
bool find(char* str, char hash_function)
{
    bool check = false;
    int i;

    switch(hash_function)
        {
            case 'h':
                i = hash(str);
                break;

            case 'f':
                i = str[0];
                i = tolower(i) - 'a' + 1;
                break;
        }

    node* tmp = hashtables[i];
    if(strcmp(tmp->name, str) == 0)
    {
        check = true;
    }
    else
    {
        while(tmp != NULL)
        {
            if(strcmp(tmp->name, str) == 0)
            {
                check = true;
                break;
            }
            tmp = tmp->next;
        }
    }
    return check;
}

// Delete an element from hash table
void destroy(node* head)
{
    if(head == NULL)
    {
        return;
    }
    destroy(head->next);
    free(head);
}
