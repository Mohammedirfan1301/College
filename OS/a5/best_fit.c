/**
 *     Jason Downing
 *     Assignment 5 best fit c file
 */
#include "main.h"

// Allocate using best fit
int allocate_best_fit(struct request *req) {

  struct free_list *f_list = NULL;      // free list
  struct free_list *v_list = NULL;      // valid list
  int size_diff = 0, left_over = 0;     // Sizes
  int sFlag = TRUE;                     // starting flag

  // Find the smallest block that fits
  for (f_list = list_head.next; f_list; f_list = f_list -> next) {
    if (req -> size <= f_list -> block_size) {

      // Size difference between the free list and the req
      size_diff = f_list -> block_size - req -> size;

      // Found a possible match
      if (left_over >= size_diff) {
        left_over = size_diff;
        v_list = f_list;
      }

      // Start of the list
      if (sFlag) {
        left_over = size_diff;
      }

      sFlag = FALSE;    // Not at the start anymore.
    }
  }

  // Did we find a match?
  if (v_list != NULL) {
    // Set the req
    req -> is_allocated = TRUE;
    req -> base_adr = v_list -> block_adr;
    req -> next_boundary_adr = req -> base_adr + req -> size;

    // Update the free count
    total_free = total_free - req -> size;
    req -> memory_left = total_free;

    // Check to see if there is a match
    if ((v_list -> block_size = v_list -> block_size - req -> size) == 0) {
      v_list -> previous -> next = v_list -> next;
      v_list -> next -> previous = v_list -> previous;

      free(v_list);
      return 0;
    }

    v_list -> block_adr = v_list -> block_adr + req -> size;
    return 0;
  }

  // We didn't find a match :(
  req -> memory_left = total_free;
  return 0;
}
