#ifndef LIST_H
#define LIST_H

#include "stdio.h"
#include "stdlib.h"
#include "semaphore.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

typedef struct node
{
    int data;
    struct node* next;
} node_t;

node_t* list_insert_front(node_t* anchor, int data);
node_t* list_create_node(int data);
node_t* list_insert_end(node_t* node, int data);
node_t* list_remove_head(node_t* node);
node_t* list_remove_tail(node_t* node);
int list_get_head(node_t* node);
void printlist(node_t* anchor);


#endif