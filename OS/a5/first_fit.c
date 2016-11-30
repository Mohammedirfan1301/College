/**
 *     Jason Downing
 *     Assignment 5 first first c file
 *
 */
#include "main.h"

// Allocate first fit
int allocate_first_fit(struct request *req) {

  struct free_list *f_list = NULL;  // Free list

  // Find first block that fits
  for (f_list = list_head.next; f_list; f_list = f_list -> next) {
    if (req -> size <= f_list -> block_size) {

      // Valid
      req -> is_allocated = TRUE;
      req -> base_adr = f_list -> block_adr;
      req -> next_boundary_adr = req -> base_adr + req -> size;

      total_free = total_free - req -> size;
      req -> memory_left = total_free;

      // Check for the first block that fits (size - request = 0)
      if ( (f_list -> block_size = f_list -> block_size - req -> size) == 0) {
        f_list -> previous -> next = f_list -> next;
        f_list -> next -> previous = f_list -> previous;

        free(f_list);
        return 0;
      }

      f_list -> block_adr = f_list -> block_adr + req -> size;
      return 0;
    }
  }

  // No valid blocks :(
  req -> memory_left = total_free;
  return 0;
}
