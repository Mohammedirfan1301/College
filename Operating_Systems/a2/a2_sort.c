/*
    Jason Downing
    Assignment 2
    Operating Systems - COMP.3080
    9/26/2016
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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
  int     inPipe[2], outPipe[2], rd_bytes;
  char    readBuffer[80];
  pid_t   child_pid;

  // Create a pipe, and check for failure (-1)
  if (pipe(inPipe) == -1 || pipe(outPipe) == -1) {
    perror("\nPipe failure!\n\n");
    exit(2);
  }

  switch (fork() ) {
    // Call failed
    case -1:
      perror("\nFailed to fork\n");
      exit(1);

    case 0:
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
      if (close(outPipe[0]) == -1 || close(outPipe[1]) == -1
          || close(inPipe[0]) == -1 || close(inPipe[1]) == -1) {
        perror("\nCHILD: pipe failed to close.\n");
        exit(4);
      }

      // Run the sort
      // Command looks like: sort -k3,3 -k1,1 cs308a2_sort_data.txt
      //execlp("sort", "-k3,3", "-k1,1", NULL);
      execlp("sort", "sort", "-k", "3.3n", "-k", "1.1", "-k", "2.2", NULL);

      perror("\nSort has failed to run correctly.\n");
      exit(4);
  }   // end of switch / child

  // Close unneeded pipes
  if (close(outPipe[0]) == -1 || close(inPipe[1]) == -1) {
      perror("\nCould not close pipes");
      exit(3);
  }

  // Open the file to be sorted
  int fd = 0;
  fd = open("cs308a2_sort_data.txt", O_RDONLY, 0);

  // Read the data from the file
  while (rd_bytes = read(fd, readBuffer, 80)) {
    // Write the data from the file into the pipe. Check for errors.
    if (write(outPipe[1], readBuffer, rd_bytes) == -1) {
      perror("\nUnabled to write to child.\n");
      exit(2);
    }
  }

  // Close unneeded pipes
  if (close(outPipe[1] == -1)) {
    perror("\nCould not close pipe\n");
    exit(3);
  }

  // Open child's stdout
  FILE* fp = fdopen(inPipe[0], "r");

  int count = 0;
  int oldAreaCode = 0;
  int areaCode, three, four;
  char first[80], last[80];

  //printf("Got to the part where we sort stuff.\n");

  // Run through the entire list, one line at a time.
  while (fscanf(fp, "%s %s %d %d %d\n", last, first, &areaCode, &three, &four) != EOF) {
    printf("HI!\n");

    // Detect the first areaCode.
    if (oldAreaCode == 0) {
      oldAreaCode = areaCode;
      count++;
    }

    // Count the number of people with the same area code
    if (oldAreaCode == areaCode) {
      count++;
    }
    else {
      // Found a new area code, so print it + the count we found.
      printf("%d: %d\n", oldAreaCode, count);
      count = 1;
    }
  }

  // Print the final area code / count
  printf("%d: %d\n", oldAreaCode, count);

  // Close the child's stdout.
  fclose(fp);

  return 0;
}
