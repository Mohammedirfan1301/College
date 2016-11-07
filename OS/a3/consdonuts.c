/*
    Jason Downing
    Assignment 3
    Operating Systems - COMP.3080
    10/24/2016

    This is the Consumer code for A3
    Parts of this file are originally from this helpfile:
    http://www.cs.uml.edu/~bill/cs308/call_help_assign3.txt
*/
#include "donuts.h"

int main() {
  int a, b, c, rand_num;            // Loop variables | rand_num => random number
  int donut_type;                   // Donut types
  int type1, type2, type3, type4;   // ^
  int shmid, semid[3];              // Shared memory ID
  int flavors[NUMFLAVORS][12];      // 4 flavors of Donuts, one dozen of each flavor
  struct tm *ptm;                   // Time structure
  struct donut_ring *shared_ring;   // Donuts
  struct timeval randtime;          // Random number seed
  char sTime[40];                   // Time string

  // Man Page: http://man7.org/linux/man-pages/man2/shmget.2.html
  if ((shmid = shmget (MEMKEY, sizeof(struct donut_ring), IPC_CREAT | 0600)) == -1) {
    perror("shared get failed: ");
    exit(1);
  }

  // This had a warning about "comparison between an integer and pointer" because
  // for some reason Prof. Moloney was comparing a void *shmat with -1. But the man
  // page actually says the function returns (void *) -1 on error. So I updated this code.
  // Man Page: http://man7.org/linux/man-pages/man2/shmat.2.html
  if ((shared_ring = (struct donut_ring *) shmat(shmid, NULL, 0) ) == -1) {
    perror("shared attach failed: ");
    exit(1);
  }

  // Get semophores
  for (a = 0; a < NUMSEMIDS; a++) {
    if ((semid[a] = semget (SEMKEY + a, NUMFLAVORS, IPC_CREAT | 0600)) == -1) {
      perror("semaphore allocation failed: ");
      exit(1);
    }
  }

  // Consumer loop, must collect 10 dozen donuts
  for (a = 0; a < 10; a++) {
    type1 = 0, type2 = 0, type3 = 0, type4 = 0;

    // Consume a dozen donuts
    for (c = 0; c < 12; c++) {
      // Random donut type
      gettimeofday(&randtime, (struct timezone *) 0);

      // Use microsecond component for uniqueness
      unsigned short xsub1[3];
      xsub1[0] = (ushort) randtime.tv_usec;
      xsub1[1] = (ushort)(randtime.tv_usec >> 16);
      xsub1[2] = (ushort)(getpid());
      rand_num = nrand48(xsub1) & 3;

      // Lock the semophore
      p(semid[OUTPTR], rand_num);
      p(semid[CONSUMER], rand_num);

      // Collect a random type of donut
      donut_type = shared_ring->flavor[rand_num][shared_ring->outptr[rand_num]];

      switch (rand_num) {

        case 0: {
          flavors[rand_num][type1] = donut_type;
          type1++;
          break;
        }

        case 1: {
          flavors[rand_num][type2] = donut_type;
          type2++;
          break;
        }

        case 2: {
          flavors[rand_num][type3] = donut_type;
          type3++;
          break;
        }

        case 3: {
          flavors[rand_num][type4] = donut_type;
          type4++;
          break;
        }
      }

      // Consume donut
      if (shared_ring->outptr[rand_num] >= NUMSLOTS) {
        shared_ring->outptr[rand_num] = 0;
      } else {
        shared_ring->outptr[rand_num] = shared_ring->outptr[rand_num] + 1;
      }

      // Unlock the semophore
      v(semid[PROD], rand_num);
      v(semid[OUTPTR], rand_num);

    } // End of Consumer loop.

    // Time stuff
    ptm = localtime(&randtime.tv_sec);                  // Get time
    strftime(sTime, sizeof(sTime), "%H:%M:%S", ptm);    // Format time as hour:minute:seconds
    long ms = randtime.tv_usec / 1000;                  // Get miliseconds for the time format.

    // Entry in local file
    printf("\nProcess PID: %d", getpid());
    printf("\nTime: %s.%ld", sTime, ms);
    printf("\nDozen #: %d\n", a + 1);
    printf("Plain\tJelly\tCoconut\tHoney-dip\n");

    // Print donuts
    for (b = 0; b < 12; b++) {
      printf("%d\t%d\t%d\t%d\n", flavors[0][b], flavors[1][b], flavors[2][b], flavors[3][b]);
    }

    // Reset donut flavors
    for (b = 0; b < NUMFLAVORS; b++) {
      for (c = 0; c < 12; c++) {
        flavors[b][c] = 0;
      }
    }
  }

  return 0;
}
