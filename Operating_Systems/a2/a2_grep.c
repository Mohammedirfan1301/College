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
  // Open the out pipe as a file.
  outWrite = fdopen(outPipe[WRITE], "w");

  // Open the file to be fed to grep (will be sent to child)
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

  // Open file to write to.
  int count = 0, bytes_read = 0;
  FILE* temp = fopen("temp.txt", "w+");
  int new_file = open("temp.txt", O_RDWR);

  // Read from child, and put the results into a temp file.
  while ( (bytes_read = read(inPipe[READ], readBuffer, 80)) != 0) {
    if (write(new_file, readBuffer, bytes_read) == -1) {
      printf("Error writing to temp file!\n");
      exit(4);
    }
  }

  // Count the number of lines in the temp file (grep matches)
  while (fgets(readBuffer, 80, temp) != NULL) {
    count++;
  }

  // Print the final area code / count
  printf("\nFound %d matches in the grep data!\n\n", count);

  return 0;
}
