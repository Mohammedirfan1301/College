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
  pid_t   child_pid;
  int     inPipe[2], outPipe[2];
  char    readBuffer[80], first[80], last[80];
  FILE    *outWrite, *sortData;

  // Check to see if the user used the program correctly.
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
    if (close(0) == -1) {
      perror("\nCHILD pipe error!\n");
      exit(3);
    }

    if (dup(outPipe[READ]) != 0) {
      perror("\nCHILD pipe dup error: outPipe[READ].\n");
      exit(3);
    }

    // Channel plumbing for stdout
    if (close(1) == -1) {
      perror("\nCHILD pipe error!\n");
      exit(3);
    }

    if (dup(inPipe[WRITE]) != 1) {
      perror("\nCHILD pipe dup error: inPipe[WRITE].\n");
      exit(3);
    }

    // Close unneeded pipes
    if (close(outPipe[READ]) == -1 || close(outPipe[WRITE]) == -1 ||
        close(inPipe[READ]) == -1 || close(inPipe[WRITE]) == -1) {
      perror("\nCHILD close error!\n");
      exit(3);
    }
    // Run the sort
    execlp("sort", "sort", "-k3,3", "-k1,1", NULL);

    perror("\nSort has failed to run correctly.\n");
    exit(4);
  }
  //****************************************************************************
  //                                Parent case
  //****************************************************************************
  // Open the out pipe as a file.
  outWrite = fdopen(outPipe[WRITE], "w");

  // Open the file to be sent to the child (who runs sort on this data)
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

  // Open file to write sorted data to.
  int total = 0, count = -1, oldAreaCode = 0, areaCode = 0, bytes_read = 0;
  FILE* sortTemp = fopen("sorted_temp.txt", "w+");
  int sort_file = open("sorted_temp.txt", O_RDWR);

  // Read from child, and put the results into a temp file.
  // Make sure to check for read errors
  while ( (bytes_read = read(inPipe[READ], readBuffer, 80)) != 0) {
    // Check for write errors
    if (write(sort_file, readBuffer, bytes_read) == -1) {
      printf("Error writing to temp file!\n");
      exit(4);
    }
  }

  // Run through the entire list, one line at a time
  while (fgets(readBuffer, 80, sortTemp) != NULL) {
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
