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
#include <string.h>
#include <errno.h>

/*
    Sort command should look like:
    sort -k3,3 -k1,1 FILE_TO_SORT
*/

#define READ 0
#define WRITE 1

int main (int argc, char *argv[]) {
  int     inPipe[2], outPipe[2];
  char    readBuffer[512];
  pid_t   child_pid;

  if (argc == 1 || argc > 2) {
    printf("\nUsage: ./a2_sort file_name_to_sort\n\n");
    exit(1);
  }

  // Create a pipe, and check for failure (-1)
  if (pipe(outPipe) == -1 || pipe(inPipe) == -1) {
    perror("\nParent pipe failure!\n\n");
    exit(2);
  }

  // Fork to create a child process
  child_pid = fork();

  // Error case
  if (child_pid == -1) {
    perror("\nFailed to create a child process!\n");
    exit(1);
  }
  //****************************************************************************
  //                                 Child case
  //****************************************************************************
  else if (child_pid == 0) {

    // Channel plumbing for stdin
    close(0);

    if (dup(outPipe[READ]) != 0) {
        perror("\nCHILD pipe dup error: outPipe[READ].\n");
        exit(3);
    }

    close(outPipe[READ]);
    close(outPipe[WRITE]);

    // Channel plumbing for stdout
    close(1);

    if (dup(inPipe[WRITE]) != 1) {
        perror("\nCHILD pipe dup error: inPipe[WRITE].\n");
        exit(3);
    }

    close(inPipe[READ]);
    close(inPipe[WRITE]);

    // Run the sort
    execlp("sort", "sort", "-k3,3", "-k1,1", NULL);

    perror("\nSort has failed to run correctly.\n");
    exit(4);
  }
  //****************************************************************************
  //                                Parent case
  //****************************************************************************
  FILE *outWrite, *sortData, *sortOut, *sortIn;
  char msg[2];

  // Open the out pipe as a file.
  outWrite = fdopen(outPipe[WRITE], "w");

  // Open the file to be sorted (will be sent to child)
  if ( (sortData = fopen(argv[1], "r")) == NULL) {
    perror("\nError opening file!\n");
  }

  // Loop to send each line of the file through the pipe.
  while (fgets(readBuffer, 80, sortData) != NULL) {
    fprintf(outWrite, "%s", readBuffer);
  }

  // close unneeded files and pipes.
  fflush(outWrite);
  fclose(outWrite);
  close(outPipe[READ]);
  close(inPipe[WRITE]);
  fclose(sortData);

  // Open file to write to.
  msg[1] = '\0';
  sortOut = fopen("sorted_data", "w");

  // Print out data returned by sort
  while (read(inPipe[READ], msg, 1) > 0) {
    fprintf(sortOut, "%s", msg);
  }

  // Close output file
  fflush(sortOut);
  fclose(sortOut);

  // Open file for reading
  if ( (sortIn = fopen("sorted_data", "r")) == NULL) {
    printf("Error opening temp data file for reading!\n");
    exit(4);
  }

  int total = 0, count = -1, oldAreaCode = 0, areaCode = 0;
  char first[80], last[80];

  // Run through the entire list, one line at a time
  while (fgets(readBuffer, 80, sortIn) != NULL) {
    sscanf(readBuffer, "%s %s %d\n", last, first, &areaCode);

    // Detect the first areaCode.
    if (oldAreaCode == 0) {
      oldAreaCode = areaCode;
      count++;
    }

    // Count the number of people with the same area code
    if (oldAreaCode == areaCode) {
      count++;
      total++;
    }
    else {
      // Found a new area code, so print it + the count we found.
      printf("Area code %d had %d unique names\n", oldAreaCode, count);
      oldAreaCode = areaCode;
      count = 1;
      total++;
    }
  }

  // Print the final area code / count
  printf("Area code %d had %d unique names\n", oldAreaCode, count);

  // Print out the total number of lines processed.
  printf("\n%d lines were processed in this report.\n", total);

  return 0;
}
