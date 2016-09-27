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
#define LINE_WIDTH 80

int main (int argc, char *argv[]) {
  pid_t   child_pid;
  int     inPipe[2], outPipe[2];
  int     count = -1, total = 0, oldAreaCode = 0, curAreaCode = 0;
  int     bytes_read = 0, sort_file = 0;
  char    line_buffer[80], first[80], last[80];
  FILE    *outWrite, *sortData, *sortTemp;

  // Check to see if the user used the program correctly
  if (argc == 1 || argc > 2) {
    printf("\nUsage: ./a2_sort file_name_to_sort\n\n");
    exit(1);
  }

  // Create two pipes
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
        close( inPipe[READ]) == -1 || close( inPipe[WRITE]) == -1) {
      perror("\nCHILD close error!\n");
      exit(3);
    }
    // Run sort
    execlp("sort", "sort", "-k3,3", "-k1,1", NULL);

    perror("\nSort has failed to run correctly.\n");
    exit(4);
  }
  //****************************************************************************
  //                                Parent case
  //****************************************************************************
  // Open the out pipe as a file
  outWrite = fdopen(outPipe[WRITE], "w");

  // Open the file to be sent to the child (who runs sort on this data)
  if ( (sortData = fopen(argv[1], "r")) == NULL) {
    perror("\nError opening file!\n");
  }

  // Send each line of the grep file to the child
  while (fgets(line_buffer, LINE_WIDTH, sortData) != NULL) {
    fprintf(outWrite, "%s", line_buffer);
  }

  // close unneeded files and pipes
  fflush(outWrite);
  fclose(outWrite);
  close(outPipe[READ]);
  close(outPipe[WRITE]);
  close(inPipe[WRITE]);
  fclose(sortData);

  // Open a temp file to write sorted data to
  sortTemp = fopen("sorted_temp.txt", "w+");
  sort_file = open("sorted_temp.txt", O_RDWR);

  // Read each line back from the child into a buffer, and then write
  // the buffer to a temporary grep file to process later
  while ( (bytes_read = read(inPipe[READ], line_buffer, LINE_WIDTH)) != 0) {
    // Check for write errors
    if (write(sort_file, line_buffer, bytes_read) == -1) {
      printf("Error writing to temp file!\n");
      exit(4);
    }
  }

  // Go through the sorted output file, line by line, and count up the total
  // number of people in each area code
  while (fgets(line_buffer, LINE_WIDTH, sortTemp) != NULL) {
    sscanf(line_buffer, "%s %s %d\n", last, first, &curAreaCode);

    // Detect the first areaCode
    if (oldAreaCode == 0) {
      oldAreaCode = curAreaCode;
      count++;
    }

    // Count the number of people with the same area code
    if (oldAreaCode == curAreaCode) {
      count++;
      total++;
    }
    else {
      // Found a new area code, so print it and the count that we found
      printf("Area code %d had %d unique names\n", oldAreaCode, count);
      oldAreaCode = curAreaCode;
      count = 1;
      total++;
    }
  }

  // Print the final area code / count
  printf("Area code %d had %d unique names\n", oldAreaCode, count);

  // Print out the total number of lines processed
  printf("\n%d lines were processed in this report.\n", total);

  // Close the temporary sort file and the last pipe
  fclose(sortTemp);
  close(inPipe[READ]);

  return 0;
}
