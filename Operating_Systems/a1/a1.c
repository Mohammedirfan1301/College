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
#include <string.h>
#include <sys/resource.h>

int counter = 0, counter_2G = 0;

// your signal handler function, includes execl call
void sigfunc (int signum) {
  // sigfunc must load prof program with execl
  execl("assign1", "/home/asus/Code/College/Operating_Systems/a1", (char*)NULL);
  perror("\nexecl() failure!\n\n");
}

int main (void) {
  int status;

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
  printf("PARENT:  Process ID is:\t\t%d\n", pid);
  printf("PARENT:  Process parent ID is:\t%d\n", ppid);
  printf("PARENT:  Real GID is:\t\t%d\n", rgid);
  printf("PARENT:  Real UID is:\t\t%d\n", ruid);
  printf("PARENT:  Effective GID is:\t%d\n", egid);
  printf("PARENT:  Effective UID is:\t%d\n", euid);
  printf("PARENT:  Process priority is:\t%d\n\n", priority);

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
    //****************************************************************************
    //                    child installs sigfunc with sigaction call
    //****************************************************************************
    sigset_t  mask, proc_mask;
    struct sigaction new;

    sigemptyset(&proc_mask);                     /** clear signal mask **/
    sigprocmask(SIG_SETMASK, &proc_mask, NULL);

    sigemptyset(&mask);
    new.sa_mask = mask;
    new.sa_handler = sigfunc;
    new.sa_flags = 0;

    // Error check
    if(sigaction(SIGTERM, &new, NULL) == -1) {
      perror("failed in sigaction:");
      exit(2);
    }

    // Gathering credentials
    pid = getpid();
    ppid = getppid();
    rgid = getgid();
    ruid = getuid();
    egid = getegid();
    euid = geteuid();
    nice(5);
    priority = getpriority(PRIO_PROCESS, 0);

    //****************************************************************************
    //                    child must print out credentials
    //****************************************************************************
    printf("CHILD Credentials:\n");
    printf("CHILD:  Process ID is:\t\t%d\n", pid);
    printf("CHILD:  Process parent ID is:\t%d\n", ppid);
    printf("CHILD:  Real GID is:\t\t%d\n", rgid);
    printf("CHILD:  Real UID is:\t\t%d\n", ruid);
    printf("CHILD:  Effective GID is:\t%d\n", egid);
    printf("CHILD:  Effective UID is:\t%d\n", euid);
    printf("CHILD:  Process priority is:\t%d\n", priority);

    //****************************************************************************
    //                    child must write pipe with write call
    //****************************************************************************
    close(fd[0]);                 // Child process closes up input side of pipe
    write(fd[1], string, (strlen(string)+1));     // write pipe

    //****************************************************************************
    //                    child enters endless loop
    //****************************************************************************
    while (counter_2G < 10) {
      counter ++;
      if (counter < 0) {
        counter = 0;
        counter_2G++;
      }
    }

    // Timeout if the signal never comes through.
    write(1,"Child: timed out after 20 billion iterations\n", 51);
    exit(2);
  }

  // Parent Process
  else {
    // Parent process closes up output side of pipe
    close(fd[1]);

    // block on pipe with read call
    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));

    // parent wakes from pipe read (after child writes)

    // parent sends SIGTERM to child pid with kill call
    kill(childpid, SIGTERM);

    // parent blocks on wait call
    wait(&status); /* can use wait(NULL) since exit status
                        from child is not used. */

    // child moves to sigfunc when SIGTERM arrives
    // prof program will print out credentials
    // prof program installs its own signal handler
    // prof program prompts user for kill command
    // prof program enters endless loop
    // user enters shell kill command
    // prof program enters signal handler, will exit

    // parent wakes from wait call when child dies
    // parent prints child term status and finishes

    // Print child term status?
  }

  return 0;
}
