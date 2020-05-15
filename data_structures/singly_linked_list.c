#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define structure
typedef struct sll
{
    int value;
    struct sll* next;
}
node;

node* create(int i);
node* insert(node* head, int i);
bool find(node* head, int i);
void destroy(node* head);

int main(void)
{
    node* new_node = create(5);
    new_node = insert(new_node, 2);
    new_node = insert(new_node, 7);

    /*for (node* tmp = new_node; tmp != NULL; tmp = tmp->next)
    *{
    *    printf("%i, %p,\n", tmp->value, tmp);
    *}
    */

    bool search = find(new_node, 3);
    printf("%s\n", search ? "True" : "False");
    destroy(new_node);
}

// Create a Singly-linked list
node* create(int i)
{
    // Allocate memory for a new node
    node* node = malloc(sizeof(node));
    if (node == NULL)
    {
        return NULL;
    }
    // Initialize value field
    node->value = i;
    // Initialize next field
    node->next = NULL;
    // Return the pointer to node
    return node;
}

// Insert a new node into a linked list
node* insert(node* head, int i)
{
    // Allocate memory for a new node
    node* node = malloc(sizeof(node));
    if (node == NULL)
    {
        return NULL;
    }
    // Initialize value field
    node->value = i;
    // Initialize next field
    node->next = head;
    // New head of the list
    head = node;
    // Return the pointer to the list
    return head;
}

// Search inside the Singly-linked list
bool find(node* head, int i)
{
    bool check = false;
    node* tmp = head;
    do
    {
        //printf("%i %i %p\n", i, tmp->value, tmp);
        if (tmp->value == i)
        {
            check = true;
            break;
        }
        else if (tmp != NULL)
        {
            tmp = tmp->next;
        }
    }while(tmp != NULL);
    return check;
}

// Delete an entire linked list
void destroy(node* head)
{
    if(head == NULL)
    {
        return;
    }
    destroy(head->next);
    free(head);
}

