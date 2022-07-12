#include "list.h"

int element = 1;

sem_t semaphore1;
sem_t countsem;

node_t* list_insert_front(node_t* anchor, int data)
{
    node_t* newnode;
    newnode = list_create_node(data);
    newnode->next = anchor;
    return newnode;
}

node_t* list_create_node(int data)
{
    node_t* newnode;
    if((newnode = malloc(sizeof(node_t))) == NULL)
    {
        printf("ERROR! Storage couldnt be located!");
        exit(EXIT_FAILURE);
    }
    else
    {
        newnode->data = data;
        newnode->next = NULL;
        return newnode;
    }
}

node_t* list_insert_end(node_t* anchor, int data)
{
    if(anchor == NULL)
    {
        return list_create_node(data);
    }

    node_t* pnode = anchor;
    while(pnode->next != NULL)
    {
        pnode = pnode->next;
    }
    pnode->next = list_create_node(data);
    return anchor;
}

node_t* list_remove_head(node_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        node_t* temp = node->next;
        free(node);
        return temp;
    }
}

node_t* list_remove_tail(node_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        if(node->next == NULL)
        {
            free(node);
            return NULL;
        }
        else
        {
            node->next = list_remove_tail(node->next);
            return node;
        }
    }
}

int list_get_head(node_t* node)
{
    if(node==NULL)
    {
        printf("ERROR! LIST EMPTY!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return node->data;
    }
}

void printlist(node_t* anchor)
{
    node_t* temp;
    temp = anchor;
    if(temp != NULL)
    {
        printf("%d. Element: %d\n", element, temp->data);
        element++;
        printlist(temp->next);
    }
    else
    {
        element = 1;
    }
}