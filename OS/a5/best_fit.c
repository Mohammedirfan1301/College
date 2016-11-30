/**
 *     Jason Downing
 *     Assignment 5 best fit c file
 */
#include "main.h"

// Allocate using best fit
int allocate_best_fit(struct request *request) {

  // Free lists
  struct free_list *freeList = NULL;
  struct free_list *validList = NULL;
  int size_diff = 0;
  int left_over = 0;

  // Find the smallest block that fits
  int smBlock_Flag = TRUE;

  for (freeList = list_head.next; freeList; freeList = freeList->next) {
    if (request->size <= freeList->block_size) {
      size_diff = freeList->block_size - request->size;

      if (left_over >= size_diff) {
        left_over = size_diff;
        validList = freeList;
      }

      if (smBlock_Flag) left_over = size_diff;
      smBlock_Flag = FALSE;
    }
  }

  // Did we find a match?
  if (validList != NULL) {
    // Set request
    request->is_allocated = TRUE;
    request->base_adr = validList->block_adr;
    request->next_boundary_adr = request->base_adr + request->size;

    // Update
    total_free = total_free - request->size;
    request->memory_left = total_free;

    // If there is a perfect match
    if ((validList->block_size = validList->block_size - request->size) == 0) {
      validList->previous->next = validList->next;
      validList->next->previous = validList->previous;
      free(validList);
      return 0;
    }

    validList->block_adr = validList->block_adr + request->size;
    return 0;
  }

    // No valid space
    request->memory_left = total_free;
    return 0;
}
