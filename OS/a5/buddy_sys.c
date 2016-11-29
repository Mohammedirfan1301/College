/**
 *     Jason Downing
 *     Assignment 5 buddy system c file
 *
 */
#include "main.h"

// Allocate using buddy sys
int allocate_buddy_sys(struct request *request) {
  struct free_list *freeList = NULL;
  struct free_list *validList = NULL;

  int diff = 0;
  int left = 0;

  // find block
  for (freeList = list_head.next; freeList; freeList = freeList->next) {
    if (request->size <= freeList->block_size) {
      diff = freeList->block_size - request->size;

      // if smaller chunk exists
      if (left >= diff) {
        left = diff;
        validList = freeList;
      }
    }
  }

  // hmm
  if (validList != NULL) {
    request->is_allocated = TRUE;
    request->base_adr = validList->block_adr;
    request->next_boundary_adr = request->base_adr + request->size;

    // remaining space
    total_free = total_free - request->size;
    request->memory_left = total_free;

    // perfect match
    if ((validList->block_size = validList->block_size - request->size) == 0) {
      validList->previous->next = validList->next;
      validList->next->previous = validList->previous;
      free(validList);
      return 0;
    }

    validList->block_adr = validList->block_adr + request->size;
    return 0;
  }

  // no valid space
  request->memory_left = total_free;
  return 0;
}
