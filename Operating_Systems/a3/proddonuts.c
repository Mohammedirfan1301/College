/*
    Jason Downing
    Assignment 3
    Operating Systems - COMP.3080
    10/24/2016

    This is the Producer code for A3
    Parts of this file are originally from this helpfile:
    http://www.cs.uml.edu/~bill/cs308/call_help_assign3.txt
*/
#include "donuts.h"

int   shmid, semid[3];
void  sig_handler (int sig);

int main(int argc, char *argv[]) {
  int i, j, k;
  int in_ptr [NUMFLAVORS];
  int serial [NUMFLAVORS];
  struct donut_ring *shared_ring;
  struct timeval randtime;

  // Producer initializes serial counters and in-pointers
  for(i = 0; i < NUMFLAVORS; i++) {
    in_ptr [i] = 0;
    serial [i]  = 0;
  }

  // Only need to catch some signals
  // Man page: https://linux.die.net/man/3/sigaddset
  sigset_t   mask_sigs;
  int nsigs;
  int sigs [] = {SIGHUP, SIGINT, SIGQUIT, SIGBUS, SIGTERM, SIGSEGV, SIGFPE};

  struct sigaction new_act;
  nsigs = sizeof (sigs) / sizeof (int);
  sigemptyset (&mask_sigs);

  for(i = 0; i < nsigs; i++) {
    sigaddset (&mask_sigs, sigs [i]);
  }

  for(i = 0; i < nsigs; i++) {
    new_act.sa_handler  = sig_handler;
    new_act.sa_mask   = mask_sigs;
    new_act.sa_flags  = 0;

    if(sigaction (sigs [i], &new_act, NULL) == -1) {
      perror("can't set signals: ");
      exit(1);
    }
  }

  // Man Page: http://man7.org/linux/man-pages/man2/shmget.2.html
  if((shmid = shmget (MEMKEY, sizeof(struct donut_ring), IPC_CREAT | 0600)) == -1) {
    perror("shared get failed: ");
    exit(1);
  }

  // This had a warning about "comparison between an integer and pointer" because
  // for some reason Prof. Moloney was comparing a void *shmat with -1. But the man
  // page actually says the function returns (void *) -1 on error. So I updated this code.
  // Man Page: http://man7.org/linux/man-pages/man2/shmat.2.html
  if((shared_ring = (struct donut_ring *) shmat(shmid, NULL, 0) ) == (void *) -1) {
    perror("shared attach failed: ");
    sig_handler(-1);
  }

  for(i = 0; i < NUMSEMIDS; i++) {
    if ((semid[i] = semget (SEMKEY+i, NUMFLAVORS, IPC_CREAT | 0600)) == -1) {
      perror("semaphore allocation failed: ");
      sig_handler(-1);
    }
  }

  // Seed random number generator
  // Man page: http://man7.org/linux/man-pages/man2/gettimeofday.2.html
  gettimeofday (&randtime, (struct timezone *) 0);

  // use microsecond component for uniqueness
  unsigned short xsub1[3];
  xsub1[0] = (ushort) randtime.tv_usec;
  xsub1[1] = (ushort) (randtime.tv_usec >> 16);
  xsub1[2] = (ushort) (getpid());

  // use nrand48 with xsub1 to get 32 bit random number
  // Man page: http://pubs.opengroup.org/onlinepubs/7908799/xsh/nrand48.html
  j = nrand48(xsub1) & 3;

  // use the semsetall utility to set initial semaphore values
  if(semsetall (semid [PROD], NUMFLAVORS, NUMSLOTS) == -1) {
    perror("semsetsall failed: ");
    sig_handler(-1);
  }
  if(semsetall (semid [CONSUMER], NUMFLAVORS, 0) == -1) {
    perror("semsetsall failed: ");
    sig_handler(-1);
  }
  if(semsetall (semid [OUTPTR], NUMFLAVORS, 1) == -1) {
    perror("semsetsall failed: ");
    sig_handler(-1);
  }

  // Endless loop until the consumer signals
  while (1) {
    // Seed random number generator
    // Man page: http://man7.org/linux/man-pages/man2/gettimeofday.2.html
    gettimeofday(&randtime, (struct timezone *) 0);

    // Use microsecond component for uniqueness
    unsigned short xsub1[3];
    xsub1[0] = (ushort) randtime.tv_usec;
    xsub1[1] = (ushort)(randtime.tv_usec >> 16);
    xsub1[2] = (ushort)(getpid());

    // Use nrand48 with xsub1 to get 32 bit random number
    // Man page: http://pubs.opengroup.org/onlinepubs/7908799/xsh/nrand48.html
    j = nrand48(xsub1) & 3;

    // Lock the semophore
    p(semid[PROD], j);

    // Produce
    serial[j] = serial[j] + 1; /* ID */
    shared_ring->flavor[j][in_ptr[j]] = serial[j];
    in_ptr[j] = (in_ptr[j] + 1) % NUMSLOTS;

    // Finished
    v(semid[CONSUMER], j);
  }

  return 0;
}

//  Producer signal handler below
void sig_handler(int sig) {
  int i, j, k;

  printf("In signal handler with signal # %d\n", sig);

  if(shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("handler failed shm RMID: ");
  }

  for(i = 0; i < NUMSEMIDS; i++) {
    if(semctl (semid[i], 0, IPC_RMID, 0) == -1) {
      perror("handler failed sem RMID: ");
    }
  }

  exit(5);
}
