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
  int sizeDiff = 0;
  int leftover = 0;

  // Find the smallest block that fits
  int bFlag = TRUE;

  for (freeList = list_head.next; freeList; freeList = freeList->next) {
    if (request->size <= freeList->block_size) {
      sizeDiff = freeList->block_size - request->size;

      if (leftover >= sizeDiff) {
        leftover = sizeDiff;
        validList = freeList;
      }

      if (bFlag) leftover = sizeDiff;
      bFlag = FALSE;
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
