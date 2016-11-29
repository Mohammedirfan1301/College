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
int free_list_length = 0, total_free;

// Function calls
int allocate_memory(struct request *);
int update_list(int);

// Best fit, Buddy sys, and First Fit functions
int allocate_switch(int mem_size, char *fileWrite);
int allocate_best_fit(struct request *);
int allocate_buddy_sys(struct request *);
int allocate_first_fit(struct request *);

// Flags for which allocate systel we are doing. Starts with 0, ends with 2.
int const ALLOC_BEST_FIT = 0;
int const ALLOC_BUDDY_SYS = 1;
int const ALLOC_FIRST_FIT = 2;

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
int mal_cnt=0;

struct lel *find_el(int bit);
int update_lists(struct lel *el);

#endif
