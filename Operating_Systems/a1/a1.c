/** This is the source file for the first assignment  **/
/** You may find it helpful to cut and paste from it  **/
/** The executable you need to exec has been compiled **/
/**   from this file and is located on mercury at:    **/
/**                 ~bill/cs308/A1                    **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/resource.h>

void sigfunc (int signum) {
  // your signal handler function, includes execl call
}

void sig_handler(int signal) {
  printf("\n\nPROF PROG: Awake in handler - You Got Me With Signal\n");
  exit(1);
}

int main (void) {

  //****************************************************************************
  //                      create pipe with pipe call
  //****************************************************************************
  int     fd[2], nbytes;
  pid_t   childpid;
  char    string[] = "Hello, world!\n";
  char    readbuffer[80];

  pipe(fd);

  //****************************************************************************
  //                      print out your credentials
  //****************************************************************************
  pid_t pid, ppid;
  int ruid, rgid, euid, egid;
  int priority;

  pid = getpid();
  ppid = getppid();
  rgid = getgid();
  ruid = getuid();
  egid = getegid();
  euid = geteuid();
  nice(5);
  priority = getpriority(PRIO_PROCESS, 0);

  printf("PARENT Credentials:\n");
  printf("PROG:  Process ID is:\t\t%d\n", pid);
  printf("PROG:  Process parent ID is:\t%d\n", ppid);
  printf("PROG:  Real GID is:\t\t%d\n", rgid);
  printf("PROG:  Real UID is:\t\t%d\n", ruid);
  printf("PROG:  Effective GID is:\t%d\n", egid);
  printf("PROG:  Effective UID is:\t%d\n", euid);
  printf("PROG:  Process priority is:\t%d\n\n", priority);

  //****************************************************************************
  //                      fork child, block on pipe with read call
  //****************************************************************************
  if((childpid = fork()) == -1)
  {
    perror("fork");
    exit(1);
  }

  // Child Process
  if(childpid == 0) {
    // child installs sigfunc with sigaction call

    // Gathering credentials
    pid = getpid();
    ppid = getppid();
    rgid = getgid();
    ruid = getuid();
    egid = getegid();
    euid = geteuid();
    nice(5);
    priority = getpriority(PRIO_PROCESS, 0);

    // child must print out credentials
    printf("CHILD Credentials:\n");
    printf("PROG:  Process ID is:\t\t%d\n", pid);
    printf("PROG:  Process parent ID is:\t%d\n", ppid);
    printf("PROG:  Real GID is:\t\t%d\n", rgid);
    printf("PROG:  Real UID is:\t\t%d\n", ruid);
    printf("PROG:  Effective GID is:\t%d\n", egid);
    printf("PROG:  Effective UID is:\t%d\n", euid);
    printf("PROG:  Process priority is:\t%d\n", priority);

    // child must write pipe with write call
    // child enters endless loop
  }

  // Parent Process
  else {
    // parent wakes from pipe read (after child writes)
    // parent sends SIGTERM to child pid with kill call
    // parent blocks on wait call

        // child moves to sigfunc when SIGTERM arrives

    // sigfunc must load prof program with execl

    // prof program will print out credentials
    // prof program installs its own signal handler
    // prof program prompts user for kill command
    // prof program enters endless loop

      // user enters shell kill command

    // prof program enters signal handler, will exit
  }

  // parent wakes from wait call when child dies
  // parent prints child term status and finishes

    // Print child term status?

  return 0;
}
