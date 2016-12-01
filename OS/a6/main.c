/**
 *     Jason Downing
 *     Assignment 6 main c file
 */
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

// Print function, displays all the stats about the files
void print_stats(struct stat statBuffer);

// Command line program
int main(int argc, char *argv[]) {

  struct stat statBuffer;
  struct dirent* entry;
  DIR* directory;
  int x, y;

  // Two ways to run this program: no arguments, or multiple arguments

  // Multiple arguments
  if (argc > 1) {

    // Let's run through all the arguments
    for(x = 0; x < argc; x++) {
      printf("WE GOT AN ARGUMENT #%d\n", x);

      // Should print details

    }
  }
  // No arguments
  else {
    printf("HEY WE DIDN'T GET ANY ARGUMENTS!\n");
  }

  return 0;
}

// Print function, displays all the stats about the files
void print_stats(struct stat statBuffer) {

}
