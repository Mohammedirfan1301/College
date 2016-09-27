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
    Grep command should look like:
    grep "123" FILE_TO_GREP_HERE
*/

#define READ 0
#define WRITE 1

int main (int argc, char *argv[]) {
  pid_t   child_pid;
  int     inPipe[2], outPipe[2];
  char    readBuffer[80];
  FILE    *outWrite, *grepData;

  // Check to see if the user used the program correctly.
  if (argc == 1 || argc > 2) {
    printf("\nUsage: ./a2_grep file_name_to_grep\n");
    exit(1);
  }

  // Create a pipe, and check for failure (-1)
  if (pipe(outPipe) == -1 || pipe(inPipe) == -1) {
    perror("\nParent pipe failure!\n\n");
    exit(2);
  }

  // Fork to create a child process
  child_pid = fork();

  // Check for errors in forking
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

    // Run grep
    execlp("grep", "grep", "123", NULL);

    // Report errors for running sort
    perror("\nSort has failed to run correctly.\n");
    exit(4);
  }
  //****************************************************************************
  //                                Parent case
  //****************************************************************************
  // Open the out pipe as a file.
  outWrite = fdopen(outPipe[WRITE], "w");

  // Open the file to be sent to the child (who runs grep on this data)
  if ( (grepData = fopen(argv[1], "r")) == NULL) {
    perror("\nError opening file!\n");
  }

  // Loop to send each line of the file through the pipe.
  while (fgets(readBuffer, 80, grepData) != NULL) {
    fprintf(outWrite, "%s", readBuffer);
  }

  // close unneeded files and pipes.
  fflush(outWrite);
  fclose(outWrite);
  close(outPipe[READ]);
  close(inPipe[WRITE]);
  fclose(grepData);

  // Open temp file to write child output to.
  int count = 0, bytes_read = 0;
  FILE* grepTemp = fopen("grep_temp.txt", "w+");
  int grep_file = open("grep_temp.txt", O_RDWR);

  // Read from child, and put the results into a temp file.
  // Make sure to check for read errors
  while ( (bytes_read = read(inPipe[READ], readBuffer, 80)) != 0) {
    // Check for write errors
    if (write(grep_file, readBuffer, bytes_read) == -1) {
      printf("Error writing to temp file!\n");
      exit(4);
    }
  }

  // Count the number of lines in the temp file (grep matches)
  while (fgets(readBuffer, 80, grepTemp) != NULL) {
    count++;
  }

  // Print the number of matches that grep found.
  printf("\nFound %d matches in the grep data!\n\n", count);

  return 0;
}
