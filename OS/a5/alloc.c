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
  struct free_list *free_list;
  total_free_space = total_free = (mem_size * 1024);

  // Initialize the array
  int x = 0;

  for (x = 0; x < NUMBER_ENTRIES; x++) {
    req_array[x].is_req = FALSE;
    req_array[x].is_allocated = FALSE;
  }

  // Free node setup
  top = malloc(sizeof(struct free_list));
  top -> next = NULL;
  top -> previous = &list_head;
  top -> block_size = total_free_space;
  top -> block_adr = 0;
  top -> adjacent_adr = total_free_space;

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

      for (free_list = list_head.next; free_list; free_list = free_list->next) {
        // Total free
        ++req_array[req_seq].elements_on_free_list;

        if (free_list->block_size > req_array[req_seq].largest_chunk) {
          req_array[req_seq].largest_chunk = free_list->block_size;
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

      for (free_list = list_head.next; free_list; free_list = free_list->next) {
        // Total free
        ++req_array[req_seq].elements_on_free_list;

        if (free_list->block_size > req_array[req_seq].largest_chunk) {
          req_array[req_seq].largest_chunk = free_list->block_size;
        }
      }
    }
  }

  // Print the results!
  // Using a switch to mark it as whatever method we're using.
  switch(alloc_flag) {
    case ALLOC_BEST_FIT:
      print_results("Best Fit", mem_size, req_array);
      break;

    case ALLOC_BUDDY_SYS:
      print_results("Buddy System", mem_size, req_array);
      break;

    case ALLOC_FIRST_FIT:
      print_results("First Fit", mem_size, req_array);
      break;

    default:
      printf("\nError, invalid alloc type!");
      exit(2);
  }

  fclose(file);
}

// Update the list
int update_list(int index){

  // free_lists to hold objects
  struct free_list *free_list, *new_block, *combine_block;

  if(req_array[index].is_allocated == FALSE) {
    return 0;
  }

  /// skip block is done
  req_array[index].is_allocated = DONE;
  total_free += req_array[index].size;

  // look at all the blocks in the free list
  for(free_list = list_head.next; free_list; free_list = free_list -> next) {

    // out of range, so skip it m8
    if(req_array[index].base_adr > free_list -> block_adr) {
      continue;
    }

    // create a block to store
    new_block = malloc(sizeof(struct free_list));
    new_block -> block_size = req_array[index].size;
    new_block -> block_adr = req_array[index].base_adr;
    new_block -> adjacent_adr = new_block -> block_adr + new_block -> block_size;

    new_block->next = free_list;
    free_list -> previous -> next = new_block;
    new_block -> previous = free_list -> previous;
    free_list -> previous = new_block;

    // Check to see if we can combine with next
    if(new_block -> adjacent_adr == new_block -> next -> block_adr) {
      combine_block = new_block -> next;
      new_block -> block_size = new_block -> block_size +
                                new_block -> next -> block_size;
      new_block -> adjacent_adr = new_block -> next -> adjacent_adr;
      new_block -> next = new_block -> next -> next;

      if(new_block -> next){
        new_block -> next -> previous = new_block;
      }

      free(combine_block);
    }

    // previous
    new_block = new_block -> previous;

    if((new_block != NULL) && (new_block -> adjacent_adr != 0)) {

      if(new_block -> adjacent_adr == new_block -> next -> block_adr) {
        combine_block = new_block -> next;
        new_block -> block_size = new_block -> block_size +
                                  new_block -> next -> block_size;
        new_block -> adjacent_adr = new_block -> next -> adjacent_adr;
        new_block -> next = new_block -> next -> next;

        if(new_block -> next) {
          new_block ->next -> previous = new_block;
        }

        free(combine_block);
      }
    }

    return 0;
  }
}

// Print function for the report
void print_results(char* policy, int mem_size, struct request* req) {

  // File Headers
  printf("POLICY: %s\tMEMORY SIZE: %d\n\n", policy, mem_size);
  printf("\nNUMBER \tSEQUENCE \tSIZE \tADR \tMEMORY LEFT \tLARGEST CHUNK\n");

  int x = 1, failCnt = 0;
  char operate[6];

  // Loop through the entries in the file, set to 1000
  for(x; x < NUMBER_ENTRIES; x++) {

    if(req[x].is_allocated == FALSE) {
      // set to invalid address
      req[x].base_adr = -1;

      // keep track of how many fails we see
      failCnt++;
    }

    // operation type
    if(req[x].is_req == 1){
      sprintf(operate, "%s", "alloc");
    } else {
      sprintf(operate, "%s", "free");
    }

    // Print data about the request
    printf("\t%d \t%s \t\t%d \t%d \t\t%d \t\t%d\n", x, operate, req[x].size,
            req[x].base_adr, req[x].memory_left, req[x].largest_chunk);
  }

  // bad request
  printf("%d Allocations Failed", failCnt);
}
