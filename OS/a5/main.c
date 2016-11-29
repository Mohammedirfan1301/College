/**
 *     Jason Downing
 *     Assignment 5 main c file
 *
 */
#include "main.h"

// Command line program
int main(int argc, char *argv[]) {
  // Make sure the user isn't an idiot and enters the right number of arguments.
  if (argc <= 3 || argc > 4) {
    // User is an idiot.
    printf("\nError, wrong number of arguments provided.");
    printf("\nYou provided %d arguments, expected 4 arguments.", argc);
    printf("\nUsage: a5 MEM_POLICY TOTAL_FREE_MEM FREE-ALLOC_FILE_NAME\n");
    exit(1);
  }

  // Step one: get the memory size
  int mem_size = atoi(argv[2]);

  // debug
  printf("Hey we got here!\n");

  // Step two: get the memory policy
  // Best Fit
  if (strcmp(argv[1], "best") == 0) {
    // best fit function here
    allocate_switch(mem_size, argv[3], ALLOC_BEST_FIT);
  }

  // debug
  printf("Best fit works!\n");

  // Buddy system
  if (strcmp(argv[1], "buddy") == 0) {
    // buddy system function here
    //allocate_switch(mem_size, argv[3], ALLOC_BUDDY_SYS);
  }

  // First fit
  if (strcmp(argv[1], "first") == 0) {
    // first fit function here
    //allocate_switch(mem_size, argv[3], ALLOC_FIRST_FIT);
  }

  // debug
  printf("First fit works!!\n");

  return 0;
}
