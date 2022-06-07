// Header file for single linked int lists
// Interface uses functional style.
// The functions return pointers to the resulting lists.
// 

#ifndef _SINGLE_LINKED_LIST_FUNCTIONAL_H
#define _SINGLE_LINKED_LIST_FUNCTIONAL_H

#include <stdbool.h>

typedef struct node {
  int data;               // Payload; integer data
  struct node* next;      // Pointer to next node
} node_t;

extern node_t* list_create_node(int data);

void list_insert_front(node_t* * panchor, int data);
void list_insert_end(node_t* * panchor, int data);

void list_dump(node_t *anchor);
void list_free(node_t** panchor);
void list_contains(node_t** panchor, int data, bool* res);

extern int list_get_head(node_t* anchor);
extern int list_get_tail(node_t* anchor);

extern node_t* list_remove_head(node_t* anchor);
extern node_t* list_remove_tail(node_t* anchor);

extern node_t* list_delete_all(node_t* anchor, int data);
extern node_t* list_delete_first(node_t* anchor, int data);

#endif
