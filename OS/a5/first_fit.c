/**
 *     Jason Downing
 *     Assignment 5 first first c file
 *
 */
#include "main.h"

// Allocate first fit
int allocate_first_fit(struct request *request) {

  // Free list
  struct free_list *freeList = NULL;

  // Find first block that fits
  for (freeList = list_head.next; freeList; freeList = freeList->next) {
    if (request->size <= freeList->block_size) {
      // Valid
      request->is_allocated = TRUE;
      request->base_adr = freeList->block_adr;
      request->next_boundary_adr = request->base_adr + request->size;

      total_free = total_free - request->size;
      request->memory_left = total_free;

      if ((freeList->block_size = freeList->block_size - request->size) == 0) {
        freeList->previous->next = freeList->next;
        freeList->next->previous = freeList->previous;

        free(freeList);
        return 0;
      }

      freeList->block_adr = freeList->block_adr + request->size;
      return 0;
    }
  }

  // No valid block
  request->memory_left = total_free;
  return 0;
}
