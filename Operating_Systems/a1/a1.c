/*
    Jason Downing
    Assignment 1
    Operating Systems - COMP.3080
    9/13/2016
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
      http://stackoverflow.com/questions/19414460/for-the-following-c-program-execl-returns-1-signifying-a-permission-denied-er
      https://www.gnu.org/software/libc/manual/html_node/Exit-Status.html
*/

// Exit status union.
typedef union {
  int exit_status;
  struct {
    unsigned sig_num: 7;
    unsigned core_dmp: 1;
    unsigned exit_num: 8;
  } parts;
} The_Wait_Status;

int counter = 0, counter_2G = 0;

// your signal handler function, includes execl call
void sigfunc (int signum) {

  printf("\nCHILD PROCESS: Awake in handler.\n");

  // run Professor program using excel
  if ( execl("assign1", "", (char*)NULL) == -1) {
    perror("\nexecl() failure!\n\n");
    exit(3);
  }
}

int main (void) {
  The_Wait_Status exit_union;
  pid_t   child_pid, pid, ppid;
  int     fd[2];
  int     ruid, rgid, euid, egid;
  int     priority;
  char    string[] = "Hello, world!\n";
  char    readbuffer[80];
  char    path[1024] = "core*";

  //  create pipe with pipe call
  if (pipe(fd) == -1) {
    perror("\npipe failure!\n\n");
    exit(3);
  }

  // Gather credentials
  pid = getpid();
  ppid = getppid();
  ruid = getuid();
  rgid = getgid();
  euid = geteuid();
  egid = getegid();
  nice(5);
  priority = getpriority(PRIO_PROCESS, 0);

  //  print out parent credentials
  printf("PARENT Credentials:\n");
  printf("PARENT:  Process ID is:\t\t%d\n", pid);
  printf("PARENT:  Process parent ID is:\t%d\n", ppid);
  printf("PARENT:  Real UID is:\t\t%d\n", ruid);
  printf("PARENT:  Real GID is:\t\t%d\n", rgid);
  printf("PARENT:  Effective UID is:\t%d\n", euid);
  printf("PARENT:  Effective GID is:\t%d\n", egid);
  printf("PARENT:  Process priority is:\t%d\n\n", priority);

  //  fork child, block on pipe with read call
  if ((child_pid = fork()) == -1)
  {
    perror("failed to fork");
    exit(3);
  }

  //****************************************************************************
  //                                Child Process
  //****************************************************************************
  if (child_pid == 0) {
    //  child installs sigfunc with sigaction call
    sigset_t  mask, proc_mask;
    struct sigaction new;

    sigemptyset(&proc_mask);                      // Clear signal mask
    sigprocmask(SIG_SETMASK, &proc_mask, NULL);   // Set proc mask

    sigemptyset(&mask);
    new.sa_mask = mask;             // Set signal mask
    new.sa_handler = sigfunc;       // Set signal function
    new.sa_flags = 0;               // Set signal flags

    // Error check
    if (sigaction(SIGTERM, &new, NULL) == -1) {
      perror("\nSigation failed!\n");
      exit(3);
    }

    // Gathering credentials
    pid = getpid();
    ppid = getppid();
    ruid = getuid();
    rgid = getgid();
    euid = geteuid();
    egid = getegid();
    nice(5);
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
    //  Parent process closes up output side of pipe
    close(fd[1]);

    // block on pipe with read call
    if (read(fd[0], readbuffer, sizeof(readbuffer)) == -1) {
      perror("\nRead failed!\n");
      exit(3);
    }

    // parent wakes from pipe read (after child writes)
    // parent sends SIGTERM to child pid with kill call
    if (kill(child_pid, SIGTERM) == -1) {
      perror("\nKill failed!\n");
      exit(3);
    }

    // parent blocks on wait call
    if ( (pid = wait(&exit_union.exit_status)) == -1) {
      perror("\nWait failed!\n");
      exit(3);
    }

    // parent prints child term status and finishes
    printf("Child %d terminated with ", pid);

    // Check for exit code vs signal code
    if (exit_union.parts.sig_num == 0) {
      printf("exit code %d and ", exit_union.parts.exit_num);
    }
    else {
      printf("signal code %d and ", exit_union.parts.sig_num);
    }

    // Check for core dump vs no core dump
    if (exit_union.parts.core_dmp == 0) {
      printf("no core dump.\n");
    }
    else {
      printf("generated a core dump.\n");
    }
  }

  return 0;
}
