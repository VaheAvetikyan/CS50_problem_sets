#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure
typedef struct trie
{
    char* name;
    struct trie* path[26];
}
trie;

trie* create(void);
trie* insert(char* str, trie* head);
bool find(trie* head, char* str);
void destroy(trie* head, char* str);

int main(void)
{
    // Creates the head of the trie
    trie* head = malloc(sizeof(struct trie));
    if (head == NULL)
    {
        return 1;
    }


    // Gets input, maybe prompt from a user, or from a file
    char* str = get_string("Name: ");
    // Inserts the input to a trie
    head = insert(str, head);

    trie* tmp = head;
    for(int i = 0; i < 5; i++)
    {
        int j = tolower(str[i]) - 'a';
        printf("%i, %p, %s\n", j, tmp->path[j], tmp->name);
        tmp = tmp->path[j];
    }

    char* string = get_string("Search name: ");
    bool search = find(head, string);
    printf("%s\n", search ? "True" : "False");

    destroy(head, str);
    free(head);
}

// Create a trie
trie* create(void)
{
    // Allocate memory for a new trie
    trie* trie = malloc(sizeof(struct trie));
    if (trie == NULL)
    {
        return NULL;
    }
    // Initialize value field
    //trie->name = NULL;
    // Return the pointer to trie
    return trie;
}

// Insert a trie
trie* insert(char* str, trie* head)
{
    // Temporary pointer to a trie
    trie* tmp = head;

    for(int i = 0; i < 46; i++)
    {
        int j = tolower(str[i]) - 'a';

        if (tmp->path[j] == NULL && str[i] != '\0')
        {
            tmp->path[j] = create();
        }
        else if(str[i] == '\0')
        {
            strcpy(tmp->name, str);
            printf("%s\n", tmp->name);
            break;
        }
        printf("%p\n", tmp->path[j]);
        tmp = tmp->path[j];
        printf("%i, %p\n", j, tmp);
    }

    return head;
}

// Search inside the trie
bool find(trie* head, char* str)
{
    bool check = false;
    trie* tmp = head;

    for(int i = 0; i < 46; i++)
    {
        int j = tolower(str[i]) - 'a';
        if(str[i] == '\0' || tmp->path[j] == NULL)
        {
            break;
        }
        tmp = tmp->path[j];
    }

    printf("%s\n", tmp->name);
    if (tmp->name == NULL)
    {
        check = false;
    }
    else if (strcmp(tmp->name, str) == 0)
    {
        check = true;
    }
    return check;
}

int _int = 0;
// Delete an element from trie
void destroy(trie* head, char* str)
{
    int j = tolower(str[_int]) - 'a';
    if(head->path[j] == NULL)
    {
        return;
    }
    _int++;
    destroy(head->path[j], str);
    free(head->path);
}

