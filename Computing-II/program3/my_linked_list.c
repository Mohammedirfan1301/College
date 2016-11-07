#include <stdlib.h>
#include "my_linked_list.h"

typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

struct linked_list
{
	Node* head;
	Node* tail;
};
typedef struct linked_list Linked_list;

int find_size(Node* head);


MY_LINKED_LIST my_linked_list_init_default(void)
{
	Linked_list *temp;

	temp = (Linked_list*) malloc(sizeof(Linked_list));
	if(temp != NULL)
	{
		temp->head = NULL;
		temp->tail = NULL;
	}


	return (MY_LINKED_LIST) temp;
}

int my_linked_list_size(MY_LINKED_LIST hList)
{
	Linked_list *list = (Linked_list*) hList;
	if(list != NULL)
	{
		return find_size(list->head);
	}
	return -1;
}

Status my_linked_list_push_back(MY_LINKED_LIST hList, int item)
{
	Linked_list *list = (Linked_list*) hList;
	Node* temp;

	if(list != NULL)
	{
		temp = (Node*) malloc(sizeof(Node));
		if(temp == NULL)
		{
			return FAILURE;
		}
		temp->data = item;
		temp->next = NULL;
		if(list->head == NULL && list->tail == NULL)
		{
			list->head = temp;
			list->tail = temp;
		}
		else
		{
			list->tail->next = temp;
			list->tail = temp;
		}
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

void my_linked_list_destroy(MY_LINKED_LIST* pList)
{
	Linked_list *list = (Linked_list*) *pList;

	Node* temp;
	if(list != NULL)
	{
		temp = list->head;

		while(temp != NULL) //delete the linked list if it exists
		{
			list->head = list->head->next;
			free(temp);
			temp = list->head;
		}	
		free(list);  //delete the footprint
		*pList = NULL;
	}
	

	return;
}

//int find_size(Node* head) //recursive (probably unsafe for stack size)
//{
//	if(head == NULL)
//	{
//		return 0;
//	}
//	else
//	{
//		return 1 + find_size(head->next);
//	}
//}

int find_size(Node* head)  //iterative version
{
	Node* temp = head;
	int size = 0;

	while(temp != NULL)
	{
		size++;
		temp = temp->next;
	}

	return size;
}

Status my_linked_list_pop_front(MY_LINKED_LIST hList)
{
	Linked_list *list = (Linked_list*) hList;

	Node* temp;

	if(list != NULL)
	{
		if(list->head !=NULL)
		{
			temp = list->head;
			list->head = list->head->next;
			free(temp);
			if(list->head == NULL)
			{
				list->tail = NULL;
			}
			return SUCCESS;
		}
	}
	return FAILURE;

}

int* my_linked_list_front(MY_LINKED_LIST hList)
{
	Linked_list *list = (Linked_list*) hList;

	if(list != NULL)
	{
		if(list->head != NULL)
		{
			return &(list->head->data);
		}
	}
	return NULL;

}