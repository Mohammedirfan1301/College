#include "status.h"

#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

typedef struct _MY_LINKED_LIST *MY_LINKED_LIST;

MY_LINKED_LIST my_linked_list_init_default(void);

int my_linked_list_size(MY_LINKED_LIST hList);

Status my_linked_list_push_back(MY_LINKED_LIST hList, int item);

Status my_linked_list_pop_front(MY_LINKED_LIST hList);
//push_front
//pop_front;
//see value of head of list
int* my_linked_list_front(MY_LINKED_LIST hList);
//
//can't do pop_back because we are singly linked list...

void my_linked_list_destroy(MY_LINKED_LIST* pList);

#endif