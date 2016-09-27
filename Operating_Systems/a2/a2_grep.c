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

#define READ 0
#define WRITE 1

int main (int argc, char *argv[]) {
  int     inPipe[2], outPipe[2], rd_bytes;
  char    readBuffer[512];
  pid_t   child_pid;

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

    // Run grep
    execlp("grep", "grep", "123", NULL);

    perror("\nSort has failed to run correctly.\n");
    exit(4);
  }
  //****************************************************************************
  //                                Parent case
  //****************************************************************************
  FILE *outWrite, *grepData;
  char msg[2];

  // Open the out pipe as a file.
  outWrite = fdopen(outPipe[WRITE], "w");

  // Open the file to be sorted (will be sent to child)
  if ( (grepData = fopen("cs308a2_grep_data_1", "r")) == NULL) {
    perror("\nError opening file!\n");
  }

  // Loop to send each line of the file through the pipe.
  while (fgets(readBuffer, 80, grepData) != NULL) {
    fprintf(outWrite, readBuffer);
  }

  // close unneeded files and pipes.
  fflush(outWrite);
  fclose(outWrite);
  close(outPipe[READ]);
  close(inPipe[WRITE]);
  fclose(grepData);

  // Open file to write to.
  msg[1] = '\0';
  int count = 0;

  // Run through the grep data looking for matches.
  while (read(inPipe[READ], msg, 1) > 0) {
    printf("%s", msg);

    // Count all the matches
    if (msg == '\n') {
      count++;
    }
  }

  // Print the final area code / count
  printf("\n Found %d matches in the grep data!\n", count);

  return 0;
}
