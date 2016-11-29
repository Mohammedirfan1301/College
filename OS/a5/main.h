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

struct request{
  int is_req;
  int is_allocated;
  int size;
  int act_size;
  int base_adr;
  int next_boundary_adr;
  int memory_left;
  int largest_chunk;
  int elements_on_free_list;
  struct lel *this_req;
}req_array[NUMBER_ENTRIES];

struct lh lst_ary[21];
int total_free_space, total_free;
int mal_cnt=0;

struct lel *find_el(int bit);
int update_lists(struct lel *el);

#endif
