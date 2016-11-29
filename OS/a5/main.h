/**
 *     Jason Downing
 *     Assignment 5 main header file
 *     Mostly taken from Prof. Moloney's site:
 *     http://www.cs.uml.edu/~bill/cs308/Assignment_5_data_structs.txt
 *
 */
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUMBER_ENTRIES  (1001)
#define FALSE           (0)
#define TRUE            (1)
#define DONE            (2)

struct request{
  int is_req;
  int is_allocated;
  int size;
  int base_adr;
  int next_boundary_adr;
  int memory_left;
  int largest_chunk;
  int elements_on_free_list;
}req_array[NUMBER_ENTRIES];

struct free_list{
  struct free_list *next;
  struct free_list *previous;
  int block_size;
  int block_adr;
  int adjacent_adr;
}list_head, *top;

int total_free_space;
int total_free;

// Function calls
int allocate_memory(struct request *);
int update_list(int index);
void print_results(char* policy, int memorySize, struct request* req);

// Best fit, Buddy sys, and First Fit functions
int best_fit(int memorySize, char *fileToWrite);
int allocate_best_fit(struct request *);
int first_fit(int memorySize, char *fileToWrite);
int allocate_first_fit(struct request *);

// Couldn't finish this one so I commented it out.
// int allocate_buddy_sys(struct request *);

/*  Buddy list structures below.
    I never finished it so I commented it out.

// a block list element on one of the block sized
// list of addresses
struct lel{
  struct lel *next;
  struct lel *prev;
  int adr;
  int bud_adr;
  int bit;
};

// a list head for one of the block sized lists that hold
// struct lel elements (need one for each in-range power of 2)
struct lh{
  struct lel *head;
  int cnt;
};

struct lh lst_ary[21];
int total_free_space, total_free;

struct lel *find_el(int bit);
int update_lists(struct lel *el);

*/

#endif
