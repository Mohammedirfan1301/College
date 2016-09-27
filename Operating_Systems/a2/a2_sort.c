/*
    Jason Downing
    Assignment 2
    Operating Systems - COMP.3080
    9/26/2016
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

/*
    Useful links:
    http://stackoverflow.com/questions/7866039/whats-the-opposite-of-closefd-in-c
    http://codewiki.wikidot.com/c%3asystem-calls%3adup
    http://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms
    http://pubs.opengroup.org/onlinepubs/7908799/xsh/open.html
*/

/*
    sort command should be:
    sort -k3,3 -k1,1 cs308a2_sort_data.txt
*/

int main (void) {
  int     inPipe[2], outPipe[2], bytes;
  char    readBuffer[80];
  pid_t   child_pid;

  // Create a pipe, and check for failure (-1)
  if (pipe(inPipe) == -1 || pipe(outPipe) == -1) {
    perror("\nPipe failure!\n\n");
    exit(2);
  }

  //  fork child, block on pipe with read call
  if ( (child_pid = fork() ) == -1) {
    perror("\nFailed to fork\n");
    exit(2);
  }

  //  Child Process
  if (child_pid == 0) {
    // Closing stdout
    if (close(0) == -1) {
        perror("\nCHILD pipe close error: stdout[0].\n");
        exit(3);
    }

    // Alias for stdout
    if (dup(outPipe[0]) != 0) {
        perror("\nCHILD pipe dup error: stdout[0].\n");
        exit(3);
    }

    // Closing stdin
    if (close(1) == -1) {
        perror("\nCHILD pipe close error: stdin[1].\n");
        exit(3);
    }

    // Alias for stdin
    if (dup(inPipe[1]) != 1) {
        perror("\nCHILD pipe dup error: stdout[1].\n");
        exit(3);
    }

    // Close unneeded pipes
    if (close(outPipe[0]) == -1 || close(outPipe[1]) == -1) {
      perror("\nCHILD: pipe failed to close.\n");
      exit(4);
    }

    // Close unneeded pipes
    if (close(inPipe[0]) == -1 || close(inPipe[1]) == -1) {
      perror("\nCHILD: pipe failed to close.\n");
      exit(4);
    }

    // Run the sort
    // Command looks like: sort -k3,3 -k1,1 cs308a2_sort_data.txt
    execlp("sort", "-k3,3", "-k1,1", NULL);

    perror("\nSort has failed to run correctly.\n");
    exit(4);
  } // End of child

  // Close unneeded pipes
  if (close(outPipe[0]) == -1 || close(inPipe[1]) == -1) {
      printf("\nCould not close pipes");
      exit(3);
  }

  // Open the file to be sorted
  int fd = 0;
  fd = open("cs308a2_sort_data", O_RDONLY, 0);

  // Open child's stdout
  FILE* fp = fdopen(inPipe[0], "r");

  return 0;
}
