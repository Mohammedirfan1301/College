/*
    Jason Downing
    Assignment 2
    Operating Systems - COMP.3080
    9/26/2016
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/resource.h>

/*
      Useful links:
      https://www.gnu.org/software/libc/manual/html_node/Creating-a-Pipe.html
      http://tldp.org/LDP/lpg/node11.html
      http://man7.org/tlpi/code/online/diff/pipes/simple_pipe.c.html
      http://web.mst.edu/~ercal/284/UNIX-fork-exec/Fork-Execl.c
      http://www.csl.mtu.edu/cs4411.ck/www/NOTES/signal/raise.html
      https://www.gnu.org/software/libc/manual/html_node/Exit-Status.html
      http://unix.stackexchange.com/questions/103731/run-a-command-without-making-me-wait
*/

/*
    sort command should be:
    sort -k3,3 -k1,1  cs308a2_sort_data.txt
*/

int counter = 0, counter_2G = 0;

int main (void) {
  The_Wait_Status exit_union;
  pid_t   child_pid, pid, ppid;
  int     fd[2];
  int     ruid, rgid, euid, egid;
  int     priority;
  char    string[] = "Hello, world!\n";
  char    readbuffer[80];
  char    path[1024] = "core*";

  //  create 1st pipe with pipe call
  if (pipe(fd) == -1) {
    perror("\nPipe failure!\n\n");
    exit(3);
  }

  //****************************************************************************
  //                                Child Process
  //****************************************************************************
  if (child_pid == 0) {
    // Gathering credentials
    pid = getpid();
    ppid = getppid();
    ruid = getuid();
    rgid = getgid();
    euid = geteuid();
    egid = getegid();
    priority = getpriority(PRIO_PROCESS, 0);

    //  print out child credentials
    printf("CHILD Credentials:\n");
    printf("CHILD:  Process ID is:\t\t%d\n", pid);
    printf("CHILD:  Process parent ID is:\t%d\n", ppid);
    printf("CHILD:  Real UID is:\t\t%d\n", ruid);
    printf("CHILD:  Real GID is:\t\t%d\n", rgid);
    printf("CHILD:  Effective UID is:\t%d\n", euid);
    printf("CHILD:  Effective GID is:\t%d\n", egid);
    printf("CHILD:  Process priority is:\t%d\n", priority);

    // Child process closes up input side of pipe
    close(fd[0]);

    //  child must write pipe with write call
    if (write(fd[1], string, (strlen(string)+1)) == -1) {
      perror("\nWrite failed!\n");
      exit(3);
    }

    //  child enters endless loop
    while (counter_2G < 10) {   // Runs for a max of 20 billion iterations
      counter++;
      if (counter < 0) {        // Every time counter goes negative, reset it.
        counter = 0;            // This is roughly 2G, or 2 billion iterations.
        counter_2G++;
      }
    }

    // Timeout if the signal never comes through.
    write(1,"Child: timed out after 20 billion iterations\n", 51);
    exit(3);
  }

  //****************************************************************************
  //                        Parent Process
  //****************************************************************************
  else {

  }

  return 0;
}
