/**
 *     Jason Downing
 *     Assignment 5 main c file
 *
 */
#include "main.h"

// Command line program
int main(int argc, char *argv[]) {
  // Make sure the user isn't an idiot and enters the right number of arguments.
  if (argc <= 3 || argc >= 4) {
    // User is an idiot.
    printf("\nError, wrong number of arguments provided.");
    printf("\nYou provided %d arguments, expected 3 arguments.", argc);
    printf("\nUsage: a5 MEM_POLICY TOTAL_FREE_MEM FREE-ALLOC_FILE_NAME");
    exit(1);
  }

  // Step one: get the memory size
  int mem_size = atoi(argv[2]);

  // Step two: get the memory policy
  // Best Fit
  if (strcmp(argv[1], "first") == 0) {
    // best fit function here
    allocate_switch(mem_size, argv[3], ALLOC_BEST_FIT)
  }

  // Buddy system
  if (strcmp(argv[1], "first") == 0) {
    // best fit function here
  }

  // First fit
  if (strcmp(argv[1], "first") == 0) {
    // best fit function here
  }

  return 0;
}

// Allocation function, we pass in memory size and a flag.
// Flags in the header file.
int allocate_switch(int mem_size, char *fileWrite, int alloc_flag) {
  char req_type[30];
  int req_seq = 0;
  int req_size = 0;
  FILE *file = fopen(fileToWrite, "r");

  // Free list
  struct free_list *freeList;
  total_free_space = total_free = (memorySize * 1024);

  // Init array
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
  while (fscanf(file, "%d %s %d", &req_seq, &req_type, &req_size) != EOF) {

    if (strcmp(req_type, "alloc") == 0) {

      // Create request
      req_array[req_seq].is_req = TRUE;
      req_array[req_seq].size = req_size;

      // Need switch here.
      //allocMemBest(&req_array[req_seq]);
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

      // Reset
      req_array[req_seq].elements_on_free_list = 0;
      req_array[req_seq].largest_chunk = 0;

      for (freeList = list_head.next; freeList; freeList = freeList->next) {
        // Total free
        ++req_array[req_seq].elements_on_free_list;

        // BEST FIT
        if (freeList->block_size > req_array[req_seq].largest_chunk) {
          req_array[req_seq].largest_chunk = freeList->block_size;
        }
      }

    } else {
      // Free
      req_array[req_seq].size = req_array[req_size].size;
      req_array[req_seq].is_allocated = req_array[req_size].is_allocated;

      update_list(req_size);

      // Reset
      req_array[req_seq].memory_left = total_free;
      req_array[req_seq].elements_on_free_list = 0;
      req_array[req_seq].largest_chunk = 0;

      for (freeList = list_head.next; freeList; freeList = freeList->next) {
        // Total free
        ++req_array[req_seq].elements_on_free_list;

        // BEST FIT
        if (freeList->block_size > req_array[req_seq].largest_chunk) {
          req_array[req_seq].largest_chunk = freeList->block_size;
        }
      }

    }

  }
  print_results("Best Fit", memorySize, req_array);
  fclose(file);
}
