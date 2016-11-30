/**
 *     Jason Downing
 *     Assignment 5 allocation utilities file
 */
#include "main.h"

// Allocation function, we pass in memory size and a flag.
// Flags in the header file.
int allocate_switch(int mem_size, char *fileWrite, int alloc_flag) {
  char req_type[30];
  int  req_seq = 0;
  int  req_size = 0;
  FILE *file = fopen(fileWrite, "r");

  // Free list
  struct free_list *freeList;
  total_free_space = total_free = (mem_size * 1024);

  // Initialize the array
  int x = 0;

  for (x = 0; x < NUMBER_ENTRIES; x++) {
    req_array[x].is_req = FALSE;
    req_array[x].is_allocated = FALSE;
  }

  // Free node setup
  top = malloc(sizeof(struct free_list));
  top->next = NULL;
  top->previous = &list_head;
  top->block_size = total_free_space;
  top->block_adr = 0;
  top->adjacent_adr = total_free_space;

  // Next free node
  list_head.next = top;
  list_head.previous = NULL;
  list_head.block_size = -1;

  // Read all requests
  while (fscanf(file, "%d %s %d", &req_seq, req_type, &req_size) != EOF) {

    if (strcmp(req_type, "alloc") == 0) {

      // Create request
      req_array[req_seq].is_req = TRUE;
      req_array[req_seq].size = req_size;

      // Switch to whatever allocation method we're using
      switch(alloc_flag) {
        case ALLOC_BEST_FIT:
          allocate_best_fit(&req_array[req_seq]);
          break;

        case ALLOC_BUDDY_SYS:
          allocate_buddy_sys(&req_array[req_seq]);
          break;

        case ALLOC_FIRST_FIT:
          allocate_first_fit(&req_array[req_seq]);
          break;

        default:
          printf("\nError, invalid alloc type!");
          exit(2);
      }

      // Reset the array
      req_array[req_seq].elements_on_free_list = 0;
      req_array[req_seq].largest_chunk = 0;

      for (freeList = list_head.next; freeList; freeList = freeList->next) {
        // Total free
        ++req_array[req_seq].elements_on_free_list;

        if (freeList->block_size > req_array[req_seq].largest_chunk) {
          req_array[req_seq].largest_chunk = freeList->block_size;
        }
      }

    } else {
      // Freeeeeeeee
      req_array[req_seq].size = req_array[req_size].size;
      req_array[req_seq].is_allocated = req_array[req_size].is_allocated;

      update_list(req_size);

      // Reset teh array
      req_array[req_seq].memory_left = total_free;
      req_array[req_seq].elements_on_free_list = 0;
      req_array[req_seq].largest_chunk = 0;

      for (freeList = list_head.next; freeList; freeList = freeList->next) {
        // Total free
        ++req_array[req_seq].elements_on_free_list;

        if (freeList->block_size > req_array[req_seq].largest_chunk) {
          req_array[req_seq].largest_chunk = freeList->block_size;
        }
      }

    }

  }

  // Print the results! Using a switch to mark it as whatever method we're using.
  print_results("Best Fit", mem_size, req_array);
  fclose(file);
}

// Update the list
int update_list(int index){

  // free_lists to hold objects
  struct free_list* freeList;
  struct free_list* newBlock;
  struct free_list* combineBlock;

  if(req_array[index].is_allocated == FALSE) {
    return 0;
  }

  /// skip block is done
  req_array[index].is_allocated = DONE;
  total_free += req_array[index].size;

  // look at all the blocks in the free list
  for(freeList = list_head.next; freeList; freeList = freeList -> next) {

    // out of range, so skip it m8
    if(req_array[index].base_adr > freeList -> block_adr) {
      continue;
    }

    // create a block to store
    newBlock = malloc(sizeof(struct free_list));
    newBlock -> block_size = req_array[index].size;
    newBlock -> block_adr = req_array[index].base_adr;
    newBlock -> adjacent_adr = newBlock -> block_adr + newBlock -> block_size;

    newBlock->next = freeList;
    freeList -> previous -> next = newBlock;
    newBlock -> previous = freeList -> previous;
    freeList -> previous = newBlock;

    // Check to see if we can combine with next
    if(newBlock -> adjacent_adr == newBlock -> next -> block_adr) {
      combineBlock = newBlock -> next;
      newBlock -> block_size = newBlock -> block_size +
                               newBlock -> next -> block_size;
      newBlock -> adjacent_adr = newBlock -> next -> adjacent_adr;
      newBlock -> next = newBlock -> next -> next;

      if(newBlock -> next){
        newBlock -> next -> previous = newBlock;
      }

      free(combineBlock);
    }

    // previous
    newBlock = newBlock -> previous;
    if((newBlock != NULL) && (newBlock -> adjacent_adr != 0)) {

      if(newBlock -> adjacent_adr == newBlock -> next -> block_adr) {
        combineBlock = newBlock->next;
        newBlock -> block_size = newBlock -> block_size +
                                 newBlock -> next -> block_size;
        newBlock -> adjacent_adr = newBlock -> next -> adjacent_adr;
        newBlock -> next = newBlock -> next -> next;

        if(newBlock -> next) {
          newBlock ->next -> previous = newBlock;
        }

        free(combineBlock);
      }
    }

    return 0;
  }
}

// Print function for the report
void print_results(char* policy, int memorySize, struct request* req) {

  // File Headers
  printf("POLICY: %s\tMEMORY SIZE: %d\n\n", policy, memorySize);
  printf("\nNUMBER \tSEQUENCE \tSIZE \tADR \tMEMORY LEFT \tLARGEST CHUNK\n");

  int i = 1;
  int fails = 0;
  char operation[6];

  // Loop through the entries in the file, set to 1000
  for(i; i < NUMBER_ENTRIES; i++) {

    if(req[i].is_allocated == FALSE) {
      // set to invalid address
      req[i].base_adr = -1;

      // keep track of how many fails
      fails++;
    }

    // operation type
    if(req[i].is_req == 1){
      sprintf(operation, "%s", "alloc");
    } else {
      sprintf(operation, "%s", "free");
    }

    // data about the request
    printf("\t%d \t%s \t\t%d \t%d \t\t%d \t\t%d\n", i, operation, req[i].size,
            req[i].base_adr, req[i].memory_left, req[i].largest_chunk);
  }

  // bad request
  printf("%d Allocations Failed", fails);
}
